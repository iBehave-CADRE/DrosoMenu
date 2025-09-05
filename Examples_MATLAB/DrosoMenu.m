%% Using the function serialport('COM', Baudrate) allows to create an object/variable that provides access to the DrosoMenu device via serial communication.
%% The Baudrate must be set to 9600, as this is the Baudrate defined in the Arduino code of the DrosoMenu controller.
%% The COM port must be adapted to the one used by the DrosoMenu controller. This can be checked in the Arduino IDE under Tools -> Port.
DrosoMenu = serialport("COM5", 9600);

%%To correctly interpret the serial communincation content, a terminator must be defined. In the Arduino code of the DrosoMenu controller, a carriage return (CR) is used as terminator.
%% Thus, the terminator of the serialport object must be set to "CR" as follows:
configureTerminator(DrosoMenu,"CR");

%% The function writeline(serialport, 'command') can be used to send commands to the DrosoMenu controller.
%% The commands '0', '1', '2' and '3' will move the DrosoMenu to the corresponding position.
writeline(DrosoMenu, '0');

%% The function readline(serialport) can be used to read the response of the DrosoMenu controller.
readout=readline(DrosoMenu);

%% The function flush(serialport) can be used to clear the input and output buffer of the serialport object.
flush(DrosoMenu);

%% Move to position 1
writeline(DrosoMenu, '1');
readout=readline(DrosoMenu);
flush(DrosoMenu);

%% Move to position 2
writeline(DrosoMenu, '2');
readout=readline(DrosoMenu);
flush(DrosoMenu);

%% Move to position 3
writeline(DrosoMenu, '3');
readout=readline(DrosoMenu);
flush(DrosoMenu);

%% The DrosoMenu can be disconnected by deleting the created object via serialport:
delete(DrosoMenu);