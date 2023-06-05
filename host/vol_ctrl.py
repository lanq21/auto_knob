from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
import os

volume = cast(None, POINTER(IAudioEndpointVolume))

vol_tansfer = {
    0: -65.25,   1: -56.99,  2: -51.67,  3: -47.74,  4: -44.62,  5: -42.03,  6: -39.82,  7: -37.89,  8: -36.17,  9: -34.63,
    10: -33.24, 11: -31.96, 12: -30.78, 13: -29.68, 14: -28.66, 15: -27.70, 16: -26.80, 17: -25.95, 18: -25.15, 19: -24.38,
    20: -23.65, 21: -22.96, 22: -22.30, 23: -21.66, 24: -21.05, 25: -20.46, 26: -19.90, 27: -19.35, 28: -18.82, 29: -18.32,
    30: -17.82, 31: -17.35, 32: -16.88, 33: -16.44, 34: -16.00, 35: -15.58, 36: -15.16, 37: -14.76, 38: -14.37, 39: -13.99,
    40: -13.62, 41: -13.26, 42: -12.90, 43: -12.56, 44: -12.22, 45: -11.89, 46: -11.56, 47: -11.24, 48: -10.93, 49: -10.63,
    50: -10.33, 51: -10.04, 52: -9.75, 53: -9.47, 54: -9.19, 55: -8.92, 56: -8.65, 57: -8.39, 58: -8.13, 59: -7.88,
    60: -7.63, 61: -7.38, 62: -7.14, 63: -6.90, 64: -6.67, 65: -6.44, 66: -6.21, 67: -5.99, 68: -5.76, 69: -5.55,
    70: -5.33, 71: -5.12, 72: -4.91, 73: -4.71, 74: -4.50, 75: -4.30, 76: -4.11, 77: -3.91, 78: -3.72, 79: -3.53,
    80: -3.34, 81: -3.15, 82: -2.97, 83: -2.79, 84: -2.61, 85: -2.43, 86: -2.26, 87: -2.09, 88: -1.91, 89: -1.75,
    90: -1.58, 91: -1.41, 92: -1.25, 93: -1.09, 94: -0.93, 95: -0.77, 96: -0.61, 97: -0.46, 98: -0.30, 99: -0.15, 100: 0.0
}

def volume_init():
    global volume
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
    volume = cast(interface, POINTER(IAudioEndpointVolume))

def set_volume(vol):
    vol = int(vol)
    vol = 100 if vol > 100 else 0 if vol < 0 else vol
    volume.SetMasterVolumeLevel(vol_tansfer[vol], None)

def run(angle):
    os.system('cls')
    print("音量调节\n\n")
    print("设置音量:")
    vol = 0 if int(angle / 2.0 - 40.0) < 0 else 100 if int(angle / 2.0 - 40.0) > 100 else int(angle / 2.0 - 40.0)
    print(vol)
    print("\n当前角度:")
    print(angle)
    print("\n无操作 5 秒后自动返回功能选择")
    set_volume(vol)