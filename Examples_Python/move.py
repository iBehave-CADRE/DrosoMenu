from time import sleep
import serial

# Specify the COM port your device is connected to here
COM_PORT = 'COM6'

def move(ser, pos):
    responses = ['Out', '1', '2', '3']
    print(f"Moving to Position {responses[pos]}")

    # Send position to the device
    ser.write(str(pos).encode('UTF-8'))

    # Get and decode response of device
    response = ser.readline().decode().strip()

    # Check the response
    if response != f'Moving to Position {responses[pos]}':
        raise Exception("Device did not respond as expected!")

    # Flush any additional
    ser.flush()


with serial.Serial(COM_PORT, timeout=5) as ser:
    for pos in range(4):
        # Move to position
        move(ser, pos)

        # Wait for a while
        sleep(10)

    # Return to 0 position
    move(ser, 0)
