# from DataCollection.JoystickModule import getJS
# from .DataCollection.JoystickModule import getJS
from DataCollection import JoystickModule
from smbus import SMBus
import serial
from time import sleep
addr = 0x08
bus = SMBus(1)

def labelencode_joystick(axis_data):
    pass


if __name__ == "__main__":
    data = JoystickModule.getJS('')
    axis = [data["axis1"], data["axis2"], data["axis3"], data["axis4"]]
    while True:
        print(axis)
        bus.write_byte(addr, 0x1)
        sleep(0.5)