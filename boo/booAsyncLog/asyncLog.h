#ifndef BOOASYNCLOG_ASYNCLOG_H
#define BOOASYNCLOG_ASYNCLOG_H

#include <memory>
#include <string>

#include "asyncLogBase.h"
#include "../booTime/booDate.h"


namespace boo::asynclog::log {

    class asyncLog {
    private:
        std::shared_ptr<asyncLogBase> _baseLogger;

    public:
        explicit asyncLog(const std::string &foldername = "log", const long &rollsize = 100 * 1024 * 1024);

        ~asyncLog() = default;

        void push(const char *buf, const size_t& len);

        void push(const std::string &buf);

        void pushUTC(const char *buf,const size_t&len);

        void pushSync(const char *buf, const size_t &len);

    };

}
#endif //BOOASYNCLOG_ASYNCLOG_H
