#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1 5    // IN1 on the ULN2003 driver 1
#define motorPin2 6    // IN2 on the ULN2003 driver 1
#define motorPin3 9     // IN3 on the ULN2003 driver 1
#define motorPin4 10     // IN4 on the ULN2003 driver 1

int photoSensor = A5;

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);


void setup() {
  pinMode(photoSensor, INPUT);
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper1.setSpeed(500);
  
}

void loop() {
  stepper1.runSpeed();
  Serial.println(analogRead(photoSensor));
}
