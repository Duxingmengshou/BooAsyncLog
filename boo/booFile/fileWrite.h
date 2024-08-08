#ifndef BOOASYNCLOG_FILEWRITE_H
#define BOOASYNCLOG_FILEWRITE_H

#include <string>
#include <cstdio>
#include <cwchar>
#include <fstream>
#include <windows.h>

namespace boo::file {

    class fileWriteFwrite {
    private:
        FILE *_fp = nullptr;
        char _buffer[64 * 1024] = {0};//64KB
        off_t _writtenBytes = 0;
        bool _isOpen = false;
    public:
        fileWriteFwrite() = delete;

        explicit fileWriteFwrite(const std::string &filename);

        ~fileWriteFwrite();

        bool write(const char *buf, size_t len);

        bool flush();

        long fileBytes() const;


    };

    class fileWriteFstream {
    private:
        std::ofstream _of;
        long _writtenBytes = 0;
        bool _isOpen = false;
    public:
        fileWriteFstream() = delete;

        explicit fileWriteFstream(const std::string &filename);

        ~fileWriteFstream();

        bool write(const char *buf, size_t len);

        bool flush();

        long fileBytes() const;
    };

    class fileWriteWapi {
    private:
        HANDLE _hFile;
        DWORD _dwBytesWritten = 0;
        static const unsigned long _bufferBytes = 8 * 1024;
        char _buffer[_bufferBytes];
        DWORD _writtenBytes = 0;
        bool _isOpen = false;
        DWORD _bufferIndex = 0;
    public:
        fileWriteWapi() = delete;

        explicit fileWriteWapi(const std::string &filename);

        ~fileWriteWapi();

        bool write(const char *buf, size_t len);

        bool flush();

        long fileBytes() const;

    };

}

#endif //BOOASYNCLOG_FILEWRITE_H
