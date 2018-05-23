#include <Servo.h>

// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;

Servo myservo; // create servo object to control a servo

void setup() {

  // initialize serial communication:
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.write(90);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (straightIsBlocked()){
    if (leftIsBlocked()){
      
    else {
      
    }
    myservo.write(90);
    delay(2000);
  }
}

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

