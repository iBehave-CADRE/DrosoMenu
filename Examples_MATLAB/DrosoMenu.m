%%Establish a connection with the DrosoMenu
DrosoMenu = serialport("COM5", 9600);
configureTerminator(DrosoMenu,"CR");

%% Move to position 0/out
writeline(DrosoMenu, '0');
readout=readline(DrosoMenu);
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

%%
delete(DrosoMenu);