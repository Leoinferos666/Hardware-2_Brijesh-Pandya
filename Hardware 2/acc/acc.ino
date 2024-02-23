#include <Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050

int16_t AcX, AcY, AcZ; // Variables to store accelerometer readings

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true); // request a total of 6 registers

  AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Convert raw accelerometer readings to degrees
  float X = (AcX != 0) ? atan2(AcX, sqrt(AcY*AcY + AcZ*AcZ)) * 180.0 / M_PI : 0;
  float Y = (AcY != 0) ? atan2(AcY, sqrt(AcX*AcX + AcZ*AcZ)) * 180.0 / M_PI : 0;
  float Z = (AcZ != 0) ? atan2(sqrt(AcX*AcX + AcY*AcY), AcZ) * 180.0 / M_PI : 0;

  // Calculate roll and pitch angles
  float roll = (AcZ != 0) ? atan2(AcY, AcZ) * 180.0 / M_PI : 0;
  float pitch = (sqrt(AcY*AcY + AcZ*AcZ) != 0) ? atan2(-AcX, sqrt(AcY*AcY + AcZ*AcZ)) * 180.0 / M_PI : 0;

  // Print accelerometer reading"s and roll/pitch angles
  Serial.print(X); Serial.print(",");
  Serial.print(Y); Serial.print(",");
  Serial.print(Z); Serial.println(",");
  Serial.print(roll); Serial.print(",");
  Serial.print(pitch); Serial.println(",");

  delay(4000);
}
