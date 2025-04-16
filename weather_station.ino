#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT settings
#define DHTPIN 2       // DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();    // Temperature in Celsius
  float hum = dht.readHumidity();        // Humidity in %

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT11");
    return;
  }

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Print to OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(temp);
  display.println("C");

  display.setCursor(0, 35);
  display.print("Hum: ");
  display.print(hum);
  display.println("%");

  display.display();

  delay(2000); // Update every 2 seconds
}
