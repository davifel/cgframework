import paho.mqtt.client as mqtt
#import json, math, threading, os
import ctypes
from ctypes import wintypes
#import time
#import threading

user32 = ctypes.WinDLL('user32', use_last_error=True)

INPUT_MOUSE    = 0
INPUT_KEYBOARD = 1
INPUT_HARDWARE = 2

KEYEVENTF_EXTENDEDKEY = 0x0001
KEYEVENTF_KEYUP       = 0x0002
KEYEVENTF_UNICODE     = 0x0004
KEYEVENTF_SCANCODE    = 0x0008

MAPVK_VK_TO_VSC = 0

# msdn.microsoft.com/en-us/library/dd375731
VK_TAB  = 0x09
VK_MENU = 0x12

A = 0x41
S = 0x53
W = 0x57
D = 0x44

J = 0x4A
K = 0x4B
I = 0x49
L = 0x4C
key = {'A':A,'S':S,'W':W,'D':D,'J':J,'K':K,'I':I,'L':L}

# C struct definitions

wintypes.ULONG_PTR = wintypes.WPARAM

class MOUSEINPUT(ctypes.Structure):
    _fields_ = (("dx",          wintypes.LONG),
                ("dy",          wintypes.LONG),
                ("mouseData",   wintypes.DWORD),
                ("dwFlags",     wintypes.DWORD),
                ("time",        wintypes.DWORD),
                ("dwExtraInfo", wintypes.ULONG_PTR))

class KEYBDINPUT(ctypes.Structure):
    _fields_ = (("wVk",         wintypes.WORD),
                ("wScan",       wintypes.WORD),
                ("dwFlags",     wintypes.DWORD),
                ("time",        wintypes.DWORD),
                ("dwExtraInfo", wintypes.ULONG_PTR))

    def __init__(self, *args, **kwds):
        super(KEYBDINPUT, self).__init__(*args, **kwds)
        # some programs use the scan code even if KEYEVENTF_SCANCODE
        # isn't set in dwFflags, so attempt to map the correct code.
        if not self.dwFlags & KEYEVENTF_UNICODE:
            self.wScan = user32.MapVirtualKeyExW(self.wVk,
                                                 MAPVK_VK_TO_VSC, 0)

class HARDWAREINPUT(ctypes.Structure):
    _fields_ = (("uMsg",    wintypes.DWORD),
                ("wParamL", wintypes.WORD),
                ("wParamH", wintypes.WORD))

class INPUT(ctypes.Structure):
    class _INPUT(ctypes.Union):
        _fields_ = (("ki", KEYBDINPUT),
                    ("mi", MOUSEINPUT),
                    ("hi", HARDWAREINPUT))
    _anonymous_ = ("_input",)
    _fields_ = (("type",   wintypes.DWORD),
                ("_input", _INPUT))

LPINPUT = ctypes.POINTER(INPUT)

def _check_count(result, func, args):
    if result == 0:
        raise ctypes.WinError(ctypes.get_last_error())
    return args

user32.SendInput.errcheck = _check_count
user32.SendInput.argtypes = (wintypes.UINT, # nInputs
                             LPINPUT,       # pInputs
                             ctypes.c_int)  # cbSize

# Functions

def PressKey(hexKeyCode):
    x = INPUT(type=INPUT_KEYBOARD,
              ki=KEYBDINPUT(wVk=hexKeyCode))
    user32.SendInput(1, ctypes.byref(x), ctypes.sizeof(x))

def ReleaseKey(hexKeyCode):
    x = INPUT(type=INPUT_KEYBOARD,
              ki=KEYBDINPUT(wVk=hexKeyCode,
                            dwFlags=KEYEVENTF_KEYUP))
    user32.SendInput(1, ctypes.byref(x), ctypes.sizeof(x))

def on_connect(client, userdata, flags, rc):
    print('connected')
    client.subscribe('sendkey')
    client.publish("cmd2dev9536", "{\"op\": 31, \"simulationTime\": 300, \"frequence\": 18, \"sensorType\": 2}")

last_keys = {0: "W", 1: "A"}
# key_isnull = [False, False]

# def HoldKey(rawkey, keyindex):
#     while (not key_isnull[keyindex]):
#         PressKey(key[rawkey])
#         time.sleep(0.01)
#     ReleaseKey(key[rawkey])

def on_message(client, userdata, msg):
    data = msg.payload.decode("utf-8").strip()
    if msg.topic == 'sendkey':
        global last_keys

        if (data[0] == "S"): data = "D" + data[1]
        if (data[1] == "D"): data = data[0] + "S"
        
        print(data)
        
        for i in range(2):
            if (data[i] != "0"):
                PressKey(key[data[i]])
                last_keys[i] = data[i]
                #key_isnull[i] = False
                #last_keyX = keys[i]
                #t = threading.Thread(target=HoldKey, args=[keys[i], i])
                #t.start()
            else:
                ReleaseKey(key[last_keys[i]])
                #key_isnull[i] = True

        #log = open("data.log", "a")
        #log.write(data + "\n")
        #print(f"write {data}")
        #log.close()


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect('host_here',1883,60)
client.loop_forever()