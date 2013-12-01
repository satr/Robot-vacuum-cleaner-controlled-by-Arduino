/*
Program for controlling a robot with two motors.
The robot turns when motors changes their speed and direction.
Front bumpers on left and right sides detect obstacles.
LED is turned on when any of bumpers are pressed.
When porgram starts it waits while one of bumpers is pressed and than runs motors forward.
*/

const int pinLED = 13;
//right side
const int pinRightMotorDirection = 2;
const int pinRightMotorSpeed = 3;
const int pinRightBumper = 7;
//left side
const int pinLeftMotorDirection = 4;
const int pinLeftMotorSpeed = 5;
const int pinLeftBumper = 8;

//fields
const int turnTimeout = 100;
boolean led;
//set in counter how long a motor is running back: N/10 (in milliseconds)
int countDownWhileMovingToRight;
int countDownWhileMovingToLeft;

//Initialization
void setup() {

  initPins();
  
  waitWhileAnyBumperIsPressed();

  runRightMotorForward();
  runLeftMotorForward();
}

//Main loop
void loop() {
  
  verifyAndSetRightSide();
  verifyAndSetLeftSide();

  processRightSide();
  processLeftSide();

  turnOnLEDIfAnySideRunsBackward();
  
  delay(10);//repeat every 10 milliseconds
}

//---------------------------------------------------
void initPins(){
  pinMode(pinLED, OUTPUT);
  pinMode(pinRightMotorDirection, OUTPUT);
  pinMode(pinRightMotorSpeed, OUTPUT);
  pinMode(pinRightBumper, INPUT);
  pinMode(pinLeftMotorDirection, OUTPUT);
  pinMode(pinLeftMotorSpeed, OUTPUT);
  pinMode(pinLeftBumper, INPUT);
}

void waitWhileAnyBumperIsPressed(){
  while(checkBumperIsNotPressed(pinRightBumper)
        && checkBumperIsNotPressed(pinLeftBumper)){
    delay(20);//check every 20 milliseconds
  }
}
 
void processRightSide(){
  if(countDownWhileMovingToRight <= 0)//checks if counter was NOT ran when bumper had been pressed
    return;
  //otherwise - counter is counting downd (as a delay) while the right motor is moving backward 
  countDownWhileMovingToRight--;//decrease the counter if it WAS ran when bumper had been pressed
  if(countDownWhileMovingToRight <= 0)//if the running counter got down to zero
    runRightMotorForward();//run the right motor forward
}
  
void processLeftSide(){
  if(countDownWhileMovingToLeft <= 0)
    return;
  countDownWhileMovingToLeft--;
  if(countDownWhileMovingToLeft <= 0)
    runLeftMotorForward();
}
  
void verifyAndSetRightSide(){
  if(checkBumperIsNotPressed(pinRightBumper))//checks if right bumper has NOT been pressed
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToRight))//if the counter is not yet counting down
    runRightMotorBackward();//run the right motor backward
  countDownWhileMovingToRight = turnTimeout;//set the counter to maximum value to start it counting down
}

void verifyAndSetLeftSide(){
  if(checkBumperIsNotPressed(pinLeftBumper))
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToLeft))
    runLeftMotorBackward();
  countDownWhileMovingToLeft = turnTimeout;
}

bool checkCounterIsNotSet(int counter){
  return counter <= 0;
}

bool checkBumperIsNotPressed(int pinBumper){
  return digitalRead(pinBumper);
}

void runRightMotorForward(){
  runMotorForward(pinRightMotorDirection, pinRightMotorSpeed);
}

void runLeftMotorForward(){
  runMotorForward(pinLeftMotorDirection, pinLeftMotorSpeed);
}

void runRightMotorBackward(){
  runMotorBackward(pinRightMotorDirection, pinRightMotorSpeed);
}

void runLeftMotorBackward(){
  runMotorBackward(pinLeftMotorDirection, pinLeftMotorSpeed);
}

void runMotorForward(int pinMotorDirection, int pinMotorSpeed){
  digitalWrite(pinMotorDirection, true); //set direction forward 
  analogWrite(pinMotorSpeed, 0); //set max speed forward (127 is for stop)
}

void runMotorBackward(int pinMotorDirection, int pinMotorSpeed){
  digitalWrite(pinMotorDirection, false); //set direction backward 
  analogWrite(pinMotorSpeed, 255); //set max speed backward (127 is for stop)
}

void turnOnLEDIfAnySideRunsBackward(){
  digitalWrite(pinLED, oneOrBothMotorsAreRunninsBack());
}

bool oneOrBothMotorsAreRunninsBack(){
  return (countDownWhileMovingToRight > 0 || countDownWhileMovingToLeft > 0);
}
