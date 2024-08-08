#ifndef BOOASYNCLOG_COUNTDOWNLATCH_H
#define BOOASYNCLOG_COUNTDOWNLATCH_H

#include <mutex>

namespace boo::thread::utils {

    class countDownLatch {
    private:
        mutable std::mutex _mutex;
        std::condition_variable _condition;
        size_t _count{0};
    public:
        explicit countDownLatch(int count);

        void countDown();

        void await();

        size_t getCount();

    };

}

#endif //BOOASYNCLOG_COUNTDOWNLATCH_H
