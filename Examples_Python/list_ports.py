import serial.tools.list_ports


for Port in serial.tools.list_ports.comports():
    attributes = ['device', 'name', 'description', 'hwid', 'vid', 'pid', 'serial_number', 'location', 'manufacturer', 'product', 'interface']
    print(Port)
    for Attribute in attributes:
        print(f"{Attribute}: {Port.__dict__[Attribute]}")
    print()
