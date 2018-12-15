#include <stdint.h>
enum registers
{
    //sensor adresses
    MAG_address       = 0x0C,//magnetometer
    MPU_address       = 0x68,//main chip

    //main chip
    USER_CTRL         = 0x6A,
    PWR_MGMT_1        = 0x6B,
    PWR_MGMT_2        = 0x6C,
    SIGNAL_PATH_RESET = 0x68,
    INT_PIN_CFG       = 0x37,
    ST1               = 0x02,
    ACCEL_CONFIG      = 0x1C,
    ACCEL_CONFIG_2    = 0x1D,
    MOT_DETECT_CTRL   = 0x69,
    WOM_THR           = 0x1F,
    GYRO_CONFIG       = 0x1B,
    CONFIG            = 0x1A,
    SMPLRT_DIV        = 0x19,
    INT_ENABLE        = 0x38,
    INT_STATUS        = 0x3A,
    WHO_AM_I          = 0x75,

    //gyroscope offset
    XG_OFFSET_H       = 0x13,
    XG_OFFSET_L       = 0x14,
    YG_OFFSET_H       = 0x15,
    YG_OFFSET_L       = 0x16,
    ZG_OFFSET_H       = 0x17,
    ZG_OFFSET_L       = 0x18,

    //accelerometer offset
    XA_OFFSET_H       = 0x77,
    XA_OFFSET_L       = 0x78,
    YA_OFFSET_H       = 0x7A,
    YA_OFFSET_L       = 0x7B,
    ZA_OFFSET_H       = 0x7D,
    ZA_OFFSET_L       = 0x7E,

    //magnetometer
    MAG_ID            = 0x00,
    CNTL              = 0x0A,
    CNTL2             = 0x0B,
    ASAX              = 0x10,
    ASAY              = 0x11,
    ASAZ              = 0x12,

    /// data registers
    MAG_XOUT_L        = 0x03,//magnetometer
    GYRO_XOUT_H       = 0x43,//gyro
    ACCEL_XOUT_H      = 0x3B,//accelerometer
    TEMP_OUT_H        = 0x41,//thermometer

};

enum modules
{
  Acc_X,//accelerometer X axis
  Acc_Y,//accelerometer Y axis
  Acc_Z,//accelerometer Z axis
  Gyro_X,//gyroscope X axis
  Gyro_Y,//gyroscope Y axis
  Gyro_Z,//gyroscope Z axis
  magnetometer,//magnetometer
  accelerometer,//accelerometer
  gyroscope,//gyroscope
  thermometer,//thermometer
  signalPaths,//all signal paths
};

enum scales
{
  scale_2g,//+-2g
  scale_4g,//+-4g
  scale_8g,//+-8g
  scale_16g,//+-16g
  scale_250dps,//+-250 degrees per second
  scale_500dps,//+- 500 degrees per second
  scale_1000dps,//+- 1000 degrees per second
  scale_2000dps,//+- 2000 degrees per second
};

//axis
enum axis
{
  X_axis,
  Y_axis,
  Z_axis,
};

//bandwidth
enum bandwidth
{
  gyro_8800Hz,
  gyro_3600Hz,
  gyro_250Hz,
  gyro_184Hz,
  gyro_92Hz,
  gyro_41Hz,
  gyro_20Hz,
  gyro_10Hz,
  gyro_5Hz,
  acc_1113Hz,
  acc_460Hz,
  acc_184Hz,
  acc_92Hz,
  acc_41Hz,
  acc_20Hz,
  acc_10Hz,
  acc_5Hz,
};

enum interrupt_pin
{
  active_low,//interrupt pin gets low when active
  active_high,//interrupt pin gets high when active
  open_drain,//open drain mode
  push_pull,//push-pull mode
  pulse_output,//pulse type output
  latched_output,//latch type output
};

//available interrupts
enum interrupts
{
  motion_interrupt,//motion detection
  FIFO_overflow_interrupt,//fifo overflow
  Fsync_interrupt,//fsync interrupts
  raw_rdy_interrupt,//raw readings ready
};

int16_t ax=0;//X axis
int16_t ay=0;//Y axis
int16_t az=0;//Z axis

int16_t gx=0;//X axis
int16_t gy=0;//Y axis
int16_t gz=0;//Z axis

  //magnetometer raw data
int16_t mx=0;//X axis
int16_t my=0;//Y axis
int16_t mz=0;//Z axis

int initMpu()
{
    class TwoWire Wire;
    Wire.begin();//enable I2C interface
    Hreset();//reset the chip
}