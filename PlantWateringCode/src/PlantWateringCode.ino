/*
 * Project PlantWateringCode
 * Description: Control a smart plant watering device
 * Author: Devon Palma
 * Date: 3/21/2022
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

#include <DTimer.h>
#include "EnvData.h"
#include "OLEDDisplay.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT/Adafruit_MQTT.h>
#include <Adafruit_MQTT/Adafruit_MQTT_SPARK.h>
#include "credentials.h"



const int RELAY_PIN = A1;
const int DUST_SENSOR_PIN = A0;
const int AIR_QUALITY_PIN = A2;
const int SOIL_PIN = A3;
const int OLED_ADDRESS = 0x3C;

void setup() {
    Serial.begin();
    while (!Serial);
    Serial.printf("Setup serial\n");
    delay(5000);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
    static OLED_Wrapper display;
    static SuperCollector collector(DUST_SENSOR_PIN, AIR_QUALITY_PIN, SOIL_PIN);
    static DTimer t_30Sec(15*1000);
    static DTimer t_3Min(3*60*1000);
    static DTimer t_30Min(30*60*1000);

    EnvData newDataSet;


    if (t_30Sec.isDone()) {
        t_30Sec.start();
        collector.collect(&newDataSet);
        display.print(&newDataSet);
    }


    if (t_3Min.isDone()) {
        t_3Min.start();
        // sendEnvToCloud(&newDataSet);
    }

    if (t_30Min.isDone()) {
        t_30Min.start();
        // requestPlantWatering(&newDataSet);
    }
}

void sendEnvToCloud(EnvData *data) {
    
}