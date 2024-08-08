#ifndef BOOASYNCLOG_BOODATE_H
#define BOOASYNCLOG_BOODATE_H

#include <string>
#include <chrono>

namespace boo::time {

    class booDate {
    public:
        static std::string formatUnderlineNow();

        static std::string formatUTCNow();

        //buf should >20
        static void formatUTCNow(char *buf);
    };

}

#endif //BOOASYNCLOG_BOODATE_H
