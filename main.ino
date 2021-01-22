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


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
Servo servo1;


void setup()
{
    motor.run(RELEASE);
}

void drive()
{
	bool driving = True;
    while(driving)
    {
    	x_value = analogRead(stick_x);
      	y_value = analogread(stick_y);
      	
      	if(y_value > 512 && speed =< 255)
        {
        	speed++;
            delay(10);
            motor1.setSpeed(speed);
            motor1.run(FORWARD);
            motor2.setSpeed(speed);
            motor2.run(FORWARD);
        }

        if(y_value < 512 && speed =< 80)  //moving backwards
        {
            speed = 0;
            spped++;
            delay(20);
            motor1.setSpeed(speed);
            motor1.run(BACKWARD);
            motor2.setSpeed(speed);
            motor2.run(BACKWARD);
        }

        if(x_value > 512 && ) //turn right
        {
            
        }

        if(x_value < 512) //turn left
        {

        }

        if(y_value == 512)
        {
            motor1.run(RELEASE);
            motor2.run(RELEASE);
        }

        if(digitalRead(stop_button) == HIGH)
        {
            driving = false;
            
        }
    }
}

void loop()
{
    drive();
}
