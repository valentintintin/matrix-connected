#ifndef TIMER_H
#define TIMER_H

class Timer {

public:
    explicit Timer(unsigned long interval = 0, bool hasExpired = false);

    void restart();
    void pause();
    void resume();
    void setExpired();
    bool hasExpired() const;
    void setInterval(unsigned long newInterval, bool shouldRestart = true);
    unsigned long getTimeLeft() const;

    inline bool isPaused() const {
        return timePause > 0;
    }

private:
    unsigned long interval;
    unsigned long timePause = 0;
    unsigned long timeLast = 0;
    bool trigger = false;
};

#endif