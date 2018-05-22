#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motor1Pin1 2    // IN1 on the ULN2003 driver 1
#define motor1Pin2 3    // IN2 on the ULN2003 driver 1
#define motor1Pin3 4     // IN3 on the ULN2003 driver 1
#define motor1Pin4 5     // IN4 on the ULN2003 driver 1


// Motor pin definitions
#define motor2Pin1 6    // IN1 on the ULN2003 driver 1
#define motor2Pin2 7    // IN2 on the ULN2003 driver 1
#define motor2Pin3 8     // IN3 on the ULN2003 driver 1
#define motor2Pin4 9     // IN4 on the ULN2003 driver 1

int photoSensorR = A1;
int photoSensorL = A0;

int ledL = 10;
int ledR = 11;

int state = 0;
#define thresholdR 920
#define thresholdL 900
int SPEED = 1000;
#define deccelerateSpeed 0.5


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepperL(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepperR(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);


void setup() {
  pinMode(photoSensorL, INPUT);
  pinMode(photoSensorR, INPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  Serial.begin(9600);
  stepperL.setMaxSpeed(1000);  
  stepperR.setMaxSpeed(1000); 
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
          stepperL.setSpeed(0);
          stepperR.setSpeed(0);
          break;
      }
    }
  Serial.println(state);  
  stepperL.runSpeed();
  stepperR.runSpeed();
  
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

void goStraight() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED);
}

void turnRight() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED * deccelerateSpeed);
}

void turnLeft() {
  stepperL.setSpeed(SPEED);
  stepperR.setSpeed(-SPEED * deccelerateSpeed);
}
