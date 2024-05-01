from machine import Pin, I2C
from ssd1306 import SSD1306_I2C
import time

i2c = I2C(sda=Pin(21), scl=Pin(22))
i2c.scan()

oled = SSD1306_I2C(128, 64, i2c)
oled.fill(1)
oled.show()

time.sleep(1)

oled.fill(0)
oled.show()

oled.fill_rect(10, 10, 107, 43, 1)  

oled.show()