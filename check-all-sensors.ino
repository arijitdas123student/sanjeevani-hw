#include <DHT.h>
#include <SoftwareSerial.h>

// ---- DHT11 ----
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---- pH Sensor (UART) ----
SoftwareSerial pHSerial(10, 11); // RX, TX

// ---- Sensor Pins ----
#define TURBIDITY_PIN A1
#define TDS_PIN A0

void setup() {
  Serial.begin(9600);
  dht.begin();
  pHSerial.begin(9600);  // try 115200 if no data comes
}

void loop() {
  // ---------- Turbidity ----------
  int turbVal = analogRead(TURBIDITY_PIN);
  float turbVolt = turbVal * 5.0 / 1023.0;
  
  // ---------- TDS ----------
  int tdsVal = analogRead(TDS_PIN);
  float tdsVolt = tdsVal * 5.0 / 1023.0;
  float tdsPPM = tdsVolt * 100; // rough calibration
  
  // ---------- DHT11 ----------
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // ---------- pH Sensor ----------
  String phData = "";
  if (pHSerial.available()) {
    phData = pHSerial.readStringUntil('\n');
    phData.trim();
  }

  // ---------- Print Data ----------
  Serial.println("------ Sensor Data ------");
  Serial.print("Turbidity: "); Serial.print(turbVolt); Serial.println(" V");
  Serial.print("TDS: "); Serial.print(tdsPPM); Serial.println(" ppm");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  if (phData.length() > 0) {
    Serial.print("pH Sensor: "); Serial.println(phData);
  } else {
    Serial.println("pH Sensor: No Data");
  }
  Serial.println("-------------------------\n");

  delay(2000); // delay between readings
}
