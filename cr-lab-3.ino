// Access the required libraries:
#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor rightMotor(10); 
MeDCMotor leftMotor(9);

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

int speed = 50;
int currentState = 3;

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
      goBack();
      break;
    case 1:
      goLeft();
      break;
    case 2:
      goRight();
      break;
    case 3:
      goForward();
  }
}
