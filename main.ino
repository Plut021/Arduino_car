#include <AFMotor.h>
#include <Servo.h> 

int tasterstatus = 0;
int stick_wert = 0;
int stick_x = A0;
int stick_y = A1;
int x_value;
int y_value;
int speed = 0;
int rotation;
int stop_button = 3;
int servo1_pin = 9;
int servo2_pin = 10;

AF_DCMotor motor1(1); //Antrieb(vorne und hinten oder 2 hinten)
AF_DCMotor motor2(2);
Servo servo1;//Lenkung(linkes und rechtes Rad je ein Motor zum lenken)
Servo servo2;


void setup()
{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    servo1.write(90); // set servo to mid
    servo2.write(90); 
}

void drive()// fortbewegung des fahrzeugs
{
	bool driving = true;
    while(driving)
    {
    	x_value = analogRead(stick_x);
      	y_value = analogread(stick_y);
      	
      	if(y_value > 512 && speed <= 255) // nach vorne fahren
        {
        	speed++;
            delay(10);
            motor1.setSpeed(speed);
            motor1.run(FORWARD);
            motor2.setSpeed(speed);
            motor2.run(FORWARD);
        }

        if(y_value > 512 && speed <= 80)  //rückwärts fahren
        {
            speed = 0;
            speed++;
            delay(20);
            motor1.setSpeed(speed);
            motor1.run(BACKWARD);
            motor2.setSpeed(speed);
            motor2.run(BACKWARD);
        }

        if(x_value < 512 && servo1.read() > 45) //rechts lenken
        {
            
        }

        if(x_value < 512 && servo1.read() < 135) //links lenken 
        {

        }

        if(y_value == 512)// hält das auto an(keine Bremsfunktion)
        {
            motor1.run(RELEASE);
            motor2.run(RELEASE);
        }

        if(digitalRead(stop_button) == HIGH) // stopt den driving loob enspricht Auto aus
        {
            driving = false;
        }
    }
}

void loop()
{
    drive();
}
