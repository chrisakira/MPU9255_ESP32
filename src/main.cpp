#include "EaseSetup.h"


void setup() {
    Ease_init();
    mySensor.beginAccel(ACC_FULL_SCALE_2_G);
    mySensor.beginMag();
    mySensor.beginGyro();
}
 
void loop() {
    Ease_Update();
    /*Serial.println("print accel values");
    Serial.println("aX: " + String(mySensor.accelX()));
    Serial.println("aY: " + String(mySensor.accelY()));
    Serial.println("aZ: " + String(mySensor.accelZ()));
    Serial.println("\n \ngX: " + String(mySensor.gyroX()));
    Serial.println("gY: " + String(mySensor.gyroY()));
    Serial.println("gZ: " + String(mySensor.gyroZ()));
    Serial.println("aM: " + String(mySensor.accelSqrt()));
 
    //Serial.println("print mag values");
    //Serial.println("mX: " + String(mySensor.magX()));
    //Serial.println("mY: " + String(mySensor.magY()));
    //Serial.println("mZ: " + String(mySensor.magZ()));
    */
    Serial.println("hd: " + String(mySensor.magHorizDirection()));
    delay(100);
}