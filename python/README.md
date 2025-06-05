# Setup environment

> [!IMPORTANT]
> The third step must be repeated every time you close and open the shell!

> [!NOTE]
> Replace ```{User}``` with your Windows user name!

1. Open PowerShell
2. Create virtual python environment: ```python -m venv C:\Users\{User}\.venv\fly_feeder```
3. Activate environment: ```C:\Users\{User}\.venv\fly_feeder\Scripts\activate.ps1```

# Usage

> [!NOTE]
> Make sure to edit the COM port in the file to the COM port your device is connected to.
> If you are unsure refer to this [section](#finding-the-com-port).

## Interactive

To run the example script use the command ```python interactive.py``` from the same folder where the file is located.

You can now interact with the device.

Type a number 0-3 to make the device go to the corresponding position. If you want to exit, type ```exit```.


## Test movement

> [!TIP]
> If you get the Error ```Device did not respond as expected!``` you probably have selected the wrong serial port!

To run the example movement script use the command ```python move.py``` from the same folder where the file is located.
The device should move between the positions with a delay of $10\mathrm{s}$.

# Custom Code

A minimal example to tell the device to move to a specific position is given in ```minimal.py```.
It expects a number in the range of $0-3$ encoded as UTF-8. The serial port is opened in a context manager (```with```-statement) and the position send via the ```write``` function.

The minimal exmaple does not check for a response from the device but just blindly commands a position.


If you want to move to multiple positions it is best to do this within the ```with``` block instead of opening a new connection to the serial port each time.

# Finding the COM port

To find the COM port your device is connected to you can use the ```list_ports.py``` script. It will show you all connected COM ports.

If you are unsure which port corresponds to your device run the script without the device plugged in and again with the device plugged in and see which COM port got added.
