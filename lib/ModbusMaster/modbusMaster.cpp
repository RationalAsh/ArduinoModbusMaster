#include "modbusMaster.h"

#if defined (CORE_TEENSY)
WORD modbusMaster::CRC16 (const uint8_t *nData, WORD wLength)
{
    static const WORD wCRCTable[] = {
       0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
       0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
       0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
       0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
       0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
       0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
       0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
       0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
       0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
       0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
       0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
       0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
       0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
       0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
       0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
       0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
       0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
       0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
       0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
       0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
       0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
       0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
       0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
       0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
       0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
       0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
       0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
       0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
       0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
       0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
       0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
       0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

    uint8_t nTemp;
    WORD wCRCWord = 0xFFFF;

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord  ^= wCRCTable[nTemp];
    }
    return wCRCWord;
} // End: CRC16

#else

WORD modbusMaster::CRC16 (const uint8_t *nData, WORD wLength)
{
    static const WORD wCRCTable[] PROGMEM = {
       0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
       0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
       0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
       0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
       0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
       0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
       0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
       0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
       0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
       0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
       0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
       0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
       0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
       0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
       0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
       0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
       0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
       0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
       0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
       0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
       0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
       0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
       0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
       0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
       0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
       0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
       0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
       0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
       0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
       0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
       0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
       0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

    uint8_t nTemp;
    WORD wCRCWord = 0xFFFF;

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        WORD wCRCTableVal = pgm_read_word_near(&(wCRCTable[nTemp]));
        //wCRCWord  ^= wCRCTable[nTemp];
        wCRCWord  ^= wCRCTableVal;
    }
    return wCRCWord;
} // End: CRC16

#endif

int modbusMaster::readMultipleHR(uint8_t slave_id, uint16_t start_addr, uint16_t num_regs, uint16_t *data) {
    const uint16_t slave_id_len = 1;
    const uint16_t fcode_len = 1;
    const uint16_t start_addr_len = 2;
    const uint16_t num_regs_len = 2;
    const uint16_t crc_len = 2;
    int ctr;

    data_buf[0] = start_addr >> 8; 
    data_buf[1] = start_addr & 0xFF;
    data_buf[2] = num_regs >> 8;
    data_buf[3] = num_regs & 0xFF;
    static int8_t state = ST_IDLE;
    int encode = encodeRTUFrame(data_buf, start_addr_len+num_regs_len, send_buf, slave_id, FUNC_READ_MULTIREG);
    int output = -1;

    if (encode == 0) {
        state = ST_WRIT;
        uint16_t send_buf_len = slave_id_len + fcode_len + start_addr_len + num_regs_len + crc_len;
        for(uint16_t i=0; i < send_buf_len; i++) {
            ser.write(send_buf[i]);
            ser.flush();
            Serial.print(send_buf[i], HEX);
            Serial.print(" ");
        }
        Serial.print("\n");
        state = ST_IDLE;

        delayMicroseconds(100);
        // Bytes available to read
        if ( ser.available() > 0 )
        {
            state = ST_RECV;
            ctr = 0;
            sa_recv = 0;
            fcode = 0;
            bytes_read = 0;
        } else {
            Serial.println("No packet received");
        }

        while (state == ST_RECV)
        {
            if(ser.available())
            {
                recv_buf[ctr++] = ser.read();
            }
            else
            {
                // Wait for a bit
                delayMicroseconds(t15);
                // If serial is still not available
                if( ser.available() == 0 )
                {
                    //Transmission has ended
                    for (int i = 0; i < ctr; i++) {
                        Serial.print(recv_buf[i], HEX);
                        Serial.print(" ");
                    }
                    Serial.println();
                    state = ST_PROC;
                    bytes_read = ctr;
                }
            }
        }

        if ( state == ST_PROC )
        {
            Serial.println("in ST_PROC");
            // Process the request in the incoming message.
            int ret = decodeRTUFrame(recv_buf, bytes_read, data_buf, &sa_recv, &fcode);

            // If frame decoding was successful
            if(ret >= 0)
            {
                Serial.print("slave id = ");
                Serial.println(slave_id);
                if ( sa_recv != slave_id )
                {
                    // Ignore the message
                    state = ST_IDLE;
                }
                else
                {
                    Serial.println(fcode, HEX);
                    if(fcode == FUNC_READ_MULTIREG) {
                        Serial.print("in fcode\n");
                            uint16_t byte_count;
                            byte_count = data_buf[1] | (data_buf[0] << 8);
                            for(int i = 0; i < byte_count/2; i++) {
                                data[i] = data_buf[i*2+3] | (data_buf[i*2+2] << 8);
                            }
                            if(byte_count == num_regs * 2);
                                output = 0;
                    }
                    state = ST_IDLE;
                }
            }
            else
            {
                Serial.print("Error decoding frame. Code: ");
                Serial.println(ret);
                state = ST_IDLE;
            }
        }
    }
    return output;
}

int modbusMaster::writeMultipleHR(uint8_t slave_id, uint16_t start_addr, uint16_t num_regs, const uint16_t *data) {
    const uint16_t slave_id_len = 1;
    const uint16_t fcode_len = 1;
    const uint16_t start_addr_len = 2;
    const uint16_t byte_count_len = 1;
    const uint16_t num_regs_len = 2;
    const uint16_t crc_len = 2;
    data_buf[0] = start_addr >> 8; 
    data_buf[1] = start_addr & 0xFF;
    data_buf[2] = num_regs >> 8;
    data_buf[3] = num_regs & 0xFF;
    data_buf[4] = num_regs*2;
    for(int i = 0; i < num_regs; i++) {
        data_buf[2*i+5] = data[i] >> 8;
        data_buf[2*i+6] = data[i] & 0xFF;
    }  
    static int8_t state = ST_IDLE;
    int encode = encodeRTUFrame(data_buf, start_addr_len + num_regs_len + num_regs*2 + byte_count_len, send_buf, slave_id, FUNC_WRITE_MULTIREG);
    int output = -1;
    uint16_t send_buf_len = slave_id_len + fcode_len + start_addr_len + num_regs_len + num_regs*2 + byte_count_len + crc_len;
    if (encode == 0) {
        int ctr;
        state = ST_WRIT;

        for(uint16_t i=0; i<(uint16_t)send_buf_len; i++) {
            ser.write(send_buf[i]);
            ser.flush();
            // Serial.print(send_buf[i], HEX);
            // Serial.print(" ");
        }
        // Serial.println("");
        // Serial.println("encoded\n");
        state = ST_IDLE;

        delayMicroseconds(100);
        // Bytes available to read
        if ( ser.available() > 0 )
        {
            Serial.println("message received\n");
            state = ST_RECV;
            ctr = 0;
            sa_recv = 0;
            fcode = 0;
            bytes_read = 0;
        } else { 
            Serial.println("Error");
        }

        while (state == ST_RECV)
        {
            if(ser.available())
            {
                recv_buf[ctr++] = ser.read();
            }
            else
            {
                // Wait for a bit
                delayMicroseconds(t15);
                // If serial is still not available
                if( ser.available() == 0 )
                {
                    //Transmission has ended
                    state = ST_PROC;
                    bytes_read = ctr;
                }
            }
        }

        if ( state == ST_PROC )
        {
            // Process the request in the incoming message.
            int ret = decodeRTUFrame(recv_buf, bytes_read, data_buf, &sa_recv, &fcode);

            // If frame decoding was successful
            if(ret >= 0)
            {
                if ( sa_recv != slave_id )
                {
                    // Ignore the message
                    state = ST_IDLE;
                }
                else
                {
                    if(fcode == FUNC_WRITE_MULTIREG ) {
                            uint16_t start;
                            uint16_t regs_read;
                            start = data_buf[1] | (data_buf[0] << 8);
                            regs_read = data_buf[3] | (data_buf[2] << 8);
                            if (start == start_addr && regs_read == num_regs) {
                                output = 0;
                            }
                    }
                    state = ST_IDLE;
                }
            }
            else
            {
                Serial.print("Error decoding frame. Code: ");
                Serial.println(ret);
                state = ST_IDLE;
            }
        }
    }
    return output;
}

int modbusMaster::encodeRTUFrame(const uint8_t *data, uint8_t dlen, uint8_t *frame, uint8_t slave_addr, uint8_t function_code)
{
    // Check address for rule violations
    if ((slave_addr >= 248)) return EINVADDR;

    // Address and function codes and data length
    frame[0] = slave_addr;
    frame[1] = function_code;

    // Fill up data
    WORD i;
    for (i=2; i<dlen+2; i++)
        frame[i] = data[i-2];

    // Generate CRC
    WORD crc_val = CRC16(frame, dlen+2);
    //cout << "Generated CRC: " << crc_val << endl;
    frame[i] = crc_val & 0xFF;
    frame[i+1] = (crc_val >> 8) & 0xFF;

    return 0;
}

int modbusMaster::decodeRTUFrame(const uint8_t *frame, WORD flen, uint8_t *data, uint8_t *slave_addr, uint8_t *function_code)
{
    // First check CRC
    WORD crc_val = CRC16(frame, flen-2);
    WORD crc_incoming = (frame[flen-1] << 8) | (frame[flen-2]);

    // Serial.print("Frame: ");
    // for(int j=0; j<flen; j++)
    // {
    //     Serial.print(frame[j], HEX);
    //     Serial.print(" ");
    // }
    // Serial.println();
    // Serial.print("CRC (old): ");
    // Serial.print(crc_incoming, HEX);
    // Serial.print("  CRC (new): ");
    // Serial.println(crc_val, HEX);

    //cout << "CRC (old): " << crc_val << "; CRC (new): " << crc_incoming << endl;

    if(crc_incoming != crc_val) return ECRCFAIL;

    // Then check for valid address
    if (((*slave_addr) >= 248)) return EINVADDR;

    //cout << "CRC Pass." << endl;

    // If CRC check passed
    *slave_addr = frame[0];
    *function_code = frame[1];

    WORD i;
    for(i=2; i<flen-2; i++)
        data[i-2] = frame[i];

    return 0;
}

void modbusMaster::begin(int baud, int den)
{
    DEN_ = den;

    // Set DEN pin to output
    pinMode(DEN_, OUTPUT);
    // Set it to receiving mode (default)
    digitalWrite(DEN_, LOW);
    _baud = baud;
    byte_time = (1.0e6)/baud;
    t15 = (unsigned long) (byte_time*2);
    t35 = (unsigned long) (byte_time*4);
}

void modbusMaster::broadcast(uint8_t *data, int dlen)
{

}