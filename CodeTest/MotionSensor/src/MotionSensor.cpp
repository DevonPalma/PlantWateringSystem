/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/MotionSensor/src/MotionSensor.ino"
/*
 * Project MotionSensor
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/MotionSensor/src/MotionSensor.ino"
const int MOTION_PIN = A0;
const int DISPLAY_PIN = A1;

SYSTEM_MODE(SEMI_AUTOMATIC);

// setup() runs once, when the device is first turned on.
void setup() {
    pinMode(MOTION_PIN, INPUT);
    pinMode(DISPLAY_PIN, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    static bool lastState;
    bool isMotion = digitalRead(MOTION_PIN);

    if (isMotion && !lastState) {
      Serial.printf("Motion Detected\n");
      digitalWrite(DISPLAY_PIN, HIGH);
    } else if (!isMotion && lastState) {
      Serial.printf("Motion stopped\n");
      digitalWrite(DISPLAY_PIN, LOW);
    }

    lastState = isMotion;
}