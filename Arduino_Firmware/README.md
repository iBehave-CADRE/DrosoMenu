# DrosoMenu Arduino Firmware

This firmware controls the DrosoMenu apparatus for neuroscience experiments, such as automated delivery of gustatory stimuli or precise positioning of experimental subjects. The code manages two actuators (X and Z axes) and provides a synchronization signal for external data acquisition systems. It has to be flashed on the Arduino in the DrosoMenu control box, to run in a continuous loop.

## Hardware Overview

- **X Axis (Linear Actuator):** Controls the position of the stimulus or platform. Connected to analog (PWM) pin `A0`.
- **Z Axis (Binary Actuator):** Controls insertion/retraction (all in/all out) of the stimulus. Connected to digital pin `2`.
- **Synchronization Signal:** Outputs a PWM signal (pin `10`) for synchronizing actuator movements with external DAQ systems.

## Serial Communication

The Arduino receives commands from a host computer (e.g., via MATLAB or Python) over USB serial. Each command is a single ASCII character:
- `'0'`: Move to "Out" position (baseline/reset)
- `'1'`: Move to Position 1
- `'2'`: Move to Position 2
- `'3'`: Move to Position 3

The firmware expects a baud rate of **115200** (set in `Serial.begin(115200)`).

## Pin and Position Configuration

- **Pin Assignments:**
  - `XAxisPin = A0` (PWM output)
  - `ZAxisPin = 2` (digital output)
  - `SynchPin = 10` (PWM output for sync)
- **Position Values:** PWM duty cycles (0–255) must be calibrated for your hardware setup.
  - `PosOut`: Baseline/out position
  - `PosOne`, `PosTwo`, `PosThree`: Experimental positions

## Firmware Logic

### Setup

On startup, the Arduino:
- Initializes serial communication.
- Sets actuator pins as outputs.
- Moves all actuators to the "Out" position for a known baseline.

### Main Loop

The Arduino continuously listens for serial commands:
- **Command `'0'`:** Retracts Z axis, sets X axis and sync signal to baseline.
- **Command `'1'`:** Moves X axis to Position 1, inserts Z axis, updates sync signal.
- **Command `'2'`:** Moves X axis to Position 2, inserts Z axis, updates sync signal.
- **Command `'3'`:** Moves X axis to Position 3, inserts Z axis, updates sync signal.

Each movement is separated by a configurable delay (`MovementTimeout`, default 2000 ms) to ensure precise timing. After receiving a command for movement, the arduino prints an ansewer via serial communication. This answer can be read out with Python, MATLAB or Bonsai.

### Synchronization

The sync signal (PWM on pin 10) changes with each position, allowing external DAQ systems to record actuator states alongside neural or behavioral data.

## Example Workflow

1. **Connect Arduino to Host Computer:** Use USB and select the correct COM port.
2. **Send Commands:** Use MATLAB, Python, or Arduino Serial Monitor to send `'0'`, `'1'`, `'2'`, or `'3'`.
3. **Monitor Serial Output:** The Arduino prints status messages for each movement.
4. **Synchronize Data:** Use the sync signal to align actuator movements with experimental recordings.

## Customization

- **Calibrate Position Values:** Adjust `PosOut`, `PosOne`, `PosTwo`, `PosThree` for your hardware.
- **Change Movement Timing:** Modify `MovementTimeout` for faster or slower transitions.
- **Expand Functionality:** Add new commands or actuator positions as needed.

> [!TIP]
> Always test actuator movements with your experimental setup before running live experiments to ensure safety and accuracy.

## Troubleshooting

- **No Movement:** Check pin assignments and wiring.
- **Incorrect Positioning:** Recalibrate PWM values for each position.
- **Serial Communication Issues:** Ensure baud rate matches between Arduino and host computer.

## Key Functions Used in DrosoMenu.ino

The Arduino firmware uses several built-in functions to control hardware and handle communication:

### `Serial.begin(baudrate)`
Initializes serial communication between the Arduino and the host computer.  
**Usage in DrosoMenu:**  
`Serial.begin(115200);` sets the communication speed to 115200 bits per second, allowing fast and reliable data transfer for real-time experimental control.

### `pinMode(pin, mode)`
Configures a specified pin to behave as either an input or output.  
**Usage in DrosoMenu:**  
Used to set actuator and synchronization pins as outputs so they can control hardware devices.

### `digitalWrite(pin, value)`
Sets a digital pin to HIGH (5V) or LOW (0V).  
**Usage in DrosoMenu:**  
Controls the Z axis actuator (binary movement: all in or all out).

### `analogWrite(pin, value)`
Outputs a PWM (pulse-width modulation) signal on a pin, simulating analog output.  
**Usage in DrosoMenu:**  
Controls the X axis actuator and the synchronization signal. The value (0–255) determines the actuator position or sync signal level.

### `Serial.available()`
Returns the number of bytes available to read from the serial buffer.  
**Usage in DrosoMenu:**  
Checks if a command has been sent from the host computer.

### `Serial.read()`
Reads incoming serial data (one byte at a time).  
**Usage in DrosoMenu:**  
Retrieves the command character sent by the host computer.

### `Serial.println(message)`
Sends a message back to the host computer, useful for status updates and debugging.  
**Usage in DrosoMenu:**  
Prints which position the DrosoMenu is moving to, aiding experiment monitoring.

### `delay(milliseconds)`
Pauses the program for a specified time (in milliseconds).  
**Usage in DrosoMenu:**  
Ensures actuators have time to reach their positions before the next movement or command.

### `Serial.flush()`
Clears the serial buffer, ensuring only the latest data is processed.  
**Usage in DrosoMenu:**  
Prevents old or unwanted commands from interfering with actuator control.

---

These functions together enable precise, real-time control of the DrosoMenu hardware, allowing for automated and synchronized experimental procedures

---

For further details, see the annotated source code
