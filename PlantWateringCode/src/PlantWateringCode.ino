/*
 * Project PlantWateringCode
 * Description: Control a smart plant watering device
 * Author: Devon Palma
 * Date: 3/21/2022
 */

// SYSTEM_MODE(SEMI_AUTOMATIC);

#include "CloudConnect.h"
#include "EnvData.h"
#include "OLEDDisplay.h"
#include <DTimer.h>

const int RELAY_PIN = A1;
const int DUST_SENSOR_PIN = A0;
const int AIR_QUALITY_PIN = A2;
const int SOIL_PIN = A3;
const int OLED_ADDRESS = 0x3C;
const int BUTTON_PIN = D2;

CloudConnect cloudConnect;

void setup() {
    Serial.begin();
    delay(5000);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}


/* Every 30 seconds:
 * - Read the data
 * - Push to OLED
 * 
 * Every 2 minutes:
 * - Push last reading to cloud
 * 
 * Every 10 minutes:
 * - Check if plant needs watered, and do so
 * 
 * Checks if either the physical or adafruit button
 *  was pressed, and waters the plant if true.
 * 
*/
void loop() {
    static OLED_Wrapper display;
    static SuperCollector collector(DUST_SENSOR_PIN, AIR_QUALITY_PIN, SOIL_PIN);
    static DTimer t_30Sec(30 * 1000);
    static DTimer t_2Min(2 * 60 * 1000);
    static DTimer t_10Min(10 * 60 * 1000);

    static EnvData newDataSet;

    if (t_30Sec.isDone()) {
        t_30Sec.start();
        collector.collect(&newDataSet);
        display.print(&newDataSet);
        Serial.printf("Time till publish: %.2f\n", t_2Min.timeLeft() / 1000.0);
        Serial.printf("Time till Water: %.2f\n", t_10Min.timeLeft() / 1000.0);
    }

    if (t_2Min.isDone()) {
        t_2Min.start();
        cloudConnect.publish(&newDataSet);
    }

    if (t_10Min.isDone()) {
        t_10Min.start();
        if (newDataSet.soilMoisture > 1900) {
            waterPlant();
        }
    }

    if (physicalButtonPressed() || cloudConnect.buttonPressed()) {
        waterPlant();
    }
}



// Check if the physical button was pressed.
// Only returns true if the button was released
bool physicalButtonPressed() {
    static bool lastState = digitalRead(BUTTON_PIN);

    bool _lastState = lastState;
    bool _curState = digitalRead(BUTTON_PIN);
    lastState = _curState;

    if (_curState && !_lastState) {
        return true;
    }
    return false;
}


// Waters the plant by setting relay pin high then back to low after a set time
// Then pushes to the cloud the water time stamp
void waterPlant() {
    Serial.printf("Watering plant\n");
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    digitalWrite(RELAY_PIN, LOW);
    cloudConnect.sendWaterStamp();
}