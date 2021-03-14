#include <IRremote.h>


int IR_SEND = 3;
int STICK_X = A0;
int STICK_Y = A1;
int x_val;
int y_val;
String komplett;
String x_pos;
String y_pos;
int msg;
String zero = "0";
String add;
uint8_t msg_hex;
String komplett_hex;



uint16_t ADRESS = 0x102;
uint8_t REPEATS = 0;


void sending (){
    //x_val = analogRead(STICK_X);
    //y_val = analogRead(STICK_Y);
    x_val = 1563;
    y_val = 5655;
    x_pos = String(x_pos);
    y_pos = String(y_pos);
    add = "";
    if(x_pos.length() < 4){
        for(int i = 0; i < 4 - x_pos.length(); i++){
            add += zero;
        }
        x_pos = add + x_pos;
    }
    add = "";
    if(y_pos.length() < 4){
        for(int i = 0; i < 4 - y_pos.length(); i++){
            add += zero;
        }
        y_pos = add + y_pos;
    }
    
    String komplett = x_pos + y_pos;
    komplett_hex = String(komplett.toInt(), HEX);
    msg_hex = komplett_hex.toInt();
    Serial.println(msg_hex);
    

    
    IrSender.sendRC5(ADRESS, msg_hex, REPEATS);
}

void setup(){
    IrSender.begin(IR_SEND);
    Serial.begin(9600);

}

void loop() {
    sending();
    delay(1000);
    Serial.println("sending done");
    
}

