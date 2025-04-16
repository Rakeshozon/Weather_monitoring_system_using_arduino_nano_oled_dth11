# Arduino Nano Weather Station using dth 11 and oled

A simple and compact **Weather Station** project using **Arduino Nano**, **DHT11 sensor**, and a **0.96" I2C OLED display**. It reads the **temperature in Celsius** and **humidity**, and displays it on the OLED in real-time.

---

## 📦 Components Required

| Component               | Quantity |
|------------------------|----------|
| Arduino Nano           | 1        |
| DHT11 Temperature & Humidity Sensor | 1 |
| OLED Display (0.96", I2C - 128x64) | 1 |
| Jumper Wires           | Few      |
| Breadboard             | 1 (optional) |

---

## 🧰 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- Arduino Nano board drivers
- Libraries (see below)

---

## 📚 Library Installation

Install the following libraries via Arduino IDE:

1. Go to **Sketch → Include Library → Manage Libraries…**
2. Search and install:

   - **Adafruit SSD1306** by Adafruit  
   - **Adafruit GFX Library** by Adafruit  
   - **DHT sensor library** by Adafruit

These libraries handle the OLED and sensor communication.

---

## 🔌 Circuit Diagram & Connections

| OLED Display | Arduino Nano |
|--------------|--------------|
| VCC          | 5V           |
| GND          | GND          |
| SDA          | A4           |
| SCL          | A5           |

| DHT11 Sensor | Arduino Nano |
|--------------|--------------|
| VCC          | 5V           |
| GND          | GND          |
| DATA         | D2           |

> 💡 **Note**: Some DHT11 modules already have a pull-up resistor. If not, add a 10KΩ resistor between VCC and DATA.

---

## 💻 Code with Explanation

```cpp
#include <Adafruit_GFX.h>          // Graphics library for OLED
#include <Adafruit_SSD1306.h>      // OLED driver
#include <DHT.h>                   // DHT sensor library

// OLED screen configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11 sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true); // Stop if OLED not detected
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  dht.begin(); // Start DHT sensor
}

void loop() {
  float temp = dht.readTemperature(); // Temperature in °C
  float hum = dht.readHumidity();     // Humidity in %

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  // Print to Serial Monitor (optional)
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Display on OLED
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

  delay(2000); // Wait 2 seconds before next read
}
