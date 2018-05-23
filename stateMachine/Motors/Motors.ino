#include <AccelStepper.h>
#include <ByteTransfer.h>

const int motorAPin1 = 2;
const int motorAPin2 = 3;
const int motorAPin3 = 4;
const int motorAPin4 = 5;
const int motorBPin1 = 6;
const int motorBPin2 = 7;
const int motorBPin3 = 8;
const int motorBPin4 = 9;

// initialize the stepper library:
AccelStepper stepperR(AccelStepper::FULL4WIRE, motorAPin1, motorAPin3, motorAPin2, motorAPin4);
AccelStepper stepperL(AccelStepper::FULL4WIRE, motorBPin1, motorBPin3, motorBPin2, motorBPin4);

const int stepsPrFullTurn = 3000;

const int inPin = 11;
const int dataPin = 12;
const int outPin = 13;

uint8_t outData;
boolean waitingToWrite;
boolean leftMovingTo;
boolean rightMovingTo;

bool sendByte(uint8_t data)
{
  if(waitingToWrite) return false;
  outData = data;
  waitingToWrite = true;
  return true;
}

const int SPEED = 150;
const float deccelerateSpeed = -0.5;
void OnDataIn(uint8_t data)
{
  Serial.println(data);
  switch(data) {
        case 1:
          goStraight();
          sendByte(0);
          break;
        case 2:
          turnRight();
          sendByte(0);
          break;
        case 3:
          turnLeft();
          sendByte(0);
          break;
        case 4:
          turnLeft90deg();
          break;
        case 5:
          turnRight90deg();
          break;
        case 6:
          stopMotors();
          break;
        default:
          stepperL.setSpeed(0);
          stepperR.setSpeed(0);
//          sendByte(1);
          break;
      }
}

bool OnDataOut(uint8_t &data)
{
  if(waitingToWrite)
  {
    data = outData;
    waitingToWrite = false;
    return true;
  }
  return false;
}



ByteTransfer bt(inPin, dataPin, outPin, OnDataIn, OnDataOut);

void setup()
{
  waitingToWrite = false;
  leftMovingTo = false;
  rightMovingTo = false;
//  delay(5000);
  Serial.begin(9600);
  Serial.println("done waiting");
  bt.Initialize();
  stepperL.setMaxSpeed(1000);  
  stepperR.setMaxSpeed(1000); 
  goStraight();
}

void loop()
{
  stepperL.runSpeed();
  stepperR.runSpeed();
  //Serial.println(stepperR.distanceToGo());
  
  if (stepperL.distanceToGo()==0 && leftMovingTo) {
    stepperL.setSpeed(0);  
    leftMovingTo = false;
    sendByte(0);
  }
 // Serial.println(movingTo);
  if (stepperR.distanceToGo()<=0 && rightMovingTo) {
    Serial.println("Inside if");
    stepperR.setSpeed(0);  
    rightMovingTo = false;
    sendByte(0);
  }
  
  bt.Update();
}

void goStraight() {
  stepperL.setSpeed(-SPEED);
  stepperR.setSpeed(SPEED);
}

void turnRight() {
  stepperR.setSpeed(-SPEED);
  stepperL.setSpeed(SPEED * deccelerateSpeed);
}

void turnLeft() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED * deccelerateSpeed);
}

void turnLeft90deg() {
  rightMovingTo = true;
  stopMotors();
  
  //stepperR.setCurrentPosition(1400);
  stepperR.moveTo(1550);
  stepperR.setSpeed(500);
  stepperR.runSpeedToPosition();
  Serial.println("Done turning");
  
}

void stopMotors(){
  stepperL.setSpeed(0);
  stepperR.setSpeed(0);
}

void turnRight90deg() {
  leftMovingTo = true;
  stopMotors();
  stepperL.moveTo(1550);
  stepperL.setSpeed(-500);
  Serial.println("turn right");
  stepperL.runSpeedToPosition();
  Serial.println("Done turning");
 
}
