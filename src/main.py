from communication import Communication
# from vision import ComputerVision
# from tools import statistics, calculate # random functions
from DataCollection.JoystickModule import getJS
from time import sleep
if __name__ == "__main__":
    com = Communication(port="/dev/ttyACM0")
    for i in range(100):
        data = getJS('')
        axis = [data["axis1"], data["axis2"], data["axis3"], data["axis4"]]
        axis_str = f"{data['axis1']} {data['axis2']} {data['axis3']} {data['axis4']}"
        com.write(axis_str)
        print(i + 1)
        print(axis)

        sleep(0.5)
    