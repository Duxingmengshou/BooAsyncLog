#include <iostream>
#include <chrono>

#include "boo/booFile/fileWrite.h"
#include "boo/booAsyncLog/logFile.h"
#include "boo/booAsyncLog/asyncLog.h"


int main() {
    boo::asynclog::log::asyncLog alb;
    std::chrono::high_resolution_clock::time_point start, end;

    std::chrono::duration<double> elapsed{};
    std::vector<std::thread> threads;

    start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 1000000; ++i) {
        alb.pushSync(
                "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n",
                100);
    }


    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "同步输出100w条（100B/条）日志时间: " << elapsed.count() << " seconds" << std::endl;


    start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 1000000; ++i) {
        alb.push(
                "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n",
                100);
    }


    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "异步输出100w条（100B/条）日志时间: " << elapsed.count() << " seconds" << std::endl;
}