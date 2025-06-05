# Setup environment

> [!IMPORTANT]
> The third step must be repeated every time you close and open the shell!

> [!NOTE]
> Replace ```{User}``` with your Windows user name!

1. Open PowerShell
2. Create virtual python environment: ```python -m venv C:\Users\{User}\.venv\fly_feeder```
3. Activate environment: ```C:\Users\{User}\.venv\fly_feeder\Scripts\activate.ps1```

# Usage

## Interactive

To run the example script use the command ```python interactive.py``` from the same folder where the file is located.
You can now interact with the device.

Type a number 0-3 to make the device go to the corresponding position. If you want to exit, type ```exit```.


## Test movement

> [!TIP]
> If you get the Error ```Device did not respond as expected!``` you probably have selected the wrong serial port!

To run the example movement script use the command ```python move.py``` from the same folder where the file is located.
The device should move between the positions with a delay of $10\mathrm{s}$.
