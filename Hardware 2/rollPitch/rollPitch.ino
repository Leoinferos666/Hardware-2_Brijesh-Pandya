#include <Wire.h>

const int MPU_addr = 0x68;  // I2C address of the MPU-6050
const int numReadings = 10; // Number of readings to average

int16_t AcX, AcY, AcZ;       // Variables to store accelerometer readings
int readingsX[numReadings];
int readingsY[numReadings];
int readingsZ[numReadings];
int currentIndex = 0; // Change 'index' to 'currentIndex'

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

float calculateAverage(int readings[]) {
  int total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += readings[i];
  }
  return static_cast<float>(total) / numReadings;
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true); // request a total of 6 registers

  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Store current readings in arrays
  readingsX[currentIndex] = AcX;
  readingsY[currentIndex] = AcY;
  readingsZ[currentIndex] = AcZ;
  currentIndex = (currentIndex + 1) % numReadings;

  // Calculate averages
  float avgX = calculateAverage(readingsX);
  float avgY = calculateAverage(readingsY);
  float avgZ = calculateAverage(readingsZ);

  // Convert raw accelerometer readings to degrees
  float X = (avgX != 0) ? atan2(avgX, sqrt(avgY * avgY + avgZ * avgZ)) * 180.0 / M_PI : 0;
  float Y = (avgY != 0) ? atan2(avgY, sqrt(avgX * avgX + avgZ * avgZ)) * 180.0 / M_PI : 0;
  float Z = (avgZ != 0) ? atan2(sqrt(avgX * avgX + avgY * avgY), avgZ) * 180.0 / M_PI : 0;

  // Calculate roll and pitch angles
  float roll = (avgZ != 0) ? atan2(avgY, avgZ) * 180.0 / M_PI : 0;
  float pitch = (sqrt(avgY * avgY + avgZ * avgZ) != 0) ? atan2(-avgX, sqrt(avgY * avgY + avgZ * avgZ)) * 180.0 / M_PI : 0;

  // Print accelerometer readings and roll/pitch angles
  Serial.print(X); Serial.print(",");
  Serial.print(Y); Serial.print(",");
  Serial.print(Z); Serial.print(",");
  Serial.print(roll); Serial.print(",");
  Serial.print(pitch); Serial.println(",");

  delay(100);
}
