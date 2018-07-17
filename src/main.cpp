#include <Arduino.h>
#include "modbusMaster.h"

int send_output = 0;
uint16_t output_data[1] = {0x123D};
uint16_t input_data[10] = {0};
modbusMaster *master;
int ledState = 0;

void setup() {
    // put your setup code here, to run once:

    modbusMaster tmpobj(Serial1);
    master = &tmpobj;
    master->begin(115200, 1); 
   
    Serial.begin(9600);
    Serial1.begin(115200);

    pinMode(13, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:

    // send_output = master->writeMultipleHR(2,10,1,output_data);
    send_output = master->readMultipleHR(2,6,3,input_data);
    // Serial1.println("Hello");

    // Serial.println(send_output);
    if(send_output == 0) {
        Serial.print("Send successful\n");
        // Serial.print(input_data[0], HEX);
        // Serial.print(" ");
        // Serial.print(input_data[1], HEX);
        // Serial.print(" ");
        // Serial.println(input_data[2], HEX);
        send_output = -1;
    } else {
        Serial.print("Send no successful\n");
    }
    // // Serial1.write("hello world\n");

    // Serial.println("Hello world\n");
    digitalWrite(13, ledState);
    ledState ^= 1;
    delay(1000);
}