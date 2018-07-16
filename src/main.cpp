#include <Arduino.h>
#include "modbusMaster.h"

int send_output = 0;
uint16_t data[1] = {1};
uint16_t input_data[3] = {0};
modbusMaster master(Serial1);
int ledState = 0;

void setup() {
    // put your setup code here, to run once:
    master.begin(115200, 1);
    Serial.begin(115200);
    Serial1.begin(115200); 
    pinMode(13, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    //Serial1.print("Hello World!");
    //Serial1.println(ledState);
    send_output = master.readMultipleHR(2,6,3,input_data);

    data[0] ^= 1;
    // Serial.println(send_output);
    if(send_output == 0) {
        // Serial.print("Send successful\n");
        Serial.print(input_data[0], HEX);
        Serial.print(" ");
        Serial.print(input_data[1], HEX);
        Serial.print(" ");
        Serial.println(input_data[2], HEX);
        send_output = -1;
    } else {
        Serial.print("Send no successful\n");
    }
    // // Serial1.write("hello world\n");
    digitalWrite(13, ledState);
    ledState ^= 1;
    delay(500);
}