
#ifndef TwoWire_h
#define TwoWire_h

#define PSDA 21
#define PSCL 22

#include <esp32-hal.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "Stream.h"

#define STICKBREAKER V0.2.2
#define I2C_BUFFER_LENGTH 128
typedef void(*user_onRequest)(void);
typedef void(*user_onReceive)(uint8_t*, int);

class TwoWire: public Stream
{
protected:
    uint8_t num;
    int8_t sda;
    int8_t scl;
    i2c_t * i2c;

    uint8_t rxBuffer[I2C_BUFFER_LENGTH];
    uint16_t rxIndex;
    uint16_t rxLength;
    uint16_t rxQueued; //@stickBreaker

    uint8_t txBuffer[I2C_BUFFER_LENGTH];
    uint16_t txIndex;
    uint16_t txLength;
    uint16_t txAddress;
    uint16_t txQueued; //@stickbreaker

    uint8_t transmitting;
    /* slave Mode, not yet Stickbreaker
            static user_onRequest uReq[2];
            static user_onReceive uRcv[2];
        void onRequestService(void);
        void onReceiveService(uint8_t*, int);
    */
    i2c_err_t last_error; // @stickBreaker from esp32-hal-i2c.h
    uint16_t _timeOutMillis;

public:
    TwoWire(uint8_t bus_num);
    ~TwoWire();
    void begin(int sda=PSDA, int scl=PSCL, uint32_t frequency=0);

    void setClock(uint32_t frequency); // change bus clock without initing hardware
    size_t getClock(); // current bus clock rate in hz

    void setTimeOut(uint16_t timeOutMillis);
    uint16_t getTimeOut();

    uint8_t lastError();
    char * getErrorText(uint8_t err);

    //@stickBreaker for big blocks and ISR model
    i2c_err_t writeTransmission(uint16_t address, uint8_t* buff, uint16_t size, bool sendStop=true);
    i2c_err_t readTransmission(uint16_t address, uint8_t* buff, uint16_t size, bool sendStop=true, uint32_t *readCount=NULL);

    void beginTransmission(uint16_t address);
    void beginTransmission(uint8_t address);
    void beginTransmission(int address);

    uint8_t endTransmission(bool sendStop);
    uint8_t endTransmission(uint8_t sendStop);
    uint8_t endTransmission(void);

    uint8_t requestFrom(uint16_t address, uint8_t size, bool sendStop);
    uint8_t requestFrom(uint16_t address, uint8_t size, uint8_t sendStop);
    uint8_t requestFrom(uint16_t address, uint8_t size);
    uint8_t requestFrom(uint8_t address, uint8_t size, uint8_t sendStop);
    uint8_t requestFrom(uint8_t address, uint8_t size);
    uint8_t requestFrom(int address, int size, int sendStop);
    uint8_t requestFrom(int address, int size);

    size_t write(uint8_t);
    size_t write(const uint8_t *, size_t);
    int available(void);
    int read(void);
    int peek(void);
    void flush(void);

    inline size_t write(const char * s)
    {
        return write((uint8_t*) s, strlen(s));
    }
    inline size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t)n);
    }

    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );

    void dumpInts();
    void dumpI2C();
};

extern TwoWire Wire;
extern TwoWire Wire1;


/*
V0.2.2 13APR2018 preserve custom SCL,SDA,Frequency when no parameters passed to begin()
V0.2.1 15MAR2018 Hardware reset, Glitch prevention, adding destructor for second i2c testing
*/
#endif
