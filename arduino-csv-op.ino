#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Sensors
  int rawTDS = analogRead(A0);
  int rawTurb = analogRead(A1);
  float voltTDS = rawTDS * (5.0 / 1023.0);
  float voltTurb = rawTurb * (5.0 / 1023.0);

  // PH sensor (assume analog pin A2)
  int rawPH = analogRead(A2);
  float voltPH = rawPH * (5.0 / 1023.0);
  float phValue = 7 + ((2.5 - voltPH) / 0.18); // basic approx calibration

  // DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Send CSV line: TDS,Turbidity,pH,Temp,Humidity
  Serial.print(voltTDS, 2); Serial.print(",");
  Serial.print(voltTurb, 2); Serial.print(",");
  Serial.print(phValue, 2); Serial.print(",");
  Serial.print(t, 1); Serial.print(",");
  Serial.println(h, 1);

  delay(2000);
}
