#ifndef _D_TIMER_H_
#define _D_TIMER_H_


class DTimer {
    unsigned int startTime;
    unsigned int durationTime;


  public:

    DTimer();
    DTimer(int durTime);

    void setDuration(int durTime);

    void start();
    void stop();

    int timeLeft();

    bool isDone();
    bool isRunning();
};

#endif
