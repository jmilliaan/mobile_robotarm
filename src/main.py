from communication import Communication
from vision import ComputerVision
from tools import statistics, calculate # random functions
from DataCollection.JoystickModule import getJS

if __name__ == "__main__":
    data = getJS('')
    # com = Communication(port="/dev/ttyACM0")
    # com.write()