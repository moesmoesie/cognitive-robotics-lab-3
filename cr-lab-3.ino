// Access the required libraries:
#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor rightMotor(9); 
MeDCMotor leftMotor(10);

MeLineFollower linefollower(2);

void applyPower(int power, int motor){
  power *= 2.55;
  switch(motor){
    case 0:
      rightMotor.run(power);
      leftMotor.run(-power);
      break;
    case 1:
      leftMotor.run(-power);
      break;
    case 2:
      rightMotor.run(power);
      break;
      
  }
}

int speed = 60;
int currentState = 3;
int previousState = 3;

void goRight(){
  Serial.print("Going Right");
  applyPower(speed, 2);
}

void goLeft(){
  Serial.print("Going Left");
  applyPower(speed, 1);
}

void goForward(){
  Serial.print("Going Forward");
  applyPower(speed, 0);
}

void goBack(){
  Serial.print("Going Back");
  applyPower(-speed, 0);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  currentState = linefollower.readSensors();
  switch(currentState){
    case 0:
      Serial.print(previousState);
      if(previousState == 1){
        goRight();
      }else if(previousState == 2){
        goLeft();
      }else if(previousState == 3){
        goBack();
      }
      break;
    case 1:
      previousState = currentState;
      goLeft();
      break;
    case 2:
       previousState = currentState;
      goRight();
      break;
    case 3:
      previousState = currentState;
      goForward();
  }
}
