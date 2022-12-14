
from smbus import SMBus
from time import sleep
# from DataCollection.JoystickModule import getJS
from JoystickModule import getJS
addr = 0x08
bus = SMBus(1)

def labelencode_joystick(axis_data):
    # forward -> axis2 = -0.88 -> 1
    # right -> axis1 = 0.88 -> 2
    # left -> axis1 = -0.83 -> 3
    # reverse -> axis2 = 0.83 -> 4

    if sum(axis_data) == 0:
        return 0

    ax1 = axis_data[0]
    ax2 = axis_data[1]

    if abs(ax1) > abs(ax2):
        if ax1 < 0:
            return 3
        elif ax1 > 0:
            return 2
    if abs(ax2) < abs(ax1):
        if ax2 > 0:
            return 4
        elif ax2 < 0:
            return 1



if __name__ == "__main__":
    while True:
        data = getJS('')
        axis = [data["axis1"], data["axis2"]]
        print(axis, labelencode_joystick(axis))
        bus.write_byte(addr, 0x1)
        sleep(0.5)