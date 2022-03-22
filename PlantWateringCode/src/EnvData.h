#ifndef _ENV_DATA_H_
#define _ENV_DATA_H_


#define BME680_DEBUG

#include <Adafruit_BME280.h>
#include <Air_Quality_Sensor.h>
#include <DTimer.h>
#include <math.h>


struct EnvData {
    int temperature;
    int humidity;
    int soilMoisture;
    float dustDensity;
    int airQuality;
};

class Collector {
public:
    virtual void collect(EnvData *data) = 0;
};

class BMECollector : public Collector {
private:
    Adafruit_BME280 myBME;

public:
    BMECollector() : myBME() {
        if (!myBME.begin()) {
            Serial.printf("BME Collector > Failed to init BME\n");
        } else {
            Serial.printf("BME Collector > Setup\n");
        }
    }

    void collect(EnvData *data) {
        data->temperature = myBME.readTemperature();
        data->humidity = myBME.readHumidity();
        Serial.printf("BME Collector > Collected Temp=%d  Humid=%d\n", data->temperature, data->humidity);
    }
};

class DustCollector : public Collector {
private:
    int sensorPin;
    int sampleTime;

public:
    DustCollector(int pin) {
        sensorPin = pin;
        pinMode(pin, INPUT);
        sampleTime = 2000;
        Serial.printf("Dust Collector > Setup\n");
    }

    void collect(EnvData *data) {
        DTimer samplingTimer(sampleTime);
        int lowPulseOccupancy = 0;
        int samples = 0;
        while (!samplingTimer.isDone()) { // collects data until the timer is done
            lowPulseOccupancy += pulseIn(sensorPin, LOW);
            samples++;
        }
        float ratio = lowPulseOccupancy / (sampleTime * 10.0);
        data->dustDensity = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
        Serial.printf("Dust Collector > Ratio %.2f    Concent: %.2f   Samples: %d\n", ratio, data->dustDensity, samples);
    }
};

class AirQualityCollector : public Collector {
private:
    AirQualitySensor aqSensor;

public:
    AirQualityCollector(int PIN) : aqSensor(PIN) {
        if (aqSensor.init()) {
            Serial.printf("Air Sensor > Ready\n");
        } else {
            Serial.printf("Air Sensor > Could not setup\n");
        }
    }

    void collect(EnvData *data) {
        data->airQuality = aqSensor.slope();
        Serial.printf("Air Sensor > Collected %d\n", data->airQuality);
    }
};

class SoilMoistureCollector : public Collector {
private:
    int soilPin;

public:
    SoilMoistureCollector(int PIN) {
        pinMode(PIN, INPUT);
        soilPin = PIN;
        Serial.printf("Soil Collector > Initialized\n");
    }

    void collect(EnvData *data) {
        data->soilMoisture = analogRead(soilPin);
        Serial.printf("Soil Collector > collected %d\n", data->soilMoisture);
    }
};

class SuperCollector : public BMECollector, public DustCollector, public AirQualityCollector, public SoilMoistureCollector {
public:
    SuperCollector(int dustPin, int airPin, int soilPin) : BMECollector(), DustCollector(dustPin), AirQualityCollector(airPin), SoilMoistureCollector(soilPin) {
    }

    void collect(EnvData *data) {

        Serial.printf("=== Beginning Collection ===\n");
        BMECollector::collect(data);
        DustCollector::collect(data);
        AirQualityCollector::collect(data);
        SoilMoistureCollector::collect(data);
        Serial.printf("\n\n\n");
    }
};

#endif