#include <Servo.h> 
#include <IRremote.h>

//Pins Jaldyz
// Sensor Pins
//Sensor rechts(Spurhalten1)
const int IR_INPUT_PIN_RECHTS = A0;
const int IR_LED_PIN_RECHTS = 13;
int SENSOR_RECHTS[] = {IR_INPUT_PIN_RECHTS, IR_LED_PIN_RECHTS, -10};
//Sensor links(Spurhalten2)
const int IR_INPUT_PIN_LINKS = A1;
const int IR_LED_PIN_LINKS = 12;
int SENSOR_LINKS[] = {IR_INPUT_PIN_LINKS, IR_LED_PIN_LINKS, 10};
//Sensor Geswindgkeitserkennung(Farbcodes mit Ir Sensor)(auf Ampel erwiterbar)
const int IR_INPUT_PIN_MITTE = A2;
const int IR_LED_PIN_MITTE = 11;

//Variablen Jaldyz
int ambient = 0;
int lit = 0;
int value = 0;
int max_geschw = 255;

//Pins Roman
const int IR_INPUT_PIN = A1;
const int IR_LED_PIN = 10;
const int ECHO = 9;
const int TRIGGER = 8;

//Variablen Roman
long dauer=0;
long entfernung=0;

int fahren_start_zeit = 0;
int helligkeit;


//Pins Nico 
//motor  

int GSM2 = 5; 

int in3 = 7; 

int in4 = 6; 

// servo

const int SERVO_L_PIN = 4; 

Servo servo_l; 


//Pins Jonathan 
const int IR_RECIVE_PIN = 3;
int command;
IRrecv irrecv(IR_RECIVE_PIN); // legt fest an welchem pin das Singnal des Empfängers eingeht
decode_results results;
int bewegung[2];
bool parken;







void setup()
{   
    Serial.begin(9600); 
    
    
    //Setup Sensoren Jaldyz
    // Setup Sensoren
    pinMode(IR_INPUT_PIN_RECHTS, INPUT);
    pinMode(IR_LED_PIN_RECHTS, OUTPUT);
    pinMode(IR_INPUT_PIN_LINKS, INPUT);
    pinMode(IR_LED_PIN_LINKS, OUTPUT);
    pinMode(IR_INPUT_PIN_MITTE, INPUT);
    pinMode(IR_LED_PIN_MITTE, OUTPUT);

    //Setup Roman
    //Ultraschallsensor Setup 
    pinMode(TRIGGER, OUTPUT); 
    pinMode(ECHO, INPUT); 
  
    //IR Sensor Setup
    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);

    //Setup Nico
    servo_l.attach(SERVO_L_PIN); 

    pinMode(GSM2, OUTPUT); 

    pinMode(in3, OUTPUT); 

    pinMode(in4, OUTPUT); 


    //Setup Jonathan
    irrecv.enableIRIn();


}

int Spurhalten(int Sensor[]){//Jaldyz

    digitalWrite(Sensor[1], LOW);// LED aus
    delay(5);//To give ADC and LED transition time
    ambient = analogRead(Sensor[0]);//Umgebungs helligkeuit
  
    digitalWrite(Sensor[1], HIGH);
    delay(5);
    lit = analogRead(Sensor[1]);
  
    value = lit - ambient;
  
    if (value > 600 ){//Wenn weiße linie erkannt
    //Wert für weiß muss bestimmt werden 
        return Sensor[2];
    }
    else{
        return 0;
    }
}

int Geschwidigkeit_Erkennen(){//Jaldyz

    //liefert Wert für Helligkeit(je nach farbe anderer wert muss bestimmt werden )
    digitalWrite(IR_LED_PIN_MITTE, LOW);
    delay(5); 
    //misst umgebungshelligkeit                          
    ambient = analogRead(IR_INPUT_PIN_MITTE);
  
    digitalWrite(IR_LED_PIN_MITTE, HIGH);
    delay(5);
    lit = analogRead(IR_INPUT_PIN_MITTE);
    //differenz zum Umgebungslicht berechnen
    value = lit - ambient;

    //werte für farben und geschwindigkeitne (return werte müssen noch fesgelegt werden)
    //geschwidigkeiten werden als maimal geschawindigkeiten verwendet
    if (900 > value > 600){
        return 200;
    }
    else if(600 > value > 300){
        return 100;
    }
    else if (300 > value > 0){
        return 0;
    }
    else{
        return NULL;
    }
    
}

void fahren(int einschlag, int geschw){// Nico  //einschlag zwischen -45 für ganz links und 45 für ganz rechts 

    servo_l.write(45+einschlag); 
 

    if(geschw > 0){ 


        digitalWrite(in3, HIGH);  // Motor vorwärts 

        digitalWrite(in4, LOW); 

         //Geschwindigkeit vom Motor wird festgelegt 

        analogWrite(GSM2, abs(geschw)); 

    } 



    else if(geschw < 0){ 

        // Motor dreht sich rückwärts 

        

        digitalWrite(in3, LOW); 

        digitalWrite(in4, HIGH); 

        analogWrite(GSM2, abs(geschw)); 

    } 

    else if(geschw == 0){ 

        // beide Motoren halten an 
 
        digitalWrite(in3, LOW); 

        digitalWrite(in4, LOW); 

    } 

} 

int messen (){  //Roman
    // Funktion gibt enfernung als int zurück        
    //Töne(Ultraschall) and und aus machen 
    digitalWrite(TRIGGER, LOW);
    delay(5);
    digitalWrite(TRIGGER, HIGH); 
    delay(10);
    digitalWrite(TRIGGER, LOW);
    dauer = pulseIn(ECHO, HIGH); 
    entfernung = long((dauer/2) * 0.03432); 
    if (entfernung >= 500 || entfernung <= 0) {
        //ungültiger Messbereich
        Serial.println("Kein Messwert"); 
    }
    else 
    {
      Serial.print(entfernung); 
      Serial.println(" cm"); 
    }

    return entfernung;
 }


int markierungErkennen() { //Roman
    //liefert Wert für Helligkeit(schwarz => kleinerer Wert)
    digitalWrite(IR_LED_PIN, LOW);
    delay(5); 
    //misst umgebungshelligkeit                          
    ambient = analogRead(IR_INPUT_PIN);
  
    digitalWrite(IR_LED_PIN, HIGH);
    delay(5);
    lit = analogRead(IR_INPUT_PIN);
    //differenz zum Umgebungslicht berechnen
    value = lit - ambient;
    
    return value;
}

void einparken_s(int richtung){//Roman // richtung = -1 für links für rechts 1
    helligkeit = markierungErkennen();
    while (helligkeit < 300){ 
        fahren(0,70);
        helligkeit = markierungErkennen();

    while (helligkeit < 300){
        fahren(0,70);
        helligkeit = markierungErkennen();
    }
    fahren(45*richtung, -50);
    delay(3000);
    fahren(-45*richtung, -50);
    delay(3000);
    fahren(0, 50);
    delay(1000);

    }
    
}

void einparken_ruck(){ // Roman
    //nur rückwärts links falls Zeit rückwärts rechts hinzufügen
    //Auto soll Lücke erkennen, vorbei fahren, dann rückwärts einparken 
    //delays müssen auf das getriebe abgestimmt werden => Tests
    helligkeit = markierungErkennen();
    while (helligkeit > 300){//Wert für schwarz muss noch ermittelt werden
        //fahren bis Parklücke erkannt
        fahren(0, 50);
    }
    //Parklücke gefunden
    fahren(0,0);
    delay(100);
    //an Parklücke vorbei fahren
    fahren(0,100);
    delay(2000);
    //rückwärts einparken
    entfernung = messen();
    fahren_start_zeit = millis();
    while(entfernung > 10 && (fahren_start_zeit - millis()) < 2000){// fährt für 2 sec oder bis 10 cm vor Wand Rückwärts links (Zeit bis gerade in Parklücke)
        fahren(-45, -40);
    }

    fahren(0,0);
    delay(100);

    //rückwärtsfahren bis ganz in Parklücke
    while (entfernung > 10){
        fahren(0, -40);
    }
}

void empfangen(){
    
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
            case 0:
                bewegung[0] = 0;
                bewegung[1] = 0;
                break; 
            case 1:
                bewegung[0] = 200;
                bewegung[1] = 0;
                break;
            case 2:
                bewegung[0] = 255;
                bewegung[1] = 0;
                break;
            case 3:
                bewegung[0] = 200;
                bewegung[1] = -20;
                break;
            case 4:
                bewegung[0] = 2000;
                bewegung[1] = -45;
                break;
            case 5:
                bewegung[0] = -200;
                bewegung[1] = -20;
                break;
            case 6:
                bewegung[0] = -200;
                bewegung[1] = -45;
                break;
            case 7:
                bewegung[0] = 200;
                bewegung[1] = 20;
                break;
            case 8:
                bewegung[0] = 200;
                bewegung[1] = 45;
                break;
            case 9:
                bewegung[0] = -200;
                bewegung[1] = 20;
                break;
            case 16:
                bewegung[0] = -200;
                bewegung[1] = 45;
                break;
            case 17:
                bewegung[0] = -200;
                bewegung[1] = 0;
                break;
            case 18:
                bewegung[0] = -255;
                bewegung[1] = 0;
                break;
            case 19:
                parken = true;
                break;
        }
        irrecv.resume();
    } 
}


void loop(){
    empfangen();
    if (parken == true){
        einparken_s(1);
    }
    else{
        empfangen();
        int einschlag = bewegung[1];
        int geschwindigkeit = bewegung[0];
        int new_max = Geschwidigkeit_Erkennen();
        if(new_max != NULL){
            int max_geschw = new_max;
        }
        if (geschwindigkeit > max_geschw){
            geschwindigkeit = max_geschw;
        }
        int anpassung = Spurhalten(SENSOR_RECHTS);
        if (anpassung == 0){
            anpassung = Spurhalten(SENSOR_LINKS);
        }
        einschlag = einschlag + anpassung;
        fahren(einschlag ,geschwindigkeit);
        }
}
