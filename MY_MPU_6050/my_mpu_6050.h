#ifndef MY_MPU6050_H
#define MY_MPU6050_H
//This code was originally developed by arduino.cc user Krodal
// I have just cropped it a little to make a MPU6050 Class
//that I can use in my projects. If you find this class useful,
//please share it freely with other people

#include "Arduino.h"
#include <Wire.h>

#define MPU6050_WHO_AM_I           0x75   // R
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W
#define MPU6050_ACCEL_XOUT_H       0x3B   // R

// Default I2C address 0X68, if AD0 pin is high, address is 0x69

#define MPU6050_I2C_ADDRESS 0x68

typedef union accel_t_gyro_union
{
  struct
  {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct
  {
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
  } value;
};

class MY_MPU_6050
{
private:

    float gyro_output[3];

    float accel_output[3];

    accel_t_gyro_union accel_t_gyro;
    
    int MY_MPU_6050_read(int start, uint8_t *buffer, int size);

    int MY_MPU_6050_write(int start, const uint8_t *pData, int size);

    int MY_MPU_6050_write_reg(int reg, uint8_t data);

public:

    MY_MPU_6050();
    
    ~MY_MPU_6050();
    
    void Initialise();

    void Update();

    float GetGyroReading(int offset);

    float GetAccelerometerReading(int offset);

};

#endif // MY_MPU6050_H
