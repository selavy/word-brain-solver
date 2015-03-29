//
// Created by peter on 3/29/15.
//

#ifndef WORD_BRAIN_SOLVER_TIMER_H
#define WORD_BRAIN_SOLVER_TIMER_H

#include <cstdint>
#include <chrono>

class Timer {
public:
    Timer();
    ~Timer() {}
    void start();
    int64_t elapsedNs() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};


#endif //WORD_BRAIN_SOLVER_TIMER_H
