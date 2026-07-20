// Firmware de prueba de pines MKS Gen L
// Cada 2 segundos activa un pin diferente
// Observa con multímetro o si el motor responde

// Pines Motor 3 - Codo (Slot Z)
#define PUL3 46
#define DIR3 48
#define ENA3 62

// Pines Motor 1 - Base (Slot X) para comparar
#define PUL1 54
#define DIR1 55
#define ENA1 38

void setup() {
  Serial.begin(115200);

  // Configurar pines como salida
  pinMode(PUL1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(ENA1, OUTPUT);

  pinMode(PUL3, OUTPUT);
  pinMode(DIR3, OUTPUT);
  pinMode(ENA3, OUTPUT);

  // Habilitar motores
  digitalWrite(ENA1, LOW);
  digitalWrite(ENA3, LOW);

  Serial.println("=== TEST DE PINES ===");
  Serial.println("Mide con multimetro entre cada pin y GND");
  Serial.println("HIGH = 5V, LOW = 0V");
  Serial.println("====================");
}

void loop() {

  // TEST ENA3 (pin 62)
  Serial.println("ENA3 (pin 62) → HIGH (5V)");
  digitalWrite(ENA3, HIGH);
  delay(2000);
  Serial.println("ENA3 (pin 62) → LOW (0V)");
  digitalWrite(ENA3, LOW);
  delay(2000);

  // TEST DIR3 (pin 48)
  Serial.println("DIR3 (pin 48) → HIGH (5V)");
  digitalWrite(DIR3, HIGH);
  delay(2000);
  Serial.println("DIR3 (pin 48) → LOW (0V)");
  digitalWrite(DIR3, LOW);
  delay(2000);

  // TEST PUL3 (pin 46) - pulsos
  Serial.println("PUL3 (pin 46) → enviando 200 pulsos");
  digitalWrite(DIR3, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(PUL3, HIGH);
    delayMicroseconds(500);
    digitalWrite(PUL3, LOW);
    delayMicroseconds(500);
  }
  Serial.println("PUL3 → 200 pulsos enviados");
  delay(2000);

  // TEST PUL3 direccion contraria
  Serial.println("PUL3 (pin 46) → enviando 200 pulsos direccion contraria");
  digitalWrite(DIR3, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(PUL3, HIGH);
    delayMicroseconds(500);
    digitalWrite(PUL3, LOW);
    delayMicroseconds(500);
  }
  Serial.println("PUL3 → 200 pulsos enviados direccion contraria");
  delay(2000);

  Serial.println("====================");
  Serial.println("Repitiendo test...");
  Serial.println("====================");
}
