import serial
import struct

knob_serial = serial.Serial()

def serial_open(Port, Baudrate):
    global knob_serial
    try:
        knob_serial = serial.Serial(port=Port, baudrate=Baudrate, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1, rtscts=False)
    except serial.SerialException:
        return False
    else:
        return True

def serial_read():
    knob_serial.reset_input_buffer()
    knob_serial.readline()
    return knob_serial.readline()
    
def serial_decode(data):
    try:
        [angle, speed] = data.decode('ascii', 'ignore').strip().split(',')
        angle = 360.0 - float(angle)
        speed = - float(speed)
    except ValueError:
        return [None, None]
    else:
        return [angle, speed]

# uint8_t uartBuf[30];

# hasStart = uartBuf[0] & (1 << 0);
# hasEnd = uartBuf[0] & (1 << 1);
# hasLvl = uartBuf[0] & (1 << 2);
# lvlAngle = *((float *)(uartBuf + 1));
# startAngle = *((float *)(uartBuf + 5));
# endAngle = *((float *)(uartBuf + 9));

#       0: 0000 0--- hasLvl hasEnd hasStart
#  1 ~  4: lvlAngle
#  5 ~  8: startAngle
#  9 ~ 12: endAngle
#      13: Draw_Mode
# 14 ~ 19: empty

def data_pack(hasLvl, hasEnd, hasStart, lvlAngle, startAngle, endAngle, Draw_Mode):
    byte0     = struct.pack('B', hasLvl << 2 | hasEnd << 1 | hasStart)
    byte1_4   = struct.pack('f', lvlAngle)
    byte5_8   = struct.pack('f', startAngle)
    byte9_12  = struct.pack('f', endAngle)
    byte13    = struct.pack('B', Draw_Mode)
    byte14_19 = b'\x00\x00\x00\x00\x00\x00'
    uartBuf = byte0 + byte1_4 + byte5_8 + byte9_12 + byte13 + byte14_19
    return uartBuf

def serial_write(data):
    knob_serial.write(data)

def serial_close():
    knob_serial.close()