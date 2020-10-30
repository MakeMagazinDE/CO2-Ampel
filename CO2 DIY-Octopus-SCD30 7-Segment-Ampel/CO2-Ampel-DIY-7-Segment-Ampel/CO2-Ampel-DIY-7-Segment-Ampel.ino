#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

int CO2 = 0 ;
//Reading CO2, humidity and temperature from the SCD30 By: Nathan Seidle SparkFun Electronics 

//https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library

SCD30 airSensorSCD30; // Objekt SDC30 Umweltsensor
// Adafruit Feather 7 Segment https://learn.adafruit.com/adafruit-7-segment-led-featherwings/overview
Adafruit_7segment matrix7Seg = Adafruit_7segment(); // 7Segment Feather

void setup(){ // Einmalige Initialisierung
  Wire.begin(); // ---- Initialisiere den I2C-Bus 

  if (Wire.status() != I2C_OK) Serial.println("Something wrong with I2C");

  if (airSensorSCD30.begin() == false) {
    Serial.println("The SCD30 did not respond. Please check wiring."); 
    while(1) {
      yield(); 
      delay(1);
    } 
  }

  airSensorSCD30.setAutoSelfCalibration(false); // Sensirion no auto calibration

  airSensorSCD30.setMeasurementInterval(2);     // CO2-Messung alle 5 s

  Serial.begin(115200);
  matrix7Seg.begin(0x70); // ---- Initialisiere 7Segment Matrix
  matrix7Seg.clear();     // 
  matrix7Seg.writeDisplay();

  Wire.setClock(100000L);            // 100 kHz SCD30 
  Wire.setClockStretchLimit(200000L);// CO2-SCD30
}

void loop() { // Kontinuierliche Wiederholung 
  CO2 = airSensorSCD30.getCO2() ;
  matrix7Seg.print(CO2);
  matrix7Seg.writeDisplay();
  delay( 3000 );
}
