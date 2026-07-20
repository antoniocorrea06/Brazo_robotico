#include <AccelStepper.h>

// Motor 3 - (Slot Z en placa RAMPS)
#define PUL3 46
#define DIR3 48
#define ENA3 62

AccelStepper motor3(AccelStepper::DRIVER, PUL3, DIR3);

// 200 pasos x 16 microsteps = 3200 pasos por vuelta
#define PASOS_POR_VUELTA 3200

void setup() {
  Serial.begin(115200);

  // Habilitar el motor 3
  pinMode(ENA3, OUTPUT); 
  digitalWrite(ENA3, LOW);

  // Configuración de velocidad y aceleración
  motor3.setMaxSpeed(500);
  motor3.setAcceleration(200);
  motor3.setMinPulseWidth(5);

  Serial.println("Sistema listo. Iniciando prueba del Motor 3...");
}

void loop() {

  // =====================
  // MOTOR 3 - 1 VUELTA
  // =====================
  Serial.println("MOTOR 3 -> 1 vuelta adelante");
  motor3.move(PASOS_POR_VUELTA);
  while (motor3.distanceToGo() != 0) motor3.run();
  delay(1000);

  Serial.println("MOTOR 3 -> 1 vuelta atras");
  motor3.move(-PASOS_POR_VUELTA);
  while (motor3.distanceToGo() != 0) motor3.run();
  delay(1000);

  // =====================
  // MOTOR 3 - 2 VUELTAS
  // =====================
  Serial.println("MOTOR 3 -> 2 vueltas adelante");
  motor3.move(PASOS_POR_VUELTA * 2);
  while (motor3.distanceToGo() != 0) motor3.run();
  delay(1000);

  Serial.println("MOTOR 3 -> 2 vueltas atras");
  motor3.move(-PASOS_POR_VUELTA * 2);
  while (motor3.distanceToGo() != 0) motor3.run();
  delay(1000);

  Serial.println("--- Repitiendo ---");
  delay(2000);
}