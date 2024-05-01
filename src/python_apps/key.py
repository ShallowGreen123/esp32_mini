from machine import Pin

key = Pin(0, Pin.IN)

key_val = 0
key_pre_val = 0
while True:
    key_val = key.value()
    if(key_val != key_pre_val):
        key_pre_val = key_val
        if key_pre_val == 0:
            print("key is pressed!")
        else:
            print("key is released!")

