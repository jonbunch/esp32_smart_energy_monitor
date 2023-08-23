// Include libraries for the onboard display and current sensor
#include <Wire.h>               
#include "HT_SSD1306Wire.h"
#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

// Display setup (manufacturer provided): addr , freq , i2c group , resolution , rst
SSD1306Wire  display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

// Pin mapping
const int sensor_pin = 6;        // Signal from current sensor: pin 6, analog input
const int onboard_led_pin = 35;  // White LED built-in to the dev board: pin 35, active LOW

void setup() {
  // Enable serial monitor
  Serial.begin(115200);
  Serial.println("Starting up...");
  // Set up pins
  pinMode(sensor_pin, INPUT);
  pinMode(onboard_led_pin, OUTPUT);
  // Turn on the "Vext" transistor-controlled pins (controls the onboard display)
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
  delay(100);
  // Initialize display and set text parameters
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //Setup energy monitor instance. (original value 111.1)
  emon1.current(sensor_pin, 60);
}

void loop() {
  //Calculate and print Irms.
  double Irms = emon1.calcIrms(1480);
  Serial.print("Irms: ");
  Serial.println(Irms);
  // Setup built-in OLED
  display.clear();
  display.drawString(0, 30, ("Irms: " + String(Irms)));
  display.display();
  delay(1000);
}