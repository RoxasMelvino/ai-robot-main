import evdev
import serial
import time
from datetime import datetime

# ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
# time.sleep(2)
# print(ser.name)

# the values of the joysticks and triggers depend on the controller!
xb1_js_max = (2 ** 16) - 1
ds4_js_max = (2 ** 8) - 1

js_max = xb1_js_max
js_center = js_max / 2
js_raw_x = js_center
js_raw_y = js_center
js_raw_w = js_center
deadzone_thresh = 0.10

#search for devices
devices = [evdev.InputDevice(path) for path in evdev.list_devices()] 
for device in devices: 
    print(device.name)
    if (device.name == "Wireless Controller"):
        controller_path = device.path
    elif (device.name == "Xbox Wireless Controller"):
        controller_path = device.path
              
controller = evdev.InputDevice(controller_path)

for event in controller.read_loop():
    if event.type == evdev.ecodes.EV_ABS:
        button_name = evdev.ecodes.ABS[event.code]
        if (button_name == "ABS_X"):
            js_raw_x = event.value
            print(js_raw_x)
        elif (button_name == "ABS_Y"):
            js_raw_y = event.value
        elif (button_name == "ABS_RX"): # right joystick x axis for ds4
            js_raw_w = event.value
        elif (button_name == "ABS_Z"): # right joystick x axis for xb1
            js_raw_w = event.value
            
            
    if event.type == evdev.ecodes.EV_SYN :
        # we need the center to be 0, otherwise the motors will move by themselves
        x_percent = round((js_raw_x - js_center) / (js_max - js_center), 2)
        y_percent = round((js_raw_y - js_center) / (js_max - js_center), 2) * -1
        w_percent = round((js_raw_w - js_center) / (js_max - js_center), 2)
        
        if (abs(x_percent) < deadzone_thresh) : x_percent = 0.00
        if (abs(y_percent) < deadzone_thresh) : y_percent = 0.00
        if (abs(w_percent) < deadzone_thresh) : w_percent = 0.00
        
        action_space = f"{w_percent},{x_percent},{y_percent}\n"
        print(action_space)
        # ser.write(action_space.encode())
        # while ser.in_waiting > 0 :
        #     print("Arduino Serial", ser.readline().decode('utf-8'))
        
ser.close()







 






        
        





