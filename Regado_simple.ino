const int PIN_SENSOR = 34; // Pin analógico donde va AOUT del sensor
const int PIN_DRIVER = 23; // Pin digital que va a IN1 e IN2 del ULN2003

// Calibración: ~3000 en seco, ~1400 en agua
const int UMBRAL_SECO = 2400; 

void setup() {
  Serial.begin(115200);
  pinMode(PIN_DRIVER, OUTPUT);
  digitalWrite(PIN_DRIVER, LOW); // Inicia con la bomba apagada
  analogReadResolution(12);
}

void loop() {
  int humedad = analogRead(PIN_SENSOR);
  Serial.print("Lectura sensor: ");
  Serial.print(humedad);

  if (humedad > UMBRAL_SECO) {
    Serial.println(" -> [TIERRA SECA] Regando...");
    digitalWrite(PIN_DRIVER, HIGH); // Enciende la bomba
    delay(2000);                    // Riega por 2 segundos
    
    digitalWrite(PIN_DRIVER, LOW);  // Apaga la bomba
    Serial.println(" -> [PAUSA] Esperando absorción...");
    delay(5000);                    // Espera 5 segundos antes de volver a medir
  } 
  else {
    digitalWrite(PIN_DRIVER, LOW);  // Bomba apagada
    Serial.println(" -> [HUMEDAD OK] Todo bien.");
  }

  delay(1000);
}