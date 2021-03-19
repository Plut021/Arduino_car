  
#include <IRremote.h>

const int IR_RECIVE_PIN = 11;
int com;
IRrecv irrecv(IR_RECIVE_PIN);
decode_results results;


void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn();
    irrecv.blink13(true);
}


int empfangen(){
    if (irrecv.decode()){
        com = irrecv.decodeIRData.command;
        


        //return com;  verwenden wenn einzelen comandos übergeben(nicht x und y wert des sticks
    }
}




void loop(){
    if (irrecv.decode()){
        // irrecv.printIRResultShort(&Serial);
        Serial.println(irrecv.decodedIRData.command);
        irrecv.resume();
    }
}
