#include <Arduino.h>
#include <Wire.h>
#include <iostream> 
#include <stdint.h>

using namespace std;
uint8_t state ;
#include <C:\Users\chmae\OneDrive\Projetos esp32\Mpu9255\lib\AkiraMpu.h>

void setup() {
  
  Serial.begin(9600);
  Wire.begin(22,21);
  Serial.println();
  delay(1000);
  initMpu();
  read_acc();
}

void loop() {
  Serial.print(ax);
  Serial.print(ay);
  Serial.print(az);
  Serial.println();
  
  delay(100 );

}