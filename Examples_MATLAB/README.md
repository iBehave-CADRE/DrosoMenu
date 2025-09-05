# Example Code for MATLAB Implementation

This code illustrated how to connect to the DrosoMenu in MATLAB via serial communication:

Using the function `serialport(port, Baudrate)` allows to create an object/variable that provides access to the DrosoMenu device via serial communication. The Baudrate must be set to 9600, as this is the Baudrate defined in the Arduino code of the DrosoMenu controller. The COM port must be adapted to the one used by the DrosoMenu controller. 

> [!TIP]
> The COM port can be checked in the Arduino IDE under Tools -> Port.


```matlab
DrosoMenu = serialport("COM5", 9600);
```

To correctly interpret the serial communincation content, a terminator must be defined. In the Arduino code of the DrosoMenu controller, a carriage return (CR) is used as terminator. Thus, the terminator of the serialport object must be set to "CR" with `configureTerminator(device, terminator)`:

```matlab
configureTerminator(DrosoMenu,"CR");
```

The function `writeline(device, data)` can be used to send commands to the DrosoMenu controller. The commands '0', '1', '2' and '3' will move the DrosoMenu to the corresponding position:

```matlab
writeline(DrosoMenu, '0');
```

%% The function `readline(device)` can be used to read the response of the DrosoMenu controller:

> [!TIP]
> The specific response to an incoming command is determined in the Arduino firmware and can also be adapted.

```matlab
readout=readline(DrosoMenu);
```

The function `flush(device)` can be used to clear the input and output buffer of the serialport object. This prevents stack overflow when interacting with the device and ensures reading out the most recent data.

```matlab
flush(DrosoMenu);
```

%% The DrosoMenu can be disconnected with the function `delete(var)`. This deletes the object and device created via serial port:

```matlab
delete(DrosoMenu);
```