import serial
import sys
import time

with open(sys.argv[1], "r") as f:
    with serial.Serial("/dev/ttyACM0", 9600) as ser:
        ser.write("\n")
        while True:
            buf = f.read(60)
            ser.write(buf)
            time.sleep(10)
