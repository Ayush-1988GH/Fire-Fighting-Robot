#include <Servo.h>

Servo myServo;

// Motor B pins
#define IN3 10
#define IN4 11
#define ENB 8

int relayPin = 7;
int buzzer = 12;

int flame1 = 2;
int flame2 = 3;
int flame3 = 4;
int flame4 = 5;
int flame5 = 6;

bool approachDone = false; // ensures motor forward + beep runs only once per fire event

void setup() {
  myServo.attach(9);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(flame1, INPUT);
  pinMode(flame2, INPUT);
  pinMode(flame3, INPUT);
  pinMode(flame4, INPUT);
  pinMode(flame5, INPUT);

  digitalWrite(relayPin, HIGH); // Pump OFF
  digitalWrite(buzzer, LOW);

  // Motor stopped initially
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  myServo.write(0); // initial position
}

void loop() {

  bool fireDetected =
      digitalRead(flame1) == HIGH ||
      digitalRead(flame2) == HIGH ||
      digitalRead(flame3) == HIGH ||
      digitalRead(flame4) == HIGH ||
      digitalRead(flame5) == HIGH;

  if (fireDetected) {

    // --- PHASE 1: Approach + Beep (runs only once when fire is first detected) ---
    if (!approachDone) {

      // Move forward for 1.5 seconds while beeping continuously
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 150);

      unsigned long startTime = millis();
      while (millis() - startTime < 300) {
        digitalWrite(buzzer, HIGH);  // continuous beep during approach
      }

      // Stop motor
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);

      digitalWrite(buzzer, LOW);    // brief pause after approach
      delay(200);

      approachDone = true;
    }

    // --- PHASE 2: Pump ON + Servo sweep (runs continuously until fire out) ---
    digitalWrite(relayPin, LOW);  // Pump ON
    digitalWrite(buzzer, HIGH);   // Buzzer ON (continuous while fire active)

    // Sweep 0 → 40
    for (int angle = 0; angle <= 40; angle++) {
      myServo.write(angle);
      delay(15);
    }

    delay(50);

    // Sweep 40 → 0
    for (int angle = 40; angle >= 0; angle--) {
      myServo.write(angle);
      delay(15);
    }

    delay(50);

  } else {

    // --- Fire extinguished: reset everything ---
    digitalWrite(relayPin, HIGH); // Pump OFF
    digitalWrite(buzzer, LOW);    // Buzzer OFF

    // Motor stopped
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);

    myServo.write(0);             // Servo reset
    approachDone = false;         // Reset flag for next fire event
  }
}
