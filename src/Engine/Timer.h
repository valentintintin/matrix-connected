#ifndef TIMER_H
#define TIMER_H

class Timer {

public:
    Timer(unsigned long interval, bool hasExpired = false);

    void restart();
    void setExpired();
    bool hasExpired();

    unsigned long getTimeLeft();

private:
    unsigned long interval;
    unsigned long timeLast = 0;
    bool trigger = false;
};

#endif