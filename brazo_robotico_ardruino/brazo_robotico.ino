#include <AccelStepper.h>

// =============================================
// PINES Motores (MKS Gen L V1.0)
// =============================================
// Motor 1 - Base (Slot X)
#define PUL1 54
#define DIR1 55
#define ENA1 38

// Motor 2 - Hombro (Slot Y)
#define PUL2 60
#define DIR2 61
#define ENA2 56

// Motor 3 - Codo (Slot Z)
#define PUL3 46
#define DIR3 48
#define ENA3 62

// Motor 4 - Muñeca (Slot E0)
#define PUL4 26
#define DIR4 28
#define ENA4 24

// =============================================
// PARÁMETROS GLOBALES
// =============================================
float ratioM1 = 10; 
float ratioM2 = 10;  
float ratioM3 = 10;  
float ratioM4 = 20;
int microstep    = 16;
int maxSpeed     = 8000;
int maxAccel     = 4000;
double passiPerGrado = 0.0;
int passiPerGiro = 200;

// =============================================
// MOTORES
// =============================================
AccelStepper motor1(AccelStepper::DRIVER, PUL1, DIR1);
AccelStepper motor2(AccelStepper::DRIVER, PUL2, DIR2);
AccelStepper motor3(AccelStepper::DRIVER, PUL3, DIR3);
AccelStepper motor4(AccelStepper::DRIVER, PUL4, DIR4);

// Estado (Posiciones objetivo)
int target1 = 0;
int target2 = 0;
int target3 = 0;
int target4 = 0;
String inputBuffer = "";

// =============================================
// SETUP
// =============================================
void setup() {
  Serial.begin(115200);

  // Configurar pines Enable como salida
  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(ENA3, OUTPUT);
  pinMode(ENA4, OUTPUT);

  // Habilitar todos los drivers TB6600 (LOW = Activado)
  digitalWrite(ENA1, LOW);
  digitalWrite(ENA2, LOW);
  digitalWrite(ENA3, LOW);
  digitalWrite(ENA4, LOW);

  // Calcular pasos por grado
  recalcPassiPerGrado();

  // Configurar parámetros iniciales de los 4 motores
  motor1.setMaxSpeed(maxSpeed); motor1.setAcceleration(maxAccel); motor1.setMinPulseWidth(5);
  motor2.setMaxSpeed(maxSpeed); motor2.setAcceleration(maxAccel); motor2.setMinPulseWidth(5);
  motor3.setMaxSpeed(maxSpeed); motor3.setAcceleration(maxAccel); motor3.setMinPulseWidth(5);
  motor4.setMaxSpeed(maxSpeed); motor4.setAcceleration(maxAccel); motor4.setMinPulseWidth(5);

  Serial.println("Sistema pronto.");
}

// =============================================
// LOOP
// =============================================
void loop() {
  // Leer serial de forma no bloqueante
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      inputBuffer.trim();
      if (inputBuffer.length() > 0)
        processLine(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }

  // Ejecutar un paso si corresponde según el reloj de la placa
  motor1.run();
  motor2.run();
  motor3.run();
  motor4.run();
}

// =============================================
// FUNCIONES
// =============================================
void recalcPassiPerGrado() {
  passiPerGrado = (double)(passiPerGiro * microstep) / 360.0;
}

long degreesToSteps(int degrees) {
  return (long)(degrees * passiPerGrado);
}

void processLine(String line) {

  // Configuración desde app C#
  if (line.startsWith("CFG:")) {
    handleConfig(line.substring(4));
    Serial.println("ok");
    return;
  }

  // Leer Targets de cada motor
  if (line.startsWith("M1:")) { target1 = line.substring(3).toInt(); return; }
  if (line.startsWith("M2:")) { target2 = line.substring(3).toInt(); return; }
  if (line.startsWith("M3:")) { target3 = line.substring(3).toInt(); return; }
  if (line.startsWith("M4:")) { target4 = line.substring(3).toInt(); return; }
  
  // Ignorar comandos no usados (como la pinza)
  if (line.startsWith("GRIP:")) { return; }
  if (line.startsWith("C:"))    { return; }

  // Ejecutar movimiento
  if (line == "RUN") {
    long stepsM1 = (long)(target1 * passiPerGrado * ratioM1);
    long stepsM2 = (long)(target2 * passiPerGrado * ratioM2);
    long stepsM3 = (long)(target3 * passiPerGrado * ratioM3);
    long stepsM4 = (long)(target4 * passiPerGrado * ratioM4);
    // Asignar nuevas posiciones objetivo
    motor1.moveTo(degreesToSteps(target1));
    motor2.moveTo(degreesToSteps(target2));
    motor3.moveTo(degreesToSteps(target3));
    motor4.moveTo(degreesToSteps(target4));

    // Bucle bloqueante para el movimiento físico sincronizado.
    // Solo sale cuando los 4 motores han llegado a la distancia 0.
    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || 
           motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
      motor1.run();
      motor2.run();
      motor3.run();
      motor4.run();
    }

    Serial.println("ready");
    return;
  }

  // Home General (Todos los motores a la vez)
  if (line == "HOME") {
    motor1.moveTo(0);
    motor2.moveTo(0);
    motor3.moveTo(0);
    motor4.moveTo(0);
    
    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || 
           motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
      motor1.run();
      motor2.run();
      motor3.run();
      motor4.run();
    }
    target1 = 0; target2 = 0; target3 = 0; target4 = 0;
    Serial.println("ok");
    return;
  }

  // Home Individuales
  if (line == "HOME_1") { motor1.moveTo(0); while (motor1.distanceToGo() != 0) motor1.run(); target1 = 0; Serial.println("ok"); return; }
  if (line == "HOME_2") { motor2.moveTo(0); while (motor2.distanceToGo() != 0) motor2.run(); target2 = 0; Serial.println("ok"); return; }
  if (line == "HOME_3") { motor3.moveTo(0); while (motor3.distanceToGo() != 0) motor3.run(); target3 = 0; Serial.println("ok"); return; }
  if (line == "HOME_4") { motor4.moveTo(0); while (motor4.distanceToGo() != 0) motor4.run(); target4 = 0; Serial.println("ok"); return; }

  // Parada de emergencia (Clava los 4 motores)
  if (line == "EMERGENCY_STOP") {
    motor1.stop(); motor1.setCurrentPosition(motor1.currentPosition()); target1 = motor1.currentPosition();
    motor2.stop(); motor2.setCurrentPosition(motor2.currentPosition()); target2 = motor2.currentPosition();
    motor3.stop(); motor3.setCurrentPosition(motor3.currentPosition()); target3 = motor3.currentPosition();
    motor4.stop(); motor4.setCurrentPosition(motor4.currentPosition()); target4 = motor4.currentPosition();
    Serial.println("ok");
    return;
  }

  // Set home manual (Fija el 0 lógico en la posición física actual para los 4 motores)
  if (line == "SETHOME") {
    motor1.setCurrentPosition(0); target1 = 0;
    motor2.setCurrentPosition(0); target2 = 0;
    motor3.setCurrentPosition(0); target3 = 0;
    motor4.setCurrentPosition(0); target4 = 0;
    Serial.println("ok");
    return;
  }

  // Enable/Disable de TODOS los motores (Libera o bloquea los ejes)
  if (line == "ENA:1") {
    digitalWrite(ENA1, LOW); digitalWrite(ENA2, LOW); digitalWrite(ENA3, LOW); digitalWrite(ENA4, LOW);
    Serial.println("ok");
    return;
  }
  if (line == "ENA:0") {
    digitalWrite(ENA1, HIGH); digitalWrite(ENA2, HIGH); digitalWrite(ENA3, HIGH); digitalWrite(ENA4, HIGH);
    Serial.println("ok");
    return;
  }
}

void handleConfig(String config) {
  int sep = config.indexOf(':');
  if (sep == -1) return;

  String param = config.substring(0, sep);
  int    value = config.substring(sep + 1).toInt();

  if (param == "passiPerGiro") {
    passiPerGiro = value;
    recalcPassiPerGrado();
  }
  else if (param == "microstep") {
    microstep = value;
    recalcPassiPerGrado();
  }
  else if (param == "maxSpeed") {
    maxSpeed = value;
    motor1.setMaxSpeed(maxSpeed);
    motor2.setMaxSpeed(maxSpeed);
    motor3.setMaxSpeed(maxSpeed);
    motor4.setMaxSpeed(maxSpeed);
  }
  else if (param == "maxAccel") {
    maxAccel = value;
    motor1.setAcceleration(maxAccel);
    motor2.setAcceleration(maxAccel);
    motor3.setAcceleration(maxAccel);
    motor4.setAcceleration(maxAccel);
  }
}