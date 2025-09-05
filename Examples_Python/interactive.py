import serial

# Specify the COM port your device is connected to here
COM_PORT = 'COM6'

with serial.Serial(COM_PORT, timeout=5) as ser:
    # Enter interactive loop
    while True:
        # Get user input
        x = input('>>> ')

        # Break if user wants to exit
        if x == 'exit': break

        # Send input to device
        ser.write(x.encode('UTF-8'))

        # Wait for, decode and print response
        print(ser.readline().decode().strip())

        # Flush any additional response
        ser.flush()
