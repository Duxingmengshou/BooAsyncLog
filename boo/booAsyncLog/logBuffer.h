#ifndef BOOASYNCLOG_LOGBUFFER_H
#define BOOASYNCLOG_LOGBUFFER_H


#include <cstring>

namespace boo::asynclog::buffer {

    template<size_t SIZE>
    class logBuffer {
    private:
        char _buffer[SIZE]{0};
        char *_cursor = nullptr;
        size_t _size = 0;
    public:
        logBuffer();

        ~logBuffer() = default;

        size_t size();

        size_t remainingSize();

        bool push(const char *buf, size_t len);

        const char *data();

        char *cursorData();

        void reset();

        void clear();

        void writeEnd();

        bool empty();


    };




}

#include "logBuffer.cpp"

#endif //BOOASYNCLOG_LOGBUFFER_H
