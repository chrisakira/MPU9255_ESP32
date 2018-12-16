#include <stdint.h>
#include <Wire.h>

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

int16_t mx=0;//X axis
int16_t my=0;//Y axis
int16_t mz=0;//Z axis

double mx_sensitivity;//X axis
double my_sensitivity;//Y axis
double mz_sensitivity;//Z axis

int AX_offset;//X axis
int AY_offset;//Y axis
int AZ_offset;//Z axis

int GX_offset;//X axis
int GY_offset;//Y axis
int GZ_offset;//Z axis

int16_t uint8ToUint16(uint8_t Lbyte, uint8_t Hbyte)
{
  return ((int16_t)Hbyte << 8) | Lbyte;
}

void requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(address, bytes);
}

void readArray(uint8_t *output, char size)
{
  for(char i = 0; i<size; i++)
  {
    output[i] = Wire.read();//read byte and put it into rawData table
  }
}

uint8_t read(uint8_t address, uint8_t subAddress)
{
  requestBytes(address,subAddress,1);//request one byte from the register
  uint8_t data = Wire.read();//read one byte of data
  return data;
}

void write(uint8_t address, uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void write_OR(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c | data;
  write(address,subAddress,c);
}

void write_AND(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c & data;
  write(address,subAddress,c);
}

void Hreset()
{
  write_OR(MPU_address,PWR_MGMT_1,1<<7);//set reset bit in PWR_MGMT_1 register
}

uint8_t testIMU()
{
  if(read(MPU_address,WHO_AM_I)==0xFF)
  {
    return 1;
  }
  return 0;
}

//test magnetometer
//Returns 0 if success, 1 if failure
uint8_t testMag()
{
  if(read(MAG_address,MAG_ID)==0xFF)
  {
    return 1;
  }
  return 0;
}

void read_acc()
{
  requestBytes(MPU_address, ACCEL_XOUT_H, 6);//request data from the accelerometer

  //read data
  uint8_t rawData[6];
  readArray(rawData,6);

  //store data in raw data variables
  ax = uint8ToUint16(rawData[1], rawData[0]);
  ay = uint8ToUint16(rawData[3], rawData[2]);
  az = uint8ToUint16(rawData[5], rawData[4]);
}

int initMpu()
{
  Hreset();
  write(MPU_address,CONFIG, 0x03); // set DLPF_CFG to 11
  write(MPU_address,SMPLRT_DIV, 0x00);// set prescaler sample rate to 0
  write(MPU_address,GYRO_CONFIG, 0x01);// set gyro to 3.6 KHz bandwidth, and 0.11 ms using FCHOICE bits
  write(MPU_address,INT_PIN_CFG, 0x02);// enable bypass
  write(MAG_address, CNTL, 0x16);//set magnetometer to read in mode 2 and enable 16 bit measurements

  //read magnetometer sensitivity
  mx_sensitivity = (((read(MAG_address, ASAX)-128)*0.5)/128)+1;
  my_sensitivity = (((read(MAG_address, ASAY)-128)*0.5)/128)+1;
  mz_sensitivity = (((read(MAG_address, ASAZ)-128)*0.5)/128)+1;

  //read factory gyroscope offset
  GX_offset = uint8ToUint16(read(MPU_address,XG_OFFSET_L), read(MPU_address,XG_OFFSET_H));
  GY_offset = uint8ToUint16(read(MPU_address,YG_OFFSET_L), read(MPU_address,YG_OFFSET_H));
  GZ_offset = uint8ToUint16(read(MPU_address,ZG_OFFSET_L), read(MPU_address,ZG_OFFSET_H));


  //Based on http://www.digikey.com/en/pdf/i/invensense/mpu-hardware-offset-registers .
  //read factory accelerometer offset

  //read the register values and save them as a 16 bit value
  AX_offset = (read(MPU_address,XA_OFFSET_H)<<8) | (read(MPU_address,XA_OFFSET_L));
  AY_offset = (read(MPU_address,YA_OFFSET_H)<<8) | (read(MPU_address,YA_OFFSET_L));
  AZ_offset = (read(MPU_address,ZA_OFFSET_H)<<8) | (read(MPU_address,ZA_OFFSET_L));
  //shift offset values to the right to remove the LSB
  AX_offset = AX_offset>>1;
  AY_offset = AY_offset>>1;
  AZ_offset = AZ_offset>>1;

  return (testIMU() || testMag());
}