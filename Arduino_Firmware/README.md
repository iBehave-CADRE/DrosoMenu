# DrosoMenu Arduino Firmware

This firmware controls the DrosoMenu apparatus for neuroscience experiments, such as automated delivery of gustatory stimuli or precise positioning of experimental subjects. The code manages two actuators (X and Z axes) and provides a synchronization signal for external data acquisition systems.

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

Each movement is separated by a configurable delay (`MovementTimeout`, default 2000 ms) to ensure precise timing.

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

---

For further details, see the annotated source code
