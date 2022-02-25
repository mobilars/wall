#!/usr/bin/python3

import RPi.GPIO as GPIO
import time
from time import sleep

clk = 40
data = 38

i = 8;


GPIO.setmode(GPIO.BOARD)
GPIO.setup(clk, GPIO.OUT)
GPIO.setup(data, GPIO.OUT)

while 1: 
    GPIO.output(data, GPIO.HIGH)
    sleep(0.1)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.1)

    GPIO.output(data, GPIO.LOW)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 0
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    # Clock
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 1
    GPIO.output(data, GPIO.LOW)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 2
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 3
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 4
    GPIO.output(data, GPIO.LOW)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 5
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 6
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set bit 7
    GPIO.output(data, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.05)
    GPIO.output(clk, GPIO.LOW)
    sleep(0.05)

    # Set end 
    GPIO.output(data, GPIO.LOW)
    sleep(0.1)
    GPIO.output(clk, GPIO.HIGH)
    sleep(0.1)
    GPIO.output(data, GPIO.HIGH)
    sleep(0.1)


GPIO.cleanup()
