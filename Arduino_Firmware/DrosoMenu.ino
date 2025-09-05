// This Arduino sketch controls the DrosoMenu apparatus for neuroscience experiments,
// such as automated delivery of gustatory stimuli or positioning of experimental subjects.
// It manages two actuators (X and Z axes) and a synchronization signal for data acquisition systems.

// Variable to store incoming serial commands from a host computer or controller. The host computer can be connected via USB and send the commands in real-time with Python and MATLAB.
// Commands are expected as single ASCII characters ('0', '1', '2', '3').
byte incomingByte;

// MovementTimeout defines the delay (in milliseconds) between sequential actuator movements.
// This allows for controlled, stepwise positioning, which can be critical for precise timing in experiments.
int MovementTimeout = 2000; // ms; set to 0 for simultaneous movement

// Pin assignments for hardware control:
// XAxisPin: Analog output (PWM) for controlling the linear actuator of the X-axis and therefore the actual positions of the stimulus..
// ZAxisPin: Digital output binary for z-axis with all in or all out position.
// SynchPin: Digital PWM output, filtered to analog, used for synchronizing with external data acquisition (DAQ) systems.
int XAxisPin = A0;
int ZAxisPin = 2;
int SynchPin = 10;

// Position values encoded as PWM duty cycles (0-255).
// These values should be calibrated to match physical positions relevant to the experiment (e.g., distances in mm). This has to be done empirically for each setup.
int PosOut = 1;      // "Out" position (baseline, e.g., actuator fully retracted)
int PosOne = 1;      // Experimental position 1
int PosTwo = 90;     // Experimental position 2
int PosThree = 180;  // Experimental position 3

// Baseline offset for the synchronization signal.
// Ensures the sync signal is distinguishable for each experimental position.
int Baseline = 255 - PosThree;

// Setup function initializes serial communication and configures actuator pins.
// At startup, all actuators are moved to the "Out" position to ensure a known baseline state.
void setup() {
  Serial.begin(115200);           // High baud rate for fast communication with host
  pinMode(XAxisPin, OUTPUT);      // Configure X axis actuator pin
  pinMode(ZAxisPin, OUTPUT);      // Configure Z axis actuator pin
  pinMode(SynchPin, OUTPUT);      // Configure synchronization pin

  // Move actuators to baseline "Out" position
  digitalWrite(ZAxisPin, LOW);    // Z axis: retract or set to baseline
  analogWrite(XAxisPin, PosOut);  // X axis: move to baseline position
  analogWrite(SynchPin, PosOut);  // Sync signal: baseline value
}

// Main loop listens for serial commands and executes corresponding actuator movements.
// Each command ('0', '1', '2', '3') represents a specific experimental configuration or trial phase.
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read(); // Read incoming command

    // Command '0': Move Z-axis and X-axis to position Out. Position out on the X-axis can be equal to position 1.
    if (incomingByte == 48) { // ASCII '0'
      Serial.println("Moving to Position Out");
      digitalWrite(ZAxisPin, LOW);         // Z axis: move to position out and retract
      analogWrite(SynchPin, PosOut);       // Sync: baseline
      delay(MovementTimeout);              // Wait for movement to complete
      analogWrite(XAxisPin, PosOut);       // X axis: move to position Out
      Serial.flush();                      // Clear serial buffer
    }
    // Command '1': Move to Position 1 (e.g., present stimulus at location 1)
    else if (incomingByte == 49) { // ASCII '1'
      Serial.println("Moving to Position 1");
      digitalWrite(ZAxisPin, LOW);         // Z axis: move to position out and retract
      analogWrite(SynchPin, PosOut);       // Sync: baseline
      delay(MovementTimeout);              // Wait for movement to complete
      analogWrite(XAxisPin, PosOne);       // X axis: move to position 1
      delay(MovementTimeout);              // Wait for movement to complete
      digitalWrite(ZAxisPin, HIGH);        // Z axis: insert (e.g., present stimulus)
      analogWrite(SynchPin, PosOne + Baseline); // Sync: signal position 1 to DAQ
      Serial.flush();
    }
    // Command '2': Move to Position 2 (e.g., present stimulus at location 2)
    else if (incomingByte == 50) { // ASCII '2'
      Serial.println("Moving to Position 2");
      digitalWrite(ZAxisPin, LOW);
      analogWrite(SynchPin, PosOut);
      delay(MovementTimeout);
      analogWrite(XAxisPin, PosTwo);
      delay(MovementTimeout);
      digitalWrite(ZAxisPin, HIGH);
      analogWrite(SynchPin, PosTwo + Baseline); // Sync: signal position 2
      Serial.flush();
    }
    // Command '3': Move to Position 3 (e.g., present stimulus at location 3)
    else if (incomingByte == 51) { // ASCII '3'
      Serial.println("Moving to Position 3");
      digitalWrite(ZAxisPin, LOW);
      analogWrite(SynchPin, PosOut);
      delay(MovementTimeout);
      analogWrite(XAxisPin, PosThree);
      delay(MovementTimeout);
      digitalWrite(ZAxisPin, HIGH);
      analogWrite(SynchPin, PosThree + Baseline); // Sync: signal position 3
      Serial.flush();
    }
  }
  Serial.flush(); // Ensure serial buffer is cleared each loop
}
