#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

int leftSensor; //left sensor reading
int rightSensor; //right sensor reading
int middleSensor;
int left; //left motor status
int right; //right motor status
int middle;
int cutoff= 600; //sensor calibration cutoff- tape or not tape
int mid_cutoff = 700;

int rMotorSpeed;
int lMotorSpeed;

Adafruit_DCMotor *leftMotor = AFMS.getMotor(3); //set up left motor
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4); //set up right motor

int incomingSpeed = 20;

void setup() { // put your setup code here, to run once:
  
  pinMode(1, INPUT); 
  pinMode(2, INPUT);
  pinMode(0, INPUT);
 
  Serial.begin(9600);           

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    //Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  //Serial.println("Motor Shield found.");

  
  // Set start speed (0 (off) to 255 (max speed))
  leftMotor->setSpeed(20);
  rightMotor->setSpeed(20);

  //Set motors ON
  left= 1;
  right= 1;
  

}

void loop() {
  //put your main code here, to run repeatedly:

  // THIS IS THE PART THAT DOES THE SERIAL CHANGE
  /*
  incomingSpeed = Serial.parseInt();
  if(incomingSpeed != currentSpeed){
    leftMotor->setSpeed(incomingSpeed); //reset sensor speed
    rightMotor->setSpeed(incomingSpeed);
    currentSpeed = incomingSpeed;
  }
  */
  /*
  if(Serial.available()){
    incomingSpeed = Serial.readString().toInt();
    leftMotor->setSpeed(incomingSpeed); //reset sensor speed
    rightMotor->setSpeed(incomingSpeed);
  }
  */
  leftSensor= analogRead(2); //pin for left sensor
  rightSensor= analogRead(0); //pin for right sensor
  middleSensor = analogRead(1);
  
  if (leftSensor > cutoff){ //set sensor variables to 0 and 1 for on black or not on black
    left= 1;
  }
  else if (leftSensor < cutoff){
    left= 0;
  }
  
  if (rightSensor > cutoff){
    right= 1;
  }
  else if (rightSensor < cutoff){
    right= 0;
  }

  if(middleSensor > mid_cutoff){
    middle = 1;
  }
  else if(middleSensor < mid_cutoff){
    middle = 0;
  }

  if (!left && !right && middle){ //if both sensors not on line go forwards
   leftMotor->run(FORWARD);
   rightMotor->run(BACKWARD);
   rMotorSpeed = incomingSpeed;
   lMotorSpeed = incomingSpeed;

  
  }
  else if (!left && right && !middle){ //if right sensor on line go right
   leftMotor->run(FORWARD);
   rightMotor->run(RELEASE);
   rMotorSpeed = 0;
   lMotorSpeed = incomingSpeed;
  
  }
  else if (left && !right && !middle){ //if left sensor on line go left
   leftMotor->run(RELEASE);
   rightMotor->run(BACKWARD);
   rMotorSpeed = incomingSpeed;
   lMotorSpeed = 0;
  
  }
  else if(left && !right && middle){// indicating that we need to make a full left turn
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD); 
    rMotorSpeed = incomingSpeed;
    lMotorSpeed = -1 * incomingSpeed;
    delay(100);   
  }
  else if(!left && right && middle){// indicating that we need to make a full right turn
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    rMotorSpeed = -1 * incomingSpeed;
    lMotorSpeed = incomingSpeed;
    delay(100);  
  }
  delay(50);


  //Serial.print("Left Sensor");
  Serial.print(leftSensor);
  Serial.print(",");
  //Serial.print("Middle Sensor");
  Serial.print(middleSensor);
  Serial.print(",");
  //Serial.print("Right Sensor");
  Serial.print(rightSensor);
  Serial.print(",");
  //Serial.print("Right Motor");
  Serial.print(rMotorSpeed);
  Serial.print(",");
  //Serial.print("Left Motor");
  Serial.println(lMotorSpeed);
  
}
