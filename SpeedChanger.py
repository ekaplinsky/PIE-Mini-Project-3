import serial

arduino_com_port = "/dev/ttyACM0"
baud_rate = 9600

serial_port = serial.Serial(arduino_com_port, baud_rate, timeout=1)
