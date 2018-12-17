#include "MPU9250_asukiaaa.h"
#include "Wire.h"
#include <WiFi.h>
 
MPU9250 mySensor;

void Ease_init()
{
    while(!Serial);
    Serial.begin(9600);
    Serial.println("started");

    Wire.begin(); //sda = 21, scl = 22 
    mySensor.setWire(&Wire);
}

void Ease_Update()
{ 
    mySensor.gyroUpdate();
    mySensor.accelUpdate();
    mySensor.magUpdate();
}
