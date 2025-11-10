// ====== PIN SESUAI DENGAN WIRING KAMU ======
#define IN1 37  // B-
#define IN2 38  // B+
#define IN3 39  // A+
#define IN4 40  // A-

// Urutan langkah untuk full-step
const int seq[4][4] = {
  {1,0,1,0},  // Langkah 1
  {0,1,1,0},  // Langkah 2
  {0,1,0,1},  // Langkah 3
  {1,0,0,1}   // Langkah 4
};

// Fungsi untuk gerak maju
void stepForward(int steps) {
  for (int s = 0; s < steps; s++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(IN1, seq[i][0]);
      digitalWrite(IN2, seq[i][1]);
      digitalWrite(IN3, seq[i][2]);
      digitalWrite(IN4, seq[i][3]);
      delay(3);
    }
  }
}

void taskStepper(void *pvParameters) {
  while (1) {
    stepForward(200);   // 1 putaran kira-kira
    delay(500);
  }
}

void setup() {
  // Inisialisasi pin
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // core 0
  xTaskCreatePinnedToCore(taskStepper, "taskStepper_Core0", 4000, NULL, 1, NULL, 0);

  // core 1 
  // xTaskCreatePinnedToCore(taskStepper, "taskStepper_Core1", 4000, NULL, 1, NULL, 1);
}

void loop() {}

