#include <IRremote.h>

int FREQUENZE = 30; // in  kHz
int IR_RECIVE_PIN = 10;
int STICK_X = A0;
int STICK_Y = A1;
int x_val;
int y_val;


uint16_t ADRESS = 0x102;
uint8_t REPEATS = 0;


void Send (uint8_t Command){
    IrSender.sendRC6(ADRESS, Command, REPEATS);
}

void setup(){
    Serial.begin(9600);

}

void loop() {
    Serial.print("start");
    x_val = analogRead(STICK_X);
    y_val = analogRead(STICK_Y);
    Serial.print(x_val, y_val);
}
