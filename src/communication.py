import serial
import time

class Communication:
    def __init__(self, port=None, baud_rate=115200, timeout=1):
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        if port is not None:
            self.ser = serial.Serial(self.port, self.baud_rate, self.timeout)
        else:
            self.search_port()
        self.ser.reset_input_buffer()
    
    def search_port(self):
        n = 4
        names = ["ACM", "USB"]
        base = "/dev/tty"
        for name in names:
            for i in range(n + 1):
                try_port = f"{base}{name}{i}"
                print(try_port)
                try:
                    self.ser = serial.Serial(try_port, self.baud_rate, self.timeout)
                    self.port = try_port
                    print(f"Serial port found at {try_port}")
                except serial.SerialException:
                    continue


        
    def write(self, message):
        self.reset()
        self.ser.write(message.encode())
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