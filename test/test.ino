#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1 2    // IN1 on the ULN2003 driver 1
#define motorPin2 3    // IN2 on the ULN2003 driver 1
#define motorPin3 4     // IN3 on the ULN2003 driver 1
#define motorPin4 5     // IN4 on the ULN2003 driver 1

#define motorPin21 6    // IN1 on the ULN2003 driver 1
#define motorPin22 7    // IN2 on the ULN2003 driver 1
#define motorPin23 8     // IN3 on the ULN2003 driver 1
#define motorPin24 9     // IN4 on the ULN2003 driver 1

int photoSensor = A5;
int counter = 0;

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin21, motorPin23, motorPin22, motorPin24);



void setup() {
  pinMode(photoSensor, INPUT);
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  stepper1.setSpeed(1000);
  stepper2.setSpeed(-1000);
}

void loop() {
//  if (millis() % 4000 > 2000) {
//    stepper1.setSpeed(500);
//  } else {
//    stepper1.setSpeed(-500); 
//  }
//  Serial.println();
//  if (analogRead(photoSensor) < 700) {
//    stepper1.setSpeed(-2000);
//  }
//   else {
//    stepper1.setSpeed(2000);
//  }
  stepper1.runSpeed();
  stepper2.runSpeed();
}
