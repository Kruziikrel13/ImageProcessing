#pragma once

#include <chrono>

class CTimer {
  public:
    void   startTimer();
    void   stopTimer();
    static void printTimes(CTimer& timer);

    double elapsedTime();

  private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
};
