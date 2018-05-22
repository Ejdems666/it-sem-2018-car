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
AccelStepper stepperL(AccelStepper::FULL4WIRE, motorAPin1, motorAPin3, motorAPin2, motorAPin4);
AccelStepper stepperR(AccelStepper::FULL4WIRE, motorBPin1, motorBPin3, motorBPin2, motorBPin4);

const int inPin = 11;
const int dataPin = 12;
const int outPin = 13;

uint8_t outData;
boolean waitingToWrite;


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
  delay(5000);
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
  bt.Update();
}

void goStraight() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED);
}

void turnRight() {
  stepperR.setSpeed(-SPEED);
  stepperL.setSpeed(SPEED * deccelerateSpeed);
}

void turnLeft() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED * deccelerateSpeed);
}

