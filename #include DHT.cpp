#include <DHT.h> 
// === Konfigurasi Sensor DHT11 === 
#define DHTPIN 14 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
// === Konfigurasi Pin Aktuator Relay === 
#define RELAY1 33 
#define RELAY2 34 
// === Variabel Pewaktuan (Non-Blocking) === 
unsigned long prevMillis = 0; 
const unsigned long interval = 2000;
void setup() { 
 Serial.begin(9600); 
 dht.begin(); 
 pinMode(RELAY1, OUTPUT);

 pinMode(RELAY2, OUTPUT); 
 digitalWrite(RELAY1, HIGH); // Kondisi awal Relay 1 OFF (Active LOW) 
 digitalWrite(RELAY2, HIGH); // Kondisi awal Relay 2 OFF (Active LOW) 
} 
void loop() { 
 unsigned long currentMillis = millis(); 
 // === 1. Baca Sensor DHT11 Setiap 2 Detik === 
 if (currentMillis - prevMillis >= interval) { 
 prevMillis = currentMillis; 
 float t = dht.readTemperature(); 
 float h = dht.readHumidity(); 
 if (!isnan(t) && !isnan(h)) { 
 Serial.print(t); 
 Serial.print(","); 
 Serial.println(h); 
 } else { 
 Serial.println("DHT error"); 
 } 
 } 
 // === 2. Terima Perintah Serial dari LabVIEW === 
 if (Serial.available() > 0) { 
 String cmd = Serial.readStringUntil('\n'); 
 cmd.trim(); 
 if (cmd.equalsIgnoreCase("ON1")) digitalWrite(RELAY1, LOW); 
 else if (cmd.equalsIgnoreCase("OFF1")) digitalWrite(RELAY1, HIGH); 
 else if (cmd.equalsIgnoreCase("ON2")) digitalWrite(RELAY2, LOW); 
 else if (cmd.equalsIgnoreCase("OFF2")) digitalWrite(RELAY2, HIGH); 
 } 
}