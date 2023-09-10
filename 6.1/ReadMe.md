# Table of Contant

- [Table of Contant](#table-of-contant)
  - [MPU 6050 Yaw Angle Calculation](#mpu-6050-yaw-angle-calculation)
    - [Libraries Used](#libraries-used)
    - [Constants Used](#constants-used)
    - [Variables Used](#variables-used)
    - [Functions Used](#functions-used)
      - [void setup()](#void-setup)
      - [void loop()](#void-loop)
  - [Question Answer](#question-answer)

## MPU 6050 Yaw Angle Calculation

This code reads the z-axis gyro data from an MPU 6050 IMU and calculates the yaw angle in degrees per second. It uses the Wire library for I2C communication with the IMU.

### Libraries Used

- Wire.h

### Constants Used

- **IMU_address**: The address of the MPU 6050 IMU
- **PWR_MGMT_1**: The address of the PWR_MGMT_1 register
- **GYRO_ZOUT_H**: The address of the GYRO_ZOUT_H register

### Variables Used

- **gyro_z**: A variable to store the z-axis gyro data as a signed integer
- **yaw_angle**: A variable to store the yaw angle in degrees per second as a float

### Functions Used

#### void setup()

- Initializes I2C communication with the IMU using  
 `Wire.begin()`
- Starts a transmission to the IMU using  
 `Wire.beginTransmission(IMU_address)`
- Selects the PWR_MGMT_1 register using  
`Wire.write(PWR_MGMT_1)`
- Writes 0x00 to the PWR_MGMT_1 register (wakes up the MPU 6050) using   
  `Wire.write(0x00)`
- Ends the transmission with a stop bit using  
`Wire.endTransmission(true)`
- Initializes serial communication at 9600 baud using  
`Wire.beginTransmission(9600)`

#### void loop()

- Starts a transmission to the IMU using  
`Wire.beginTransmission(IMU_address)`
- Selects the GYRO_ZOUT_H register (starting with 0x43) using   
`Wire.write(GYRO_ZOUT_H)`
- Ends the transmission without a stop bit using   
`Wire.endTransmission(false)`
- Requests two bytes of gyro data from the IMU using   
`Wire.requestFrom(IMU_address,2,true)`
- Waits until two bytes are available to read using   
`while(Wire.available() < 2)`
- Combines the two bytes into a signed integer using   
`gyro_z = Wire.read() << 8 | Wire.read()`
- Converts the raw gyro data to degrees per second using   
`yaw_angle = gyro_z / 131.0`
- Prints the yaw angle to the serial monitor using   
`Serial.println(yaw_angle)`

## Question Answer
>If the sensor is surrounded by a noisy environment, a low-pass filter can be used to remove high-frequency noise from the sensor data. The recommended cutoff frequency depends on the sensor datasheet and the specific application requirements.

>For **MPU6050**, the datasheet recommends a low-pass filter with a cutoff frequency of ***5Hz*** for *gyro data* and ***44Hz*** for *accelerometer data*. This can be achieved by setting the *DLPF* (Digital Low Pass Filter) configuration register of the MPU6050 to the appropriate value.
