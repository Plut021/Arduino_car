#include <IRremote.h>


const int IR_SEND = 3;
const int STICK_X = A0;
const int STICK_Y = A1;
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
uint8_t command;



const uint16_t ADRESS = 0x102;
const uint8_t REPEATS = 0;

// funktion wird verwendet wenn 32 bit zahlen übertragen werden können
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
    Serial.println(komplett);
    Serial.println(msg_hex);
    

    
    IrSender.sendRC5(ADRESS, msg_hex, REPEATS);
}

//wenn direkte werte übertragungs probleme verursachen 
void sending2(){
    /* 
     *  0x1 langsam vorwärts
     *  0x2 schnell vorwärts
     *  0x3 leicht links lenken vorwärts
     *  0x4 stark links lenken vorwärts
     *  0x5 leicht links lenken rückwarts
     *  0x6 stark links lenken rückwärts
     *  0x7 leicht rechts lenken vorwärts 
     *  0x8 stark rechts lenken vorwärts
     *  0x9 leicht rechts lenken rückwärts
     *  0x10 stark rechts lenken rückwärts
     *  0x11 sehr langsam rückwärts
     *  0x12 langsam rückwärts
     */
    x_val = analogRead(STICK_X);
    y_val = analogRead(STICK_Y);    
    if(900 > x_val > 600 && 400 < y_val < 600){
        command = 0x1;
    }
    
    else if(x_val > 900 && 400 < y_val < 600){
        command = 0x2;
    }

    else if(250 < y_val < 400 && x_val < 511){
        command = 0x3;
    }

    else if(y_val < 250 && x_val < 511){
        command = 0x4;
    }
    
    else if(250 < y_val < 400 && x_val > 511){
        command = 0x5;
    }

    else if(y_val < 250 && x_val > 511){
        command = 0x6;
    }

    else if(850 > y_val > 600 && x_val < 511){
        command = 0x7;
    }
    
    else if(y_val > 850 && x_val < 511){
        command = 0x8;
    }

    else if(850 > y_val > 600 && x_val > 511){
        command = 0x9;
    }
    
    else if(y_val > 850 && x_val > 511){
        command = 0x10;
    }
   
    else if(250 < x_val < 400 && 400 < y_val < 600){
        command = 0x11; 
    }

    else if(x_val < 250 && 400 < y_val < 600){
        command = 0x12;
    }

    IrSender.sendRC5(ADRESS, command, REPEATS);
}

void setup(){
    IrSender.begin(IR_SEND,false);
    Serial.begin(9600);

}

void loop() {
    sending();
    delay(1000);
    Serial.println("sending done");
    
}
