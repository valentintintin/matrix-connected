#ifndef TIMER_H
#define TIMER_H

class Timer {

public:
    explicit Timer(unsigned long interval, bool hasExpired = false);

    void restart();
    void setExpired();
    bool hasExpired() const;
    void setInterval(unsigned long newInterval, bool shouldRestart = true);
    unsigned long getTimeLeft() const;

private:
    unsigned long interval;
    unsigned long timeLast = 0;
    bool trigger = false;
};

#endif