from smbus import SMBus

def MoveForward(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, 1)
    print("MoveForward")
    return

addr = 0x08
bus = SMBus(1)
MoveForward(bus, addr)
