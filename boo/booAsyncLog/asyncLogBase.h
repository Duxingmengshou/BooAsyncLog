#ifndef BOOASYNCLOG_ASYNCLOGBASE_H
#define BOOASYNCLOG_ASYNCLOGBASE_H

#include <thread>
#include <mutex>
#include <queue>


#include "logFile.h"
#include "logBuffer.h"

#include "../booThread/countDownLatch.h"

namespace boo::asynclog::log {

    class asyncLogBase {
    private:
        using logBuffer = boo::asynclog::buffer::logBuffer<4 * 1024>;
        using logBufferSharedPtr = std::shared_ptr<logBuffer>;
    private:
        boo::asynclog::file::logFile _logFile;
        std::queue<logBufferSharedPtr> _tempLogBufferQueue, _writeLogBufferQueue;
        logBufferSharedPtr _currentBuffer;
        std::mutex _tempBufMutex, _writeBufMutex, _currentBufMutex;
        std::condition_variable _condition;
        std::atomic<bool> _stopLogger;
        std::thread _loggerThread, _flushThread;
        boo::thread::utils::countDownLatch _latch;
        bool _synchronize = false;
    private:
        void logFunc();

        void flushFunc();

    public:
        asyncLogBase() = delete;

        asyncLogBase(const std::string &foldername, const long &rollsize, bool sync = false);

        ~asyncLogBase();

        void push(const char *buf, const size_t &len);

        void pushSync(const char *buf, const size_t &len);

        void flush();

        void flushWriteQueue();

        void flushTempQueue();

        void waitCountDownLatch();
    };

}
#endif //BOOASYNCLOG_ASYNCLOGBASE_H
