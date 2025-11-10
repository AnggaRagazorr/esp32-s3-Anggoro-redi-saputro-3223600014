#include <ESP32Servo.h>
#define SERVO_PIN 42

Servo servo;

void taskServo(void *pvParameters) {
  while (1) {
    for (int pos = 0; pos <= 180; pos += 10) {
      servo.write(pos);
      delay(100);
    }
    for (int pos = 180; pos >= 0; pos -= 10) {
      servo.write(pos);
      delay(100);
    }
  }
}

void setup() {
  servo.attach(SERVO_PIN);

  // Core 0
  xTaskCreatePinnedToCore(taskServo, "taskServo_Core0", 2000, NULL, 1, NULL, 0);

  // Core 1
  // xTaskCreatePinnedToCore(taskServo, "taskServo_Core1", 2000, NULL, 1, NULL, 1);
}

void loop() {}

