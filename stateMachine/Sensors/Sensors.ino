// SENSORS
#include <Servo.h>
#include <ByteTransfer.h>
const int inPin = 2;
const int dataPin = 3;
const int outPin = 4;

const int trigPin = 12;
const int echoPin = 13;

Servo myservo;

int outData;
boolean waitingToWrite;

int photoSensorR = A1;
int photoSensorL = A0;

const int thresholdR = 850+10;
const int thresholdL = 870;

int ledL = 10;
int ledR = 11;

int state = 0;
boolean stoppedAtWall 
int checkState() {

  bool sensorR = analogRead(photoSensorR)<= thresholdR;
  bool sensorL = analogRead(photoSensorL)<= thresholdL;
  //if(millis()%1000==0){
    /*Serial.print(analogRead(photoSensorR));
    Serial.print("\t");
    Serial.println(analogRead(photoSensorL));*/
  //}
   if ((sensorR && sensorL)) {
    return 1;
  } else if (sensorR){
    return 2;    
  } else if (sensorL){
    return 3;
  } else {
    if (straightIsBlocked()){
      return 6;
    } else
      Serial.println("going straight");
      myservo.write(90); 
      return 1;  
  }

  // 4-left, 5-right
}

void OnDataIn(uint8_t data) {
  if(data == 0) {
    Serial.println("Response: OK");
  } else if(data == 1) {
    Serial.println("Unknown command");
  } else {
    Serial.print("Unknown response: ");
    Serial.println(data);
  }
}

bool OnDataOut(uint8_t &data) {
  if(waitingToWrite) {
    data = outData;
    Serial.println(data);
    waitingToWrite = false;
    return true;
  }
  return false;
}

ByteTransfer bt(inPin, dataPin, outPin, OnDataIn, OnDataOut);

boolean straightIsBlocked() {
  return measure() < 15;
}

boolean leftIsBlocked() {
  myservo.write(180);
  delay(2000);
  return measure() < 15;
}

long measure() {
  long duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  return microsecondsToCentimeters(duration);  
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}



void setup() {
  Serial.begin(19200);
  while (!Serial) { ;}
  
  delay(1000);  
  pinMode(photoSensorL, INPUT);
  pinMode(photoSensorR, INPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.write(90);
  myservo.attach(9);
  
  digitalWrite(ledL, HIGH); 
  digitalWrite(ledR, HIGH); 
  
  bt.Initialize();

  waitingToWrite = false;

  Serial.println("setup ended");
}

void loop() {
  if(!waitingToWrite){
    //if (millis()%50 == 0) {
      int new_state = checkState();
      /*Serial.print("New state: ");
      Serial.println(new_state);
      Serial.print("Old state: ");
      Serial.println(state);*/
      if(state != new_state){
          state = new_state;            
          outData = state;
          waitingToWrite = true;
       }
    //}
  }
  bt.Update();
}


