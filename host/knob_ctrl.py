import input_sim
import vol_ctrl
import knob_serial
import knob_mode
from time import sleep

first_call = True
last_angle = 0
wait_count = 0

hasLvl = False
hasEnd = False
hasStart = False
lvlAngle = 0.0
startAngle = 0.0
endAngle = 0.0
Draw_Mode = 0

mode = knob_mode.Mode_Type(knob_mode.Mode_Type.select)

vol_ctrl.volume_init()

if (knob_serial.serial_open("COM26", 115200)):

    while (True):

        data = knob_serial.serial_read()
        if (data):
            [angle, speed] = knob_serial.serial_decode(data)
            if(angle):

                if (mode == knob_mode.Mode_Type.select):
                    hasLvl = True
                    hasEnd = False
                    hasStart = False
                    lvlAngle = 72.0
                    startAngle = 0.0
                    endAngle = 288.0
                    Draw_Mode = 0
                    knob_mode.run(angle)
                    # 检测到按下 Enter
                    if (input_sim.win32api.GetAsyncKeyState(13)):
                        mode = knob_mode.last_choice

                elif (mode == knob_mode.Mode_Type.volue):
                    hasLvl = False
                    hasEnd = True
                    hasStart = True
                    lvlAngle = 200.0
                    startAngle = 80.0
                    endAngle = 280.0
                    Draw_Mode = 1
                    vol_ctrl.run(angle)

                elif (mode == knob_mode.Mode_Type.wheel):
                    hasLvl = True
                    hasEnd = False
                    hasStart = False
                    lvlAngle = 1.0
                    startAngle = 0.0
                    endAngle = 0.0
                    Draw_Mode = 2
                    input_sim.wheel_run(angle, speed)

                elif (mode == knob_mode.Mode_Type.key_lr):
                    hasLvl = False
                    hasEnd = True
                    hasStart = True
                    lvlAngle = 0.0
                    startAngle = 180.0
                    endAngle = 180.0
                    Draw_Mode = 3
                    input_sim.key_lr_run(angle)

                elif (mode == knob_mode.Mode_Type.key_ud):
                    hasLvl = False
                    hasEnd = True
                    hasStart = True
                    lvlAngle = 0.0
                    startAngle = 180.0
                    endAngle = 180.0
                    Draw_Mode = 4
                    input_sim.key_ud_run(angle)

        knob_serial.serial_write(knob_serial.data_pack(hasLvl, hasEnd, hasStart, lvlAngle, startAngle, endAngle, Draw_Mode))

        if (input_sim.win32api.GetAsyncKeyState(27)):
            mode = knob_mode.Mode_Type.select