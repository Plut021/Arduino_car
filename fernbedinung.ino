#include <IRremote.h>


const int IR_SEND = 3;
const int STICK_X = A0;
const int STICK_Y = A1;
const int STICK_TASTER = 7;

//Speichert die Position des Sticks 
int x_val;
int y_val;
uint8_t command; // Speichert den Befhl je nach Stickposition 
//uint8_t steht für eine Positive Ganzzahl im bereich von 0 bis 255 das 
//u steht für unsigned d.h alle zahlen die gespeichert werden können sind positiv
//das 8_t steht für eine größe von 8bit


// Adresse wird beim Senden mitgegeben um die Quelle des Signals überprüfen zu können 
// Überprüfung wird hier nicht verwendet, da nur von einem Sender/Fernbedinung ausgegangen wird
// Repeats ist Stadartwert für wiederholte Sendungen wird hier nicht benötigt daher = 0
const uint16_t ADRESS = 0x102; // kann wilkürlichfestgelegt werden
const uint8_t REPEATS = 0;

void setup(){
    pinMode(STICK_X, INPUT);
    pinMode(STICK_Y, INPUT);
    pinMode(STICK_TASTER, INPUT_PULLUP);
  
    IrSender.begin(IR_SEND,false); //Started den Sender false steht für den status einer kontroll LED die hier nicht verwendet wird
    Serial.begin(9600);

}



void sending2(){
    /* 
     *  funktion sendet je nach position des Sticks
     *  einen bestimmten Befehl der dann vom Auto in 
     *  eine Bewgung umgewandelt
     *  0x0 stopp
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
     *  0x13 einparken starten
     */
    x_val = analogRead(STICK_X);
    y_val = analogRead(STICK_Y);
    // Wenn der Stick nicht hinenigedrückt wird der Befehl für die jeweilige Position des Sticks gesendet
    // Wenn der Stick gedrückt wird wird der Befehl zum einParken gesendet
    if(digitalRead(STICK_TASTER)==1){
        if (x_val > 400 && y_val > 400 && x_val < 600 && y_val < 600){
            command = 0x0;
        }
        if(x_val > 600 && y_val < 600 && x_val < 900 && y_val > 400){
            command = 0x1;
        }
        
        else if(x_val > 900 && y_val < 600 && y_val > 400){
            command = 0x2;
        }

        else if(y_val < 400 && x_val < 400 && y_val >250){
            command = 0x3;
        }

        else if(y_val < 250 && x_val < 511){
            command = 0x4;
        }
        
        else if(y_val < 400 && x_val > 511 && y_val > 250){
            command = 0x5;
        }

        else if(y_val < 250 && x_val > 511){
            command = 0x6;
        }

        else if(y_val > 600 && x_val < 511 && y_val < 850){
            command = 0x7;
        }
        
        else if(y_val > 850 && x_val < 511){
            command = 0x8;
        }

        else if(y_val > 600 && x_val > 511 && y_val < 850){
            command = 0x9;
        }
        
        else if(y_val > 850 && x_val > 511){
            command = 0x10;
        }
    
        else if(x_val < 400 && y_val < 600 && x_val > 250 && y_val > 400){
            command = 0x11; 
        }

        else if(x_val < 250 && 400 < y_val < 600){
            command = 0x12;
        }
    }
    else{
      command = 0x13;
    }
    IrSender.sendRC5(ADRESS, command, REPEATS);// Sendet einen Befehl mit dem RC5 Protokoll
}


void loop() {
    sending2();
    delay(1000);
    Serial.println("sending done");
    Serial.println(command);
    
}
