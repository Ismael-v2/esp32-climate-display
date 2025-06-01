#include <Adafruit_SSD1306.h> //For Adafruit SSD1306 OLED display.
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED failed");
    for(;;);
  }

  dht.begin();
  display.clearDisplay();
  display.setTextSize(1); // Can adjust this to make font larger. (Only works as integer values)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Reading sensor...");
  display.display();
  delay(1000);
}

void loop() {
  float tempC = dht.readTemperature(); // Reads in Celsius and then converts to Farenheit
  float tempF = tempC * 1.8 + 32;
  float hum = dht.readHumidity();

  if (isnan(tempF) || isnan(hum)) {
    Serial.println("Sensor read failed");
    return;
  }
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Temp. & Humidity:");
  display.println(""); // Space between text lines.
  
  display.print("Temperature: ");
  display.print(tempF, 1); // 1 decimal place
  display.println(" F");
  display.println(""); // Space between text lines.

  display.print("Humidity: ");
  display.print(hum, 1);
  display.println(" %");

  display.display();
  delay(2000);
}
