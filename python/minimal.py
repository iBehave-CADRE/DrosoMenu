import serial

# Specify the COM port your device is connected to here
COM_PORT = 'COM6'

# The position to go to
position = 1

with serial.Serial(COM_PORT, timeout=5) as ser:
    # The position has to be encoded as an UTF-8 string
    ser.write(str(position).encode('UTF-8'))
