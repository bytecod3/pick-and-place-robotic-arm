import serial
import time

arduinoSerialData = serial.Serial('/dev/ttyACM3', 9600, timeout=1)

for i in range(10):
    with arduinoSerialData as ser:
        time.sleep(1)
        ser.write(b'H')
        time.sleep(1)
        ser.write(b'L')


# while 1:
#     # read data only if there is data waiting at the serial port
#     if arduinoSerialData.inWaiting() > 0:
#         myData = arduinoSerialData.readline()
#         distance = float(myData)
#         print(distance)
