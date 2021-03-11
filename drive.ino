#include <AFMotor.h>


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
}

void drive(int speed) {
    motor1.setSpeed(speed); // abs(speed) anstatt speed wenn negativ forward != backward
    motor2.setSpeed(speed);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    
/*    wenn negativ != backwards 
      
    if(speed > 0) {
        motor1.run(FORWARD);
        motor2.run(FORWARD);
    }
    else if(speed < 0) {
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);  
    }*/     
}



void halt() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
}



void loop() {
    drive(150);
    delay(10000);
    halt();
    drive(-60);
    delay(8000);
    halt();
}
