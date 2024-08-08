# BooAsyncLog
A C++ asynchronous logging library.

## Sample Program
```c++
#include <iostream>
#include <chrono>

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
```
### Result
同步输出100w条（100B/条）日志时间: 2.66441 seconds<br>
异步输出100w条（100B/条）日志时间: 0.0692614 seconds<br>
<br>
Time to output 1 million logs synchronously (100B/log): 2.66441 seconds(37w/s)<br>
Time to output 1 million logs asynchronously (100B/log): 0.0692614 seconds(1443w/s)
<br>
Of course, if the output is added with time, the asynchronous library will run slowly, so I suggest using the file name to check the date.
Currently only supports Windows, and may be updated in the future.
