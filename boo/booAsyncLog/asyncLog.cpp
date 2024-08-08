#include "asyncLog.h"


namespace boo::asynclog::log {

    asyncLog::asyncLog(const std::string &foldername, const long &rollsize)
            : _baseLogger(new asyncLogBase(foldername, rollsize)) {
        _baseLogger->waitCountDownLatch();
    }

    void asyncLog::push(const char *buf, const size_t &len) {
        _baseLogger->push(buf, len);
    }

    void asyncLog::push(const std::string &buf) {
        _baseLogger->push(buf.c_str(), buf.size());
    }

    void asyncLog::pushUTC(const char *buf, const size_t &len) {
        push(boo::time::booDate::formatUTCNow() + std::string(buf, buf + len));
    }

    void asyncLog::pushSync(const char *buf, const size_t &len) {
        _baseLogger->pushSync(buf, len);
        _baseLogger->flush();
    }
}