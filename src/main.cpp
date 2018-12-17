#include "MPU9250_asukiaaa.h"
 
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

 
MPU9250 mySensor;
 
void setup() {
while(!Serial);
 
Serial.begin(9600);
Serial.println("started");
#ifdef _ESP32_HAL_I2C_H_
// for esp32
Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
#else
Wire.begin();
#endif
 
mySensor.setWire(&Wire);
 
mySensor.beginAccel();
mySensor.beginMag();
 
// you can set your own offset for mag values
 mySensor.magXOffset = 0;
 mySensor.magYOffset = 0;
 mySensor.magZOffset = 0;
}
 
void loop() {
mySensor.accelUpdate();
Serial.println("print accel values");
Serial.println("aX: " + String(mySensor.accelX()));
Serial.println("aY: " + String(mySensor.accelY()));
Serial.println("aZ: " + String(mySensor.accelZ()));
Serial.println("aM: " + String(mySensor.accelSqrt()));
 
mySensor.magUpdate();
Serial.println("print mag values");
Serial.println("mX: " + String(mySensor.magX()));
Serial.println("mY: " + String(mySensor.magY()));
Serial.println("mZ: " + String(mySensor.magZ()));
Serial.println("hd: " + String(mySensor.magHorizDirection()));
 
Serial.println("at " + String(millis()) + "ms");
delay(500);


}