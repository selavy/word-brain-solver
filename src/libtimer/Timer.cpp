//
// Created by peter on 3/29/15.
//

#include "Timer.h"

Timer::Timer() : start_() {}

void Timer::start() {
    start_ = std::chrono::high_resolution_clock::now();
}

int64_t Timer::elapsedNs() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_).count();
}




