/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/DustSensorTest/src/DustSensorTest.ino"
/*
 * Project DustSensorTest
 * Description:
 * Author:
 * Date:
 */

#include <math.h>

void setup();
void loop();
#line 10 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/DustSensorTest/src/DustSensorTest.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);

const int DUST_SENSOR_PIN = A5;
const int SAMPLE_TIME_MS = 2000;

// setup() runs once, when the device is first turned on.
void setup() {
    // Put initialization like pinMode and begin functions here.
    Serial.begin(9600);
    pinMode(DUST_SENSOR_PIN, INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    static int startTime = millis();
    static int samples = 0;
    static int lowPulseOccupany = 0;

    int curTime = millis();
    int duration = pulseIn(DUST_SENSOR_PIN, LOW);
    samples++;
    lowPulseOccupany += duration;

    if (curTime - startTime >= SAMPLE_TIME_MS) {
        float ratio = lowPulseOccupany / (SAMPLE_TIME_MS * 10.0);
        float concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
        Serial.printf("Concentration = %f pcs/0.01cf     Samples: %d\n", concentration, samples);
        lowPulseOccupany = 0;
        samples = 0;
        startTime = curTime;
    }
}