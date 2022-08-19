import serial
import sys
from time import sleep

i = 0
while(True):
    try:
        ESP32 = serial.Serial(('COM'+str(i)), 921600)
        serialEnd = ('COM'+str(i))
        print("Serial device conecct on " +serialEnd)
        ESP32.close()
        break
    except:
        print(sys.exc_info())
    sleep(2)
    i = i + 1
