
from smbus import SMBus
from time import sleep
# from DataCollection.JoystickModule import getJS
from JoystickModule import getJS
addr = 0x08
bus = SMBus(1)

def labelencode_joystick(axis_data):
    pass


if __name__ == "__main__":
    while True:
        data = getJS('')
        axis = [data["axis1"], data["axis2"], data["axis3"], data["axis4"]]
        print(axis)
        bus.write_byte(addr, 0x1)
        sleep(0.5)