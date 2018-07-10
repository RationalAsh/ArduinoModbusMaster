#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H
#include <Arduino.h>

#if defined (CORE_TEENSY)
#else
#include <avr/pgmspace.h>
#endif

#define MAX_BUF_SIZE 32

#define ST_IDLE 20
#define ST_RECV 30
#define ST_PROC 40

typedef uint16_t WORD;
// typedef uint8_t BYTE;

// Address defines
#define ADDR_BCAST 0x00

// Function codes
#define FUNC_READ_DISCRETE 2
#define FUNC_READ_COIL 1
#define FUNC_WRITE_COIL 5
#define FUNC_WRITE_MULTICOIL 15
#define FUNC_READ_INPUT 4
#define FUNC_READ_MULTIREG 3
#define FUNC_WRITE_REG 6
#define FUNC_WRITE_MULTIREG 16
#define FUNC_READ_ID 17

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

    uint16_t readHR(uint8_t slave_id, uint16_t reg_addr);
    void readMultipleHR(uint8_t slave_id, uint16_t start_addr, int num_regs, uint16_t *arr);
    void writeHR(uint8_t slave_id, uint16_t addr, uint16_t val);
    void writeMultipleHR(uint8_t slave_id, uint16_t start_addr, int num_regs, const uint16_t *data);

    private:
    Stream &ser;
    int DEN_;

    WORD CRC16 (const uint8_t *nData, WORD wLength);
    int encodeRTUFrame(const uint8_t *data, uint8_t dlen, uint8_t *frame, uint8_t slave_addr, uint8_t function_code);
    int decodeRTUFrame(const uint8_t *frame, WORD flen, uint8_t *data, uint8_t *slave_addr, uint8_t *function_code);
};


#endif