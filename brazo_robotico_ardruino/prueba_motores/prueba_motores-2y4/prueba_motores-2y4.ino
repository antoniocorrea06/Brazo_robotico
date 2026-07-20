#include <AccelStepper.h>

// Motor 2 - Hombro (Slot Y)
#define PUL2 60
#define DIR2 61
#define ENA2 56

// Motor 4 - Muñeca (Slot E0)
#define PUL4 26
#define DIR4 28
#define ENA4 24

AccelStepper motor2(AccelStepper::DRIVER, PUL2, DIR2);
AccelStepper motor4(AccelStepper::DRIVER, PUL4, DIR4);

// 200 pasos x 16 microsteps = 3200 pasos por vuelta
#define PASOS_POR_VUELTA 3200

void setup() {
  Serial.begin(115200);

  pinMode(ENA2, OUTPUT); digitalWrite(ENA2, LOW);
  pinMode(ENA4, OUTPUT); digitalWrite(ENA4, LOW);

  motor2.setMaxSpeed(500);
  motor2.setAcceleration(200);
  motor2.setMinPulseWidth(5);

  motor4.setMaxSpeed(500);
  motor4.setAcceleration(200);
  motor4.setMinPulseWidth(5);

  Serial.println("Sistema pronto.");
}

void loop() {

  // =====================
  // MOTOR 2 - 1 VUELTA
  // =====================
  //Serial.println("MOTOR 2 → 1 vuelta adelante");
 // motor2.move(PASOS_POR_VUELTA);
 // while (motor2.distanceToGo() != 0) motor2.run();
  //delay(1000);

  //Serial.println("MOTOR 2 → 1 vuelta atras");
  //motor2.move(-PASOS_POR_VUELTA);
  //while (motor2.distanceToGo() != 0) motor2.run();
  //delay(1000);

  // =====================
  // MOTOR 2 - 2 VUELTAS
  // =====================
 // Serial.println("MOTOR 2 → 2 vueltas adelante");
  //motor2.move(PASOS_POR_VUELTA * 2);
  //while (motor2.distanceToGo() != 0) motor2.run();
 // delay(1000);

  //Serial.println("MOTOR 2 → 2 vueltas atras");
  //motor2.move(-PASOS_POR_VUELTA * 2);
 // while (motor2.distanceToGo() != 0) motor2.run();
  //delay(1000);

  // =====================
  // MOTOR 4 - 1 VUELTA
  // =====================
  //Serial.println("MOTOR 4 → 1 vuelta adelante");
  //motor4.move(PASOS_POR_VUELTA);
  //while (motor4.distanceToGo() != 0) motor4.run();
  //delay(1000);

  //Serial.println("MOTOR 4 → 1 vuelta atras");
  //motor4.move(-PASOS_POR_VUELTA);
  //while (motor4.distanceToGo() != 0) motor4.run();
  //delay(1000);

  // =====================
  // MOTOR 4 - 2 VUELTAS
  // =====================
  Serial.println("MOTOR 4 → 2 vueltas adelante");
  motor4.move(PASOS_POR_VUELTA * 2);
  while (motor4.distanceToGo() != 0) motor4.run();
  delay(1000);

  Serial.println("MOTOR 4 → 2 vueltas atras");
  motor4.move(-PASOS_POR_VUELTA * 2);
  while (motor4.distanceToGo() != 0) motor4.run();
  delay(1000);

  Serial.println("--- Repitiendo ---");
  delay(2000);
}