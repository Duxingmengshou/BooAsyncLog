#include "countDownLatch.h"


namespace boo::thread::utils {
    countDownLatch::countDownLatch(int count)
            : _mutex(),
              _count(count) {}

    void countDownLatch::countDown() {
        std::lock_guard<std::mutex> lock(_mutex);
        --_count;
        if (0 >= _count) {
            _condition.notify_all();
        }
    }

    void countDownLatch::await() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_count > 0) {
            _condition.wait(lock);
        }

    }

    size_t countDownLatch::getCount() {
        return _count;
    }


}