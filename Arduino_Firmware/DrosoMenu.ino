byte incomingByte;

int MovementTimeout = 2000; // in ms timeout between movement of each axis. 0 for simultaneous movement.
//int MovementSpeedDelay = 1; // in ms For delaying axis movement to set different speeds

int XAxisPin = A0; // X Axis is an analog output to set the actual distance of the connected linear actuator.
int ZAxisPin = 2; // Z Axis is a digital pin since it is all in or all out.
int SynchPin = 10; // Synch pint is a digital output PWM pin with a condensator turning it into an analog output for any DAQ data logging.

// Positions are encoded in PWM duty cycle between 0-255 and need to be visually confirmed for positioning. Absolute values in mm will be implemented.
int PosOut = 1;
int PosOne = 1;
int PosTwo = 90;
int PosThree = 180;

int Baseline = 255 - PosThree;
//loop for moving axis in and out in steps and therefore speed setting and better synch
//int XAxisStatus = 0;
//int YAxisStatus = 0;

void setup() {
  Serial.begin(115200);
  pinMode(XAxisPin, OUTPUT);
  pinMode(ZAxisPin, OUTPUT);
  pinMode(SynchPin, OUTPUT);
  //analogWriteResolution(10);

  // Initial configuration and Moving to Out Position
  digitalWrite(ZAxisPin, LOW);
  analogWrite(XAxisPin, PosOut);
  analogWrite(SynchPin, PosOut);
}

void loop() {
    if (Serial.available()>0) {
    incomingByte = Serial.read();
    //Serial.print(incomingByte);
    if (incomingByte == 48) { // ASCII code for 0
        Serial.println("Moving to Position Out");
        digitalWrite(ZAxisPin, LOW);
        analogWrite(SynchPin, PosOut);
        delay(MovementTimeout);
        analogWrite(XAxisPin, PosOut);
        Serial.flush();
      }
    else if (incomingByte == 49) { // ASCII code for 1
        Serial.println("Moving to Position 1");
        digitalWrite(ZAxisPin, LOW);
        analogWrite(SynchPin, PosOut);
        delay(MovementTimeout);
        analogWrite(XAxisPin, PosOne);
        delay(MovementTimeout);
        digitalWrite(ZAxisPin, HIGH);
        //delay(MovementTimeout);
        analogWrite(SynchPin, PosOne + Baseline);
        Serial.flush();
      }
    else  if (incomingByte == 50) { // ASCII code for 2
        Serial.println("Moving to Position 2");
        digitalWrite(ZAxisPin, LOW);
        analogWrite(SynchPin, PosOut);
        delay(MovementTimeout);
        analogWrite(XAxisPin, PosTwo);
        delay(MovementTimeout);
        digitalWrite(ZAxisPin, HIGH);
        //delay(MovementTimeout);
        analogWrite(SynchPin, PosTwo + Baseline);
        Serial.flush();
      }
    else  if (incomingByte == 51) { // ASCII code for 3
        Serial.println("Moving to Position 3");
        digitalWrite(ZAxisPin, LOW);
        analogWrite(SynchPin, PosOut);
        delay(MovementTimeout);
        analogWrite(XAxisPin, PosThree);
        delay(MovementTimeout);
        digitalWrite(ZAxisPin, HIGH);
        //delay(MovementTimeout);
        analogWrite(SynchPin, PosThree + Baseline);
        Serial.flush();
      }
    }
  Serial.flush();
}
