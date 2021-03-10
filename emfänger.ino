#include <IRremote.h>

int IR_RECIVE_PIN = 10;
IRrecv irrecv(IR_RECIVE_PIN);
decode_results results;


void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn();
    irrecv.blink13(true);
}

void loop(){
    if (irrecv.decode()){
        // irrecv.printIRResultShort(&Serial);
        Serial.println(irrecv.decodedIRData.command);
        irrecv.resume();
    }
}
