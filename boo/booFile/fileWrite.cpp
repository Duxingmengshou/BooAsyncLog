#include "fileWrite.h"


namespace boo::file {
    fileWriteFwrite::fileWriteFwrite(const std::string &filename) :
            _fp(::fopen(filename.c_str(), "w+")),  // 'e' for O_CLOEXEC
            _writtenBytes(0) {
        if (_fp) {
            std::setbuf(_fp, _buffer);
            _isOpen = true;
        }
    }

    fileWriteFwrite::~fileWriteFwrite() {
        if (_isOpen)
            fclose(_fp);
    }

    bool fileWriteFwrite::write(const char *buf, size_t len) {
        if (!_isOpen || fwrite(buf, len, 1, _fp) != 1) {
            return false;
        } else {
            _writtenBytes += len;
            return true;
        }
    }

    bool fileWriteFwrite::flush() {
        return fflush(_fp) == 0;
    }

    long fileWriteFwrite::fileBytes() const {
        return _writtenBytes;
    }

    fileWriteFstream::fileWriteFstream(const std::string &filename) : _of(filename) {
        if (_of) {
            _isOpen = true;
        }
    }

    fileWriteFstream::~fileWriteFstream() {
        if (_isOpen) {
            _of.close();
        }
    }

    bool fileWriteFstream::write(const char *buf, size_t len) {
        _of.write(buf, len);
        _writtenBytes += len;
        return true;
    }

    bool fileWriteFstream::flush() {
        _of.flush();
        return true;
    }

    long fileWriteFstream::fileBytes() const {
        return _writtenBytes;
    }

    fileWriteWapi::fileWriteWapi(const std::string &filename) {
        _hFile = CreateFile(filename.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL, NULL);
        if (_hFile != INVALID_HANDLE_VALUE) {
            _isOpen = true;
        }

    }

    fileWriteWapi::~fileWriteWapi() {
        if (_isOpen) {
            flush();
            CloseHandle(_hFile);
        }
    }

    bool fileWriteWapi::write(const char *buf, size_t len) {
        if (_bufferIndex + len >= _bufferBytes) {
            BOOL bErrorFlag = WriteFile(_hFile, _buffer, _bufferIndex, &_dwBytesWritten, NULL);
            if (FALSE == bErrorFlag) {
                return false;
            }
            _bufferIndex = 0;// 清空缓冲区索引
        }
        // 将字符串复制到缓冲区中
        memcpy(_buffer + _bufferIndex, buf, len);
        _bufferIndex += len;
        _writtenBytes += len;
        return true;
    }

    bool fileWriteWapi::flush() {
        if (_bufferIndex > 0) {
            BOOL bErrorFlag = WriteFile(_hFile, _buffer, _bufferIndex, &_dwBytesWritten, NULL);
            if (FALSE == bErrorFlag) {
                return false;
            }
        } else {
            return false;
        }
        _bufferIndex = 0;
        return true;
    }

    long fileWriteWapi::fileBytes() const {
        return _writtenBytes;
    }
}