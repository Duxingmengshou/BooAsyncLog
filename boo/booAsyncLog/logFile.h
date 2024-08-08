#ifndef BOOASYNCLOG_LOGFILE_H
#define BOOASYNCLOG_LOGFILE_H

#include <string>
#include <memory>
#include <mutex>
#include <memory>
#include "../booFile/fileWrite.h"
#include "../booFile/fileName.h"
#include "../booTime/booDate.h"


namespace boo::asynclog::file {

    class logFile {
    private:
        using fileWrite = boo::file::fileWriteWapi;
        using fileCtl = std::unique_ptr<fileWrite>;

    private:
        const std::string _folderName;//日志文件夹名称
        const off_t _rollSize;//日志文件滚动的大小阈值，超过这个大小就会创建新的日志文件
        const int _checkEveryN;//每隔_checkEveryN次写入后会检查是否需要刷新或滚动文件
        unsigned long _count = 0;//当前写入次数计数
        std::unique_ptr<std::mutex> _mutex;
        fileCtl _file;//当前的日志文件对象，使用AppendFile类进行实际写入操作
    public:
        logFile() = delete;

        //传入参数：文件夹名称，日志文件大小阈值，线程安全性，刷新间隔s，n次写入检查
        logFile(const std::string &folder_name,
                off_t rollSize,
                bool threadSafe = true,
                int checkEveryN = 1024);

        ~logFile() = default;

        void pushUnsafe(const char *buf,const size_t& len);

        void pushSafe(const char *buf, const size_t&len);

        void flushUnsafe();

        void flushSafe();

        bool rollFile();
    };

}

#endif //BOOASYNCLOG_LOGFILE_H
