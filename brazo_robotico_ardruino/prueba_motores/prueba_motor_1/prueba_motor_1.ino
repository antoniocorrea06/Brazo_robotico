#include <AccelStepper.h>

// Motor 1 - Base (Slot X en RAMPS)
#define PUL1 54
#define DIR1 55
#define ENA1 38

AccelStepper motor1(AccelStepper::DRIVER, PUL1, DIR1);

// 200 pasos x 16 microsteps = 3200 pasos por vuelta
#define PASOS_POR_VUELTA 6400

void setup() {
  Serial.begin(115200);

  // Habilitar el motor 1
  pinMode(ENA1, OUTPUT); 
  digitalWrite(ENA1, LOW);

  // Configuración de velocidad y aceleración
  motor1.setMaxSpeed(3200);
  motor1.setAcceleration(1500);
  motor1.setMinPulseWidth(5);

  Serial.println("Sistema listo. Iniciando prueba exclusiva del Motor 1...");
}

void loop() {
  // =====================
  // MOTOR 1 - 1 VUELTA
  // =====================
  Serial.println("MOTOR 1 -> 1 vuelta adelante");
  motor1.move(PASOS_POR_VUELTA);
  while (motor1.distanceToGo() != 0) motor1.run();
  delay(1000);

  Serial.println("MOTOR 1 -> 1 vuelta atras");
  motor1.move(-PASOS_POR_VUELTA);
  while (motor1.distanceToGo() != 0) motor1.run();
  delay(1000);

  // =====================
  // MOTOR 1 - 2 VUELTAS
  // =====================
  Serial.println("MOTOR 1 -> 2 vueltas adelante");
  motor1.move(PASOS_POR_VUELTA * 2);
  while (motor1.distanceToGo() != 0) motor1.run();
  delay(1000);

  Serial.println("MOTOR 1 -> 2 vueltas atras");
  motor1.move(-PASOS_POR_VUELTA * 2);
  while (motor1.distanceToGo() != 0) motor1.run();
  delay(1000);

  Serial.println("--- Repitiendo ---");
  delay(2000);
}
