import serial
import sys
import time

with open(sys.argv[1], "r") as f:
    with serial.Serial("/dev/ttyACM0", 9600) as ser:
        ser.write(b"\n")
        while True:
            buf = f.read(60)
            if buf == "":
                break
            ser.write(buf.encode("latin1"))
            print(ser.read(100))
            if len(buf) == 60:
                time.sleep(10)
