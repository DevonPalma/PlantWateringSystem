/*
 * Project MotionSensor
 * Description:
 * Author:
 * Date:
 */

// code learned from https://arduinogetstarted.com/tutorials/arduino-motion-sensor


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