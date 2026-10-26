Код:
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SENSOR_PIN A0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int rawValue = analogRead(SENSOR_PIN);
  float voltage = (rawValue * 5.0) / 1024.0;
  float tempC = voltage * 100.0; 

  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(20, 5);
  display.print(tempC, 1);
  display.print(" C");
  
  int circleX = display.getCursorX() - 12; 
  display.drawCircle(circleX, 5, 2, SSD1306_WHITE);
  
  display.drawFastHLine(4, 50, 120, SSD1306_WHITE);
  
  for (int i = 0; i <= 10; i++) {
    int xPosition = 4 + (i * 12);
    display.drawFastVLine(xPosition, 45, 5, SSD1306_WHITE);
  }

  float constrainedTemp = constrain(tempC, 0.0, 50.0);
  int markerX = map(constrainedTemp, 0, 50, 4, 124);
  
  display.fillRect(markerX - 2, 46, 5, 9, SSD1306_WHITE);
  
  display.display();
  delay(1000);
}
