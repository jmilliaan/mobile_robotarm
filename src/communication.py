import serial
import time

class Communication:
    def __init__(self, port, baud_rate=115200, timeout=1):
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.ser = serial.Serial(self.port, self.baud_rate, self.timeout)
        self.ser.reset_input_buffer()

    def write(self, message):
        self.reset()
        self.ser.write(bytes(message))
        self.reset()

    def read(self):
        self.reset()
        line = self.ser.readline().decode('utf-8').rstrip()
        self.reset()
        return line
    
    def reset(self):
        self.ser.reset_input_buffer()
        self.ser.reset_output_buffer()

    def terminate(self):
        self.reset()
        self.ser.close()