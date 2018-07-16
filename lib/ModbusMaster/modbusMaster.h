#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H
#include <Arduino.h>

#if defined (CORE_TEENSY)
#else
#include <avr/pgmspace.h>
#endif

#define MAX_BUF_SIZE 64

#define ST_WRIT  10
#define ST_IDLE  20
#define ST_RECV  30
#define ST_PROC  40

typedef uint16_t WORD;
// typedef uint8_t BYTE;

// Address defines
static const uint8_t ADDR_BCAST = 0x00;

// Function codes
static const uint8_t FUNC_READ_DISCRETE = 2;
static const uint8_t FUNC_READ_COIL = 1;
static const uint8_t FUNC_WRITE_COIL = 5;
static const uint8_t FUNC_WRITE_MULTICOIL = 15;
static const uint8_t FUNC_READ_INPUT = 4;
static const uint8_t FUNC_READ_MULTIREG = 3;
static const uint8_t FUNC_WRITE_REG = 6;
static const uint8_t FUNC_WRITE_MULTIREG = 16;
static const uint8_t FUNC_READ_ID = 17;

// Define some errors
#define EINVADDR -1
#define ECRCFAIL -2

// Define dev types
#define DEV_MASTER
#define DEV_SLAVE

#define DEFAULT_SADDR 1

typedef uint16_t WORD;

class modbusMaster
{
    public:
    modbusMaster(Stream &s=Serial):ser(s){}
    void begin(int baud, int DEN);
    
    void broadcast(uint8_t *data, int dlen);
    int readHR(uint8_t slave_id, uint16_t start_addr, uint16_t *data);
    int readMultipleHR(uint8_t slave_id, uint16_t start_addr, uint16_t num_regs, uint16_t *data);
    int writeHR(uint8_t slave_id, uint16_t start_addr, uint16_t data);
    int writeMultipleHR(uint8_t slave_id, uint16_t start_addr, uint16_t num_regs, const uint16_t *data);

    private:
    Stream &ser;
    int DEN_;
    uint8_t recv_buf[MAX_BUF_SIZE];
    uint8_t send_buf[MAX_BUF_SIZE];
    uint8_t data_buf[MAX_BUF_SIZE]; 
    unsigned long _baud;
    float byte_time;
    unsigned long t15;
    unsigned long t35;
    uint8_t sa_recv;
    uint8_t fcode;
    WORD bytes_read;

    WORD CRC16 (const uint8_t *nData, WORD wLength);
    int encodeRTUFrame(const uint8_t *data, uint8_t dlen, uint8_t *frame, uint8_t slave_addr, uint8_t function_code);
    int decodeRTUFrame(const uint8_t *frame, WORD flen, uint8_t *data, uint8_t *slave_addr, uint8_t *function_code);
};


#endif