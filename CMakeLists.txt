cmake_minimum_required(VERSION 3.26)
project(BooAsyncLog)

set(CMAKE_CXX_STANDARD 17)

add_executable(BooAsyncLog main.cpp

        boo/booFile/fileWrite.cpp
        boo/booFile/fileWrite.h

        boo/booAsyncLog/logFile.cpp
        boo/booAsyncLog/logFile.h


        boo/booFile/fileName.cpp
        boo/booFile/fileName.h

        boo/booTime/booDate.cpp
        boo/booTime/booDate.h

        boo/booAsyncLog/asyncLogBase.cpp
        boo/booAsyncLog/asyncLogBase.h

        boo/booAsyncLog/logBuffer.h

        boo/booThread/countDownLatch.cpp
        boo/booThread/countDownLatch.h
        boo/booAsyncLog/asyncLog.cpp
        boo/booAsyncLog/asyncLog.h


)
