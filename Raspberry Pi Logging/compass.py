import smbus2 as smbus
import math

Register_A     = 0                 #Address of Configuration register A
Register_B     = 0x01              #Address of configuration register B
Register_mode  = 0x02              #Address of mode register

X_axis_H    = 0x03                 #Address of X-axis MSB data register
Z_axis_H    = 0x05                 #Address of Z-axis MSB data register
Y_axis_H    = 0x07                 #Address of Y-axis MSB data register
declination = math.radians(-10.27) #define declination angle of location where measurement going to be done

bus = smbus.SMBus(1)
Device_Address = 0x1e

bus.write_byte_data(Device_Address, Register_A, 0x70)
bus.write_byte_data(Device_Address, Register_B, 0xa0)
bus.write_byte_data(Device_Address, Register_mode, 0)

def read_raw_data(addr):
    high = bus.read_byte_data(Device_Address, addr)
    low = bus.read_byte_data(Device_Address, addr+1)
    value = ((high << 8) | low)
    if(value > 32768):
        value = value - 65536
    return value

x = read_raw_data(X_axis_H)
y = read_raw_data(Y_axis_H)
z = read_raw_data(Z_axis_H)

heading = math.atan2(y, x) + declination

if heading > 2*math.pi:
    heading = heading - 2*math.pi
if heading < 0:
    heading = heading + 2*math.pi
heading_angle = int(heading * 180/math.pi)
print("%d°" % heading_angle)
