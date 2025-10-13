#pragma once

#include <chrono>

class CTimer {
    static void printTimes(CTimer& timer);

  public:
    void   startTimer();
    void   stopTimer();

    double elapsedTime();

  private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
};
