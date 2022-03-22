#include "DTimer.h"
#include <Arduino.h>

DTimer::DTimer() {
    startTime = 0;
    durationTime = 0;
}

DTimer::DTimer(int durTime) {
    startTime = millis();
    durationTime = durTime;
}

void DTimer::setDuration(int durTime) {
    durationTime = durTime;
}

void DTimer::start() {
    startTime = millis();
}


void DTimer::stop() {
    startTime = 0;
}

int DTimer::timeLeft() {
    int endTime = startTime + durationTime;
    int curTime = millis();
    return isDone() ? 0 : endTime - curTime;
}



bool DTimer::isDone() {
    return startTime + durationTime < millis();
}



bool DTimer::isRunning() {
    return startTime != 0;
}