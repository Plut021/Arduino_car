#include <IRremote.h>


int IR_SEND_PIN = 10;
int STICK_X = A0;
int STICK_Y = A1;
int x_val;
int y_val;


uint16_t ADRESS = 0x102;
uint8_t REPEATS = 0;


void sending (uint8_t Command){
    //x_val = analogRead(STICK_X);
    //y_val = analogRead(STICK_Y);
    
    IrSender.sendRC6(ADRESS, Command, REPEATS);
}

void setup(){
    IrSender.begin(IR_SEND_PIN);
    Serial.begin(9600);

}

void loop() {
    sending(0x15)
    delay(1000)
    Serial.println("sending done")
    
}
