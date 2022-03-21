/*
 * Project PlantWateringCode
 * Description: Control a smart plant watering device
 * Author: Devon Palma
 * Date: 3/21/2022
 */

SYSTEM_MODE(SEMI_AUTOMATIC);

const int MOTOR_PIN = A1;
const int MOISTURE_PIN = A0;

void setup() {
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(MOISTURE_PIN, INPUT);
}

void loop() {
    static int startTime = millis();
    int curTime = millis();

    int moisture = analogRead(MOISTURE_PIN);

    Serial.printf("MOIST: %d\n", moisture);

    if (curTime - startTime > 20000) {
        if (moisture > 1900) {
            digitalWrite(MOTOR_PIN, HIGH);
            delay(500);
            digitalWrite(MOTOR_PIN, LOW);
        }
        startTime = curTime;
    }
}