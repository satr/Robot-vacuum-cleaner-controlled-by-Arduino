const int ledPin = 13;
const int dirRPin = 2;
const int motorRPin = 3;
const int bumperRPin = 7;
const int dirLPin = 4;
const int motorLPin = 5;
const int bumperLPin = 8;

const int turnTimeout = 100;

boolean led;
int movedToRCount, movedToLCount;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(dirRPin, OUTPUT);
  pinMode(motorRPin, OUTPUT);
  pinMode(bumperRPin, INPUT);
  pinMode(dirLPin, OUTPUT);
  pinMode(motorLPin, OUTPUT);
  pinMode(bumperLPin, INPUT);
  
  runRForward();
}

void loop() {
  VerifyAndSetRSide();
  VerifyAndSetLSide();

  ProcessRSide();
  ProcessLSide();

  digitalWrite(ledPin, (movedToRCount > 0 || movedToLCount > 0));
  
  delay(10);
}

void ProcessRSide(){
  if(movedToRCount <= 0)
    return;
  movedToRCount--;
  if(movedToRCount <= 0)
    runRForward();
}
  
void ProcessLSide(){
  if(movedToLCount <= 0)
    return;
  movedToLCount--;
  if(movedToLCount <= 0)
    runLForward();
}
  
void VerifyAndSetRSide(){
  if(digitalRead(bumperRPin))
    return;
  if(movedToRCount <= 0)
    runRBackward();
  movedToRCount = turnTimeout;
}

void VerifyAndSetLSide(){
  if(digitalRead(bumperLPin))
    return;
  if(movedToLCount <= 0)
    runLBackward();
  movedToLCount = turnTimeout;
}

void runRBackward(){
  digitalWrite(dirRPin, false);
  analogWrite(motorRPin, 255);
}

void runLBackward(){
  digitalWrite(dirLPin, false);
  analogWrite(motorLPin, 255);
}

void runRForward(){
  digitalWrite(dirRPin, true);
  analogWrite(motorRPin, 0);
}

void runLForward(){
  digitalWrite(dirLPin, true);
  analogWrite(motorLPin, 0);
}


