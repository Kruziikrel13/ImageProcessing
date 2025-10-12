#pragma once

#include <iostream>
#include <sys/time.h>
#include <sys/times.h>
#include <ctime>
#include <unistd.h>

class Timer {

    struct timeval rS, rE;
    // clock_t rS , rE;
    struct tms uS, uE;
    double     real, user, sys;

  public:
    void   start();
    void   stop();
    void   printTimes();
    double getReal() {
        return real;
    }
    double getUser() {
        return user;
    }
    double getSys() {
        return sys;
    }
};
