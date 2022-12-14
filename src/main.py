# from communication import Communication
# from vision import ComputerVision
# from tools import statistics, calculate # random functions
# from DataCollection.JoystickModule import getJS
from smbus import SMBus
import serial
from time import sleep
addr = 0x08
bus = SMBus(1)

if __name__ == "__main__":
    while True:
        bus.write_byte(addr, 0x1)
        sleep(1)