from ast import Not
import time
import board
import digitalio
from time import sleep

def Nothing():
    print()

def Buzz():
    i = 0
    while i < 50:
        buzzer.value = False
        sleep(0.001)
        buzzer.value = True
        sleep(0.001)
        i = i+1
	

def TurnOffAllLeds():
    y_led.value  = False
    b_led.value  = False
    w_led.value  = False
    r_led.value  = False
    g_led.value  = False

def TurnOnAllLeds():
    y_led.value  = True
    b_led.value  = True
    w_led.value  = True
    r_led.value  = True
    g_led.value  = True

def CheckButtons():
    if y_btn.value == True: return 1
    if b_btn.value == True: return 2
    if w_btn.value == True: return 3
    if r_btn.value == True: return 4
    if g_btn.value == True: return 5
    return 0

def CheckButtonsLight():
    if y_btn.value == True: 
        y_led.value = True
        return 1
    if b_btn.value == True: 
        b_led.value = True
        return 2
    if w_btn.value == True: 
        w_led.value = True
        return 3
    if r_btn.value == True: 
        r_led.value = True
        return 4
    if g_btn.value == True: 
        g_led.value = True
        return 5
    return 0

y_led = digitalio.DigitalInOut(board.D4)
b_led = digitalio.DigitalInOut(board.D17)
w_led = digitalio.DigitalInOut(board.D18)
r_led = digitalio.DigitalInOut(board.D27)
g_led = digitalio.DigitalInOut(board.D25)

y_led.direction = digitalio.Direction.OUTPUT
b_led.direction = digitalio.Direction.OUTPUT
w_led.direction = digitalio.Direction.OUTPUT
r_led.direction = digitalio.Direction.OUTPUT
g_led.direction = digitalio.Direction.OUTPUT

buzzer = digitalio.DigitalInOut(board.D24)
buzzer.direction = digitalio.Direction.OUTPUT

y_btn = digitalio.DigitalInOut(board.D5)
b_btn = digitalio.DigitalInOut(board.D6)
w_btn = digitalio.DigitalInOut(board.D12)
r_btn = digitalio.DigitalInOut(board.D13)
g_btn = digitalio.DigitalInOut(board.D16)

y_btn.direction = digitalio.Direction.INPUT
b_btn.direction = digitalio.Direction.INPUT
w_btn.direction = digitalio.Direction.INPUT
r_btn.direction = digitalio.Direction.INPUT
g_btn.direction = digitalio.Direction.INPUT

y_btn.pull = digitalio.Pull.DOWN
b_btn.pull = digitalio.Pull.DOWN
w_btn.pull = digitalio.Pull.DOWN
r_btn.pull = digitalio.Pull.DOWN
g_btn.pull = digitalio.Pull.DOWN


print("Starting!")

#while True:    
#    button = CheckButtonsLight()
#    if (button != 0):
#        print(button)

while True:    
    print(CheckButtons())
    Buzz()
    TurnOffAllLeds()
    y_led.value  = True
    while CheckButtons() != 1:
        Nothing()
    y_led.value  = False

    b_led.value  = True
    while CheckButtons() != 2:
        Nothing()
    b_led.value  = False

    w_led.value  = True
    while CheckButtons() != 3:
        Nothing()
    w_led.value  = False

    r_led.value  = True
    while CheckButtons() != 4:
        Nothing()
    r_led.value  = False

    g_led.value  = True
    while CheckButtons() != 5:
        Nothing()
    g_led.value  = False
