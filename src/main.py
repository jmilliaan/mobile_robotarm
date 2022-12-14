from communication import Communication
# from vision import ComputerVision
# from tools import statistics, calculate # random functions
from DataCollection.JoystickModule import getJS

if __name__ == "__main__":
    for i in range(3):
        data = getJS('')
        axis = [data["axis1"], data["axis2"], data["axis3"], data["axis4"]]
        print(axis)
    # com = Communication(port="/dev/ttyACM0")
    # com.write()