#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

int leftSensor; //left sensor reading
int rightSensor; //right sensor reading
int left; //left motor status
int right; //right motor status
int cutoff= 600; //sensor calibration cutoff- tape or not tape

Adafruit_DCMotor *leftMotor = AFMS.getMotor(3); //set up left motor
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4); //set up right motor

int incomingSpeed = 20; // for speed from python

void setup() { // put your setup code here, to run once:
  
  pinMode(1, INPUT); 
  pinMode(2, INPUT);
 
  Serial.begin(9600);           

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    //Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  //Serial.println("Motor Shield found.");

  
  // Set start speed (0 (off) to 255 (max speed))
  leftMotor->setSpeed(25);
  rightMotor->setSpeed(25);

  //Set motors ON
  left= 1;
  right= 1;
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // if there is data from computer get new speed:
  if (Serial.available() > 0) {
    // read the incoming byte:
//    incomingSpeed = Serial.read();/

  }

  incomingSpeed = 30;
  
  leftSensor= analogRead(2); //pin for left sensor
  rightSensor= analogRead(0); //pin for right sensor
  Serial.print(leftSensor);
  Serial.print(" ");
  Serial.println(rightSensor);
  if (leftSensor > cutoff); //set sensor variables to 0 and 1 for on black or not on black
    left= 1;
  if (leftSensor < cutoff);
    left= 0;
  if (rightSensor > cutoff);
    right= 1;
  if (rightSensor < cutoff);
    right= 0; 


  if (!left && !right){ //if both sensors not on line go forwards
   leftMotor->run(FORWARD);
   rightMotor->run(BACKWARD);
  
  }
  else if (!left && right){ //if right sensor on line go right
   leftMotor->run(FORWARD);
   rightMotor->run(RELEASE);
  
  }
  else if (left && !right){ //if left sensor on line go left
   leftMotor->run(RELEASE);
   rightMotor->run(BACKWARD);
  
  }
  //leftMotor->setSpeed(incomingSpeed); //reset sensor speed
  //rightMotor->setSpeed(incomingSpeed);
  //Serial.print(leftSensor);
  //Serial.print(left);
  //delay(15); //delay 
}
