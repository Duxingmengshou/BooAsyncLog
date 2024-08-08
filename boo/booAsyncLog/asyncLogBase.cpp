#include "asyncLogBase.h"
#include <iostream>

namespace boo::asynclog::log {
    asyncLogBase::asyncLogBase(
            const std::string &foldername,
            const long &rollsize,
            bool sync)
            : _stopLogger(false),
              _logFile(foldername, rollsize),
              _loggerThread(&asyncLogBase::logFunc, this),
              _flushThread(&asyncLogBase::flushFunc, this),
              _currentBuffer(new logBuffer),
              _latch(2),
              _synchronize(sync) {}

    asyncLogBase::~asyncLogBase() {
        {
            std::lock_guard<std::mutex> writeLock(_writeBufMutex);
            std::lock_guard<std::mutex> tempLock(_tempBufMutex);
            _stopLogger = true;
        }
        _condition.notify_one();
        _loggerThread.join();
        _flushThread.join();
        {
            flushTempQueue();
            flushWriteQueue();
        }
        _logFile.flushSafe();
    }

    void asyncLogBase::logFunc() {
        _latch.countDown();
        while (true) {
            std::unique_lock<std::mutex> writeLock(_writeBufMutex);
            _condition.wait_for(writeLock, std::chrono::milliseconds(3000), [this]() {
                std::lock_guard<std::mutex> tempLock(_tempBufMutex);
                return _tempLogBufferQueue.empty() || !_stopLogger;
            });

            while (!_writeLogBufferQueue.empty()) {
                _logFile.pushSafe(_writeLogBufferQueue.front()->data(), _writeLogBufferQueue.front()->size());
                _writeLogBufferQueue.pop();
            }
            {
                std::lock_guard<std::mutex> tempLock(_tempBufMutex);
                if (!_tempLogBufferQueue.empty()) {
                    std::swap(_writeLogBufferQueue, _tempLogBufferQueue);
                }
            }
            if (_stopLogger) {
                return;
            }
        }
    }

    void asyncLogBase::push(const char *buf, const size_t &len) {
        //线程安全?
        std::lock_guard currLock(_currentBufMutex);
        if (_currentBuffer->remainingSize() > len) {
            _currentBuffer->push(buf, len);
        } else {
            _currentBuffer->writeEnd();

            std::unique_lock<std::mutex> tempLock(_tempBufMutex);
            _tempLogBufferQueue.push(_currentBuffer);
            tempLock.unlock();


            _currentBuffer = std::make_shared<logBuffer>();
            _currentBuffer->push(buf, len);

            _condition.notify_one();
        }
    }

    void asyncLogBase::waitCountDownLatch() {
        _latch.await();
    }

    void asyncLogBase::pushSync(const char *buf, const size_t &len) {
        if (!_synchronize) {
            _logFile.pushSafe(buf, len);
        } else {
            _logFile.pushUnsafe(buf, len);
        }

    }

    void asyncLogBase::flush() {
        _logFile.flushSafe();
    }

    void asyncLogBase::flushFunc() {
        _latch.countDown();
        while (true) {
            {
                std::lock_guard<std::mutex> currLock(_currentBufMutex);
                if (!_currentBuffer->empty()) {
                    _currentBuffer->writeEnd();
                    _logFile.pushSafe(_currentBuffer->data(), _currentBuffer->size());
                    _logFile.flushSafe();
                    _currentBuffer = std::make_shared<logBuffer>();
                }
            }
            if (_stopLogger)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }

    }

    void asyncLogBase::flushWriteQueue() {
        std::unique_lock<std::mutex> writeLock(_writeBufMutex);
        while (!_writeLogBufferQueue.empty()) {
            _logFile.pushSafe(_writeLogBufferQueue.front()->data(), _writeLogBufferQueue.front()->size());
            _writeLogBufferQueue.pop();
        }
    }

    void asyncLogBase::flushTempQueue() {
        std::unique_lock<std::mutex> tempLock(_tempBufMutex);
        while (!_tempLogBufferQueue.empty()) {
            std::unique_lock<std::mutex> writeLock(_writeBufMutex);
            std::swap(_writeLogBufferQueue, _tempLogBufferQueue);
        }

    }
}