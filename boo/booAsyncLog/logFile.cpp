#include "logFile.h"

#include <memory>
#include <iostream>


namespace boo::asynclog::file {
    logFile::logFile(const std::string &folder_name,
                     off_t rollSize,
                     bool threadSafe,
                     int checkEveryN) :
            _folderName(folder_name),
            _rollSize(rollSize),
            _checkEveryN(checkEveryN),
            _mutex(threadSafe ? new(std::nothrow)  std::mutex : nullptr) {
        boo::file::fileName::makeSingleDir(folder_name);
        std::string filename = folder_name + "/" + boo::time::booDate::formatUnderlineNow() + ".log";
        _file = std::make_unique<fileWrite>(filename);
    }

    void logFile::pushUnsafe(const char *buf, const size_t &len) {
        if (nullptr == _file) {
            return;
        }
        const off_t &rest_len = _rollSize - _file->fileBytes();
        if ((off_t) len > rest_len) {
            _file->flush();
            rollFile();
            _count = 0;
            _file->write(buf, len);
            return;
        }
        _file->write(buf, len);
        ++_count;
        if (_count >= _checkEveryN) {
            _count = 0;
            _file->flush();
        }
    }

    void logFile::pushSafe(const char *buf, const size_t &len) {
        if (_mutex != nullptr) {
            std::unique_lock<std::mutex> lock(*_mutex);
            pushUnsafe(buf, len);
        } else {
            pushUnsafe(buf, len);
        }

    }

    void logFile::flushUnsafe() {
        if (_file) {
            _file->flush();
        }
    }

    void logFile::flushSafe() {
        if (_mutex != nullptr) {
            std::unique_lock<std::mutex> lock(*_mutex);
            flushUnsafe();
        } else {
            flushUnsafe();
        }
    }

    bool logFile::rollFile() {
        std::string filename = _folderName + "/" + boo::time::booDate::formatUnderlineNow() + ".log";
        _file = std::make_unique<fileWrite>(filename);
        if (_file) {
            return true;
        } else {
            return false;
        }
    }

}