#include <Wire.h> // include the Wire library

#define IMU_address 0x68    // define MPU 6050 address as a constant
#define PWR_MGMT_1  0x6B     //define PWR_MGMT_1 register address
#define GYRO_ZOUT_H 0x43    // define GYRO_ZOUT_H register address

int16_t gyro_z; // declare a variable to store the z-axis gyro data as a signed integer
float yaw_angle; // declare a variable to store the yaw angle in degrees per second as a float
void setup(){
  Wire.begin(); // initialize I2C communication
  Wire.beginTransmission(IMU_address); // start a transmission to the IMU
  
  //set the DLPF to 5Hz for gyro data to remove high-frequency noise from the sensor data
  Wire.write(0x1A); // CONFIG register
  Wire.write(0x06); // set DLPF to 5Hz for gyro data 

  Wire.write(PWR_MGMT_1); // select the PWR_MGMT_1 register
  Wire.write(0x00); // set 0x00 to the PWR_MGMT_1 register (wakes up the MPU 6050)
  Wire.endTransmission(true); // end the transmission with a stop bit
  Serial.begin(9600); // initialize serial communication at 9600 baud
}

void loop(){

  Wire.beginTransmission(IMU_address);  // start a transmission to the IMU
  Wire.write(GYRO_ZOUT_H); // select the GYRO_ZOUT_H register (starting with 0x43)
  Wire.endTransmission(false); // end the transmission without a stop bit

  Wire.requestFrom(IMU_address,2,true); // request two bytes of gyro data from the IMU
  
  while(Wire.available()<2); // wait until two bytes are available to read (For Saftey)

  gyro_z =Wire.read()<<8|Wire.read(); // combine two bytes into a signed integer
  yaw_angle=gyro_z/131.0; // convert raw gyro data to degrees per second
  
  Serial.println(yaw_angle);  // print the yaw angle to the serial monitor
}

