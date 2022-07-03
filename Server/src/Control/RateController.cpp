#include <cmath>
#include <unistd.h>
#include <cstdio>
#include "../../includes/Control/RateController.h"

RateController::RateController(int rate1) : keep_running(true), rate(rate1) {
    t2 = t1;
    rest = 0, behind = 0, lost = 0;
    it = 1;
}

void RateController::stop() {
    keep_running = false;
}

RateController::~RateController() {
    keep_running = false;
}

void RateController::start() {
    t1 = std::chrono::steady_clock::now();
    t2 = t1;
}

int RateController::getRateLoop() {
    return it;
}

uint64_t RateController::finish() {
    it = 0;
    t2 = std::chrono::steady_clock::now();
    diff = t2 - t1;
    rest = rate - std::ceil(diff.count());
    if (rest < 0) {
        fprintf(stderr, ">> Ciclo principal: pérdida de frame/s.\n");
        behind = -rest;
        lost = rate + (behind - behind % rate);
        rest = rate - behind % rate;
        t1 += std::chrono::milliseconds(lost);
        it += std::floor(lost / rate);
    }
    return rest;
}

void RateController::sleepFor(uint64_t sleep_time) {
    fprintf(stderr, "ENGINE: Sleeping for %i ms.\n", rest);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    t1 += std::chrono::milliseconds(rate);
    it += 1;
}


