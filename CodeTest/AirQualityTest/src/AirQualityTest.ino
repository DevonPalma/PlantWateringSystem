/*
 * Project AirQualityTest
 * Description:
 * Author:
 * Date:
 */

#include <Air_Quality_Sensor.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

AirQualitySensor aqSensor(A0);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Serial.printf("Waiting 20 seconds for aqSensor...");
  delay(20000);

  if (aqSensor.init()) {
    Serial.printf("Sensor ready\n");
  } else {
    Serial.printf("Sensor error!\n");
  }

}

void loop() {
  int quality = aqSensor.slope();
  Serial.printf("Val: %d    Qual: %d\n", aqSensor.getValue(), quality);
}