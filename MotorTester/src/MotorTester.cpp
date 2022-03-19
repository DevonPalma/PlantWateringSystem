/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/MotorTester/src/MotorTester.ino"
/*
 * Project MotorTester
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "c:/Users/deedp/Documents/IOT/PlantWateringSystem/MotorTester/src/MotorTester.ino"
const int MOTOR_PIN = A5;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  digitalWrite(MOTOR_PIN, HIGH);
  Serial.printf("Setting motor high\n");
  delay(5000);
  digitalWrite(MOTOR_PIN, LOW);
  Serial.printf("Setting motor low\n");
  delay(5000);


}