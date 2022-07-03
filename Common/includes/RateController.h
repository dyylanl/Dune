#ifndef DUNE_RATECONTROLLER_H
#define DUNE_RATECONTROLLER_H

#include "Thread.h"

class RateController {
private:
    int rate;
    std::chrono::duration<float, std::milli> diff;
    int rest,lost,behind,it;

    std::chrono::steady_clock::time_point t1,t2;

public:
    RateController(int rate);

    void start();
    void stop();

    int getRateLoop();
    uint64_t finish();
    void sleepFor(uint64_t sleep_time);

    ~RateController();
};

#endif //DUNE_RATECONTROLLER_H
