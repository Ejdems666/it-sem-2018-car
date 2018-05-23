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
  
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
  myservo.write(90);

}

void loop() {

  // and the distance result in centimeters:
  long cm = measure();
  
  if ( cm < 15){
    myservo.write(180); // sets the servo position according to the scaled value
    delay(4000);
    cm = measure();
    if (cm < 15){
      myservo.write(0); // sets the servo position according to the scaled value
      delay(4000);
  }
  myservo.write();
  
  
  
  Serial.print(cm);
  
  Serial.print("cm");
  
  Serial.println();
  
  delay(100);

}

long microsecondsToCentimeters(long microseconds) {

// The speed of sound is 340 m/s or 29 microseconds per centimeter.

// The ping travels out and back, so to find the distance of the

// object we take half of the distance travelled.

return microseconds / 29 / 2;

}

long measure() {
  long duration, cm;
  
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(20);
  
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  
  return microsecondsToCentimeters(duration);  
}
