// SENSORS

#include <ByteTransfer.h>
const int inPin = 2;
const int dataPin = 3;
const int outPin = 4;

uint8_t outData;
boolean waitingToWrite;

int photoSensorR = A1;
int photoSensorL = A0;

int ledL = 10;
int ledR = 11;

int state = 0;


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

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(photoSensorL, INPUT);
  pinMode(photoSensorR, INPUT);

  pinMode(inPin, );
  pinMode(dataPin, );
  pinMode(outPin, );
  
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  digitalWrite(ledL, HIGH); 
  digitalWrite(ledR, HIGH); 
  
  delay(10000);
  bt.Initialize();
  waitingToWrite = false;
}

void loop()
{
    if(!waitingToWrite){
    int new_state = checkState();
      if(state != new_state){
          state = new_state;
          Serial.println(state);
          outData = state;
          waitingToWrite = true;
       }
    }
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
