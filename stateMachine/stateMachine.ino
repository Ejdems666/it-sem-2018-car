#include <ByteTransfer.h>
#include <AccelStepper.h>
#define HALFSTEP 8

int photoSensorR = A1;
int photoSensorL = A0;

int ledL = 10;
int ledR = 11;

int state = 0;

const int inPin = 11;//4
const int dataPin = 12;//3
const int outPin = 13; //2

uint8_t outData;
boolean waitingToWrite;

void OnDataIn(uint8_t data)
{
  if(data == 0)
  {
    Serial.println("Response: OK");
  }
  else if(data == 1)
  {
    Serial.println("Unknown command");
  }
  else
  {
    Serial.print("Unknown response: ");
    Serial.println(data);
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

String inString = "";


void setup() {
  pinMode(photoSensorL, INPUT);
  pinMode(photoSensorR, INPUT);

  pinMode(inPin, );
  pinMode(dataPin, );
  pinMode(outPin, );
  
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledL, HIGH); 
  digitalWrite(ledR, HIGH); 
}

void loop() {
  
  int new_state = checkState();
  if(state != new_state){
      state = new_state;
      switch(state) {
        case 1:
          goStraight();
          break;
        case 2:
          turnRight();
          break;
        case 3:
          turnLeft();
          break;
        default:
          break;
      }
    }
  Serial.println(state);  
  bt.Update();
  
}

int checkState() {
  bool sensorR = analogRead(photoSensorR)<= thresholdR;
  bool sensorL = analogRead(photoSensorL)<= thresholdL;

  Serial.print(analogRead(photoSensorR));
  Serial.print("\t");
  Serial.println(analogRead(photoSensorL));

   if ((sensorR && sensorL)) {
    return 1;
  } else if (sensorR){
    return 2;    
  } else {
    return 3;
  }
}

