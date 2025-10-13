#include "utils/timer.h"

double CTimer::elapsedTime() {
    std::chrono::duration<double> duration = this->end - this->start;
    return duration.count();
}

void CTimer::startTimer() {
    this->start = std::chrono::high_resolution_clock::now();
}
void CTimer::stopTimer() {
    this->end = std::chrono::high_resolution_clock::now();
}

void CTimer::printTimes(CTimer& timer) {
    double elapsed = timer.elapsedTime();
    printf("Elapsed time: %.6f seconds\n", elapsed);
}
