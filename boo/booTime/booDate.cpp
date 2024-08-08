#include "booDate.h"


namespace boo::time {
    std::string booDate::formatUnderlineNow() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration) % 1000000;
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);
        char buffer[64]{0};
        std::strftime(buffer, 30, "%Y_%m_%d__%H_%M_%S", &tm);
        snprintf(buffer + 20, 10, "__%06lld", micros.count());
        return buffer;
    }

    std::string booDate::formatUTCNow() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);
        char buffer[64]{0};
        //yyyy-mm-dd hh:mm:ss
        std::strftime(buffer, 21, "%Y-%m-%d %H:%M:%S\0", &tm);
        return buffer;
    }

    void booDate::formatUTCNow(char *buf) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);
        //yyyy-mm-dd hh:mm:ss
        std::strftime(buf, 21, "%Y-%m-%d %H:%M:%S\0", &tm);
    }

}