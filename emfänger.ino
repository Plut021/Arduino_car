#include <IRremote.h>

int IR_RECIVE_PIN = 10;

void setup(){
    IrReciver.begin(IR_RECIVE_PIN);
    Serial.begin(9600);
}

void emfangen(){
    if (IrReciver.decode()){
        IrReciver.printIRResultShort(&Serial);
        IrReciver.resume();
    }
    
    if (IrReceiver.decodedIRData.command == 0x10) {
        return 
    }
    
    else if (IrReceiver.decodedIRData.command == 0x11){
        return
    }
}
