#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET 17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("Embedead");

  pinMode(2, OUTPUT);

  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Embedded Midterm");
  display.display();
  delay(1000);
}
void loop() {
  if (SerialBT.available()) {
    display.clearDisplay();
    display.setCursor(0, 0);

    String incomingData = SerialBT.readString();  // Adjust the size accordingly
    incomingData.trim();

    // Check if the received data is "0"
    if (incomingData.equals("1")) {
      digitalWrite(2, HIGH);

    } else if (incomingData.equals("0")) {
      digitalWrite(2, LOW);
    }

    display.clearDisplay();
    display.println(incomingData);
    display.display();
  }
}