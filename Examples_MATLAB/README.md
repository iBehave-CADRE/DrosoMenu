# Example Code for MATLAB Implementation

This code illustrated how to connect to the DrosoMenu in MATLAB via serial communication. After a successul connection is established, sending a 0, 1, 2 or 3 will move the DrosoMenu to the corresponding position:

Use the serialport('COM', Baudrate) to connect to the Arduino in the DrosoMenu controller.

To correctly interpret the serial communincation content, a terminator must be defined. 

configureTerminator(serialport, "CR)

Will send the 

writeline(serialport, '0')


%%Establish a connection with the DrosoMenu
DrosoMenu = serialport("COM5", 9600);
configureTerminator(DrosoMenu,"CR");

%% Move to position 0/out
writeline(DrosoMenu, '0');
readout=readline(DrosoMenu);
flush(DrosoMenu);


The DrosoMenu can be disconnected by deleting the created object via serialport:

delete(DrosoMenu);




