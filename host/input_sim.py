from time import sleep
import win32api
import win32con
import os

key_map = {
    'shift': 0x10, 'ctrl': 0x11, 'alt': 0x12,
    'left': 0x25, 'up': 0x26, 'right': 0x27, 'down': 0x28
}

def wheel_up(time):
    for i in range(time * 10):
        win32api.mouse_event(win32con.MOUSEEVENTF_WHEEL, 0, 0, 1)

def wheel_down(time):
    for i in range(time * 10):
        win32api.mouse_event(win32con.MOUSEEVENTF_WHEEL, 0, 0, -1)

def key_press(key):
    win32api.keybd_event(key_map[key], 0, 0, 0)

def key_release(key):
    win32api.keybd_event(key_map[key], 0, win32con.KEYEVENTF_KEYUP, 0)

def key_press_with(key):
    win32api.keybd_event(key_map[key], 0, win32con.KEYEVENTF_EXTENDEDKEY | 0, 0)

def key_release_with(key):
    win32api.keybd_event(key_map[key], 0, win32con.KEYEVENTF_EXTENDEDKEY | win32con.KEYEVENTF_KEYUP, 0)

def key_click(key):
    key_press(key)
    key_release(key)

def key_click_with(key):
    key_press_with(key)
    key_release_with(key)

def wheel_run(angle, speed):
    os.system('cls')
    print("模拟滚轮\n\n")
    print("当前角度:")
    print(angle)
    # print("\n无操作 5 秒后自动返回功能选择")
    if (speed > 15):
        wheel_down(int(speed // 5))
    elif (speed < -15):
        wheel_up(int(-speed // 5))

def key_lr_run(angle):
    os.system('cls')
    print("模拟方向键 ← →\n\n")
    print("当前角度:")
    print(angle)
    # print("\n无操作 5 秒后自动返回功能选择")
    err = int(angle - 180)
    if (err > 20):
        for i in range(err // 10):
            key_click_with('right')
    elif (err < - 20):
        for i in range(-err // 10):
            key_click_with('left')

def key_ud_run(angle):
    os.system('cls')
    print("模拟方向键 ↑ ↓\n\n")
    print("当前角度:")
    print(angle)
    # print("\n无操作 5 秒后自动返回功能选择")
    err = int(angle - 180)
    if (err > 20):
        for i in range(err // 10):
            key_click_with('up')
    elif (err < - 20):
        for i in range(-err // 10):
            key_click_with('down')