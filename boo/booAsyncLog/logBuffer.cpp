#include "logBuffer.h"


namespace boo::asynclog::buffer {
    template<size_t SIZE>
    logBuffer<SIZE>::logBuffer() : _cursor(_buffer) {

    }

    template<size_t SIZE>
    void logBuffer<SIZE>::clear() {
        memset(_buffer, 0, sizeof(SIZE));
        reset();
    }

    template<size_t SIZE>
    void logBuffer<SIZE>::reset() {
        _cursor = _buffer;
        _size = 0;
    }

    template<size_t SIZE>
    char *logBuffer<SIZE>::cursorData() {
        return _cursor;
    }

    template<size_t SIZE>
    const char *logBuffer<SIZE>::data() {
        return _buffer;
    }

    template<size_t SIZE>
    bool logBuffer<SIZE>::push(const char *buf, size_t len) {
        if (remainingSize() > len) {
            memcpy(_cursor, buf, len);
            _cursor += len;
            _size += len;
            return true;
        }
        return false;
    }

    template<size_t SIZE>
    size_t logBuffer<SIZE>::remainingSize() {
        return SIZE - _size;
    }

    template<size_t SIZE>
    size_t logBuffer<SIZE>::size() {
        return _size;
    }

    template<size_t SIZE>
    void logBuffer<SIZE>::writeEnd() {
        _buffer[_size] = '\0';
    }

    template<size_t SIZE>
    bool logBuffer<SIZE>::empty() {
        return _size == 0;
    }
}

