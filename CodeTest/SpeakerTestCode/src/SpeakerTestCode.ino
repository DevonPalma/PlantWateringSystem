/*
 * Project SpeakerTestCode
 * Description:
 * Author:
 * Date:
 */

int SPEAKER_PIN = A5;

SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  static int i = 100;
  static int __delay = 200;
  tone(SPEAKER_PIN, i, __delay);
  Serial.printf("Tone %d\n", i);
  i += 25;
  delay(__delay);
}