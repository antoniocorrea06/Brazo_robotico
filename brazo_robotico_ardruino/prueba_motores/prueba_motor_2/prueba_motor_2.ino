#include <AccelStepper.h>

// Motor 2 - Hombro (Slot Y en RAMPS)
#define PUL2 60
#define DIR2 61
#define ENA2 56

AccelStepper motor2(AccelStepper::DRIVER, PUL2, DIR2);

// 200 pasos x 16 microsteps = 3200 pasos por vuelta
#define PASOS_POR_VUELTA 3200

void setup() {
  Serial.begin(115200);

  // Habilitar el motor 2
  pinMode(ENA2, OUTPUT); 
  digitalWrite(ENA2, LOW);

  // Configuración de velocidad y aceleración
  motor2.setMaxSpeed(500);
  motor2.setAcceleration(200);
  motor2.setMinPulseWidth(5);

  Serial.println("Sistema listo. Iniciando prueba exclusiva del Motor 2...");
}

void loop() {
  // =====================
  // MOTOR 2 - 1 VUELTA
  // =====================
  Serial.println("MOTOR 2 -> 1 vuelta adelante");
  motor2.move(PASOS_POR_VUELTA);
  while (motor2.distanceToGo() != 0) motor2.run();
  delay(1000);

  Serial.println("MOTOR 2 -> 1 vuelta atras");
  motor2.move(-PASOS_POR_VUELTA);
  while (motor2.distanceToGo() != 0) motor2.run();
  delay(1000);

  // =====================
  // MOTOR 2 - 2 VUELTAS
  // =====================
  Serial.println("MOTOR 2 -> 2 vueltas adelante");
  motor2.move(PASOS_POR_VUELTA * 2);
  while (motor2.distanceToGo() != 0) motor2.run();
  delay(1000);

  Serial.println("MOTOR 2 -> 2 vueltas atras");
  motor2.move(-PASOS_POR_VUELTA * 2);
  while (motor2.distanceToGo() != 0) motor2.run();
  delay(1000);

  Serial.println("--- Repitiendo ---");
  delay(2000);
}
