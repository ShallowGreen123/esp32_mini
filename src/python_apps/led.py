from machine import Pin
import time

import cexample
print(cexample.add_ints(1, 3))

led = Pin(2, Pin.OUT)    # create output pin on GPIO0
led.on()                 # set pin to "on" (high) level

while True:
    time.sleep(0.2)
    led.on()
    time.sleep(0.2)
    led.off()
    #print(int(cexample.timer()))