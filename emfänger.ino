#include <IRremote.h>

const int IR_RECIVE_PIN = 11;
int command;
IRrecv irrecv(IR_RECIVE_PIN);
decode_results results;
int bewegung[3];


void setup(){
    Serial.begin(9600);
    irrecv.enableIRIn();
}



int empfangen(){
    
    /*  dies funktion gibt ein array mit 2 Werten,
     *  die die Richtung und Geschwindigkeit reprässentieren,
     *  zurück
     *  bewegung = {Geschwidigkeit, Richtung}
     *  Bedeutung der Befehle
     *  0x0 stoppt das fahrzeug
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
    if (irrecv.decode()){
        command = irrecv.decodedIRData.command;
        
        switch (command){
            case 0x0:
                bewegung[0] = 0;
                bewegung[1] = 0;
                break; 
            case 0x1:
                bewegung[0] = 100;
                bewegung[1] = 0;
                break;
            case 0x2:
                bewegung[0] = 255;
                bewegung[1] = 0;
                break;
            case 0x3:
                bewegung[0] = 100;
                bewegung[1] = -20;
                break;
            case 0x4:
                bewegung[0] = 100;
                bewegung[1] = -45;
                break;
            case 0x5:
                bewegung[0] = -60;
                bewegung[1] = -20;
                break;
            case 0x6:
                bewegung[0] = -60;
                bewegung[1] = -45;
                break;
            case 0x7:
                bewegung[0] = 100;
                bewegung[1] = 20;
                break;
            case 0x8:
                bewegung[0] = 100;
                bewegung[1] = 45;
                break;
            case 0x9:
                bewegung[0] = -60;
                bewegung[1] = 20;
                break;
            case 0x10:
                bewegung[0] = -60;
                bewegung[1] = 45;
                break;
            case 0x11:
                bewegung[0] = -60;
                bewegung[1] = 0;
                break;
            case 0x12:
                bewegung[0] = -120;
                bewegung[1] = 0;
                break;
        }
        irrecv.resume();
    }
    return bewegung; 
}


void loop(){
    //if (irrecv.decode()){
        // irrecv.printIRResultShort(&Serial);
        //Serial.println(irrecv.decodedIRData.command);
        //irrecv.resume();
    
    //}
    Serial.println(empfangen())
    delay(50)
}
