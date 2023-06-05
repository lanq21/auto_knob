from enum import Enum
import os

class Mode_Type(Enum):
    select = 0
    volue = 1
    wheel = 2
    key_lr = 3
    key_ud = 4

last_choice = Mode_Type.select

def run(angle):
    global last_choice
    step = int(angle + 36) // 72
    step = 0 if step > 4 else step
    # if ((step == 0) and last_choice != Mode_Type.select):
    if(step == 0):
        os.system('cls')
        print("功能选择\n")
        print(" -> 0. 无控制\n")
        print("    1. 调节音量\n")
        print("    2. 模拟滚轮\n")
        print("    3. 模拟方向键 ← →\n")
        print("    4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)
        last_choice = Mode_Type.select
    # elif ((step == 1) and last_choice != Mode_Type.volue):
    elif(step == 1):
        os.system('cls')
        print("功能选择\n")
        print("    0. 无控制\n")
        print(" -> 1. 调节音量\n")
        print("    2. 模拟滚轮\n")
        print("    3. 模拟方向键 ← →\n")
        print("    4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)
        last_choice = Mode_Type.volue
    # elif ((step == 2) and last_choice != Mode_Type.wheel):
    elif(step == 2):
        os.system('cls')
        print("功能选择\n")
        print("    0. 无控制\n")
        print("    1. 调节音量\n")
        print(" -> 2. 模拟滚轮\n")
        print("    3. 模拟方向键 ← →\n")
        print("    4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)
        last_choice = Mode_Type.wheel
    # elif ((step == 3) and last_choice != Mode_Type.key_lr):
    elif(step == 3):
        os.system('cls')
        print("功能选择\n")
        print("    0. 无控制\n")
        print("    1. 调节音量\n")
        print("    2. 模拟滚轮\n")
        print(" -> 3. 模拟方向键 ← →\n")
        print("    4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)
        last_choice = Mode_Type.key_lr
    # elif ((step == 4) and last_choice != Mode_Type.key_ud):
    elif ((step == 4)):
        os.system('cls')
        print("功能选择\n")
        print("    0. 无控制\n")
        print("    1. 调节音量\n")
        print("    2. 模拟滚轮\n")
        print("    3. 模拟方向键 ← →\n")
        print(" -> 4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)
        last_choice = Mode_Type.key_ud
    else:
        os.system('cls')
        print("功能选择\n")
        print("    0. 无控制\n")
        print("    1. 调节音量\n")
        print("    2. 模拟滚轮\n")
        print("    3. 模拟方向键 ← →\n")
        print("    4. 模拟方向键 ↑ ↓\n\n")
        print("\n当前角度:")
        print(angle)