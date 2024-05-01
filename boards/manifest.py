freeze("$(PORT_DIR)/modules")
# freeze("$(PORT_DIR)/src/python_apps")
include("$(MPY_DIR)/extmod/uasyncio")

# Useful networking-related packages.
require("bundle-networking")

# Require some micropython-lib modules.
require("dht")
require("ds18x20")
require("neopixel")
require("onewire")
require("umqtt.robust")
require("umqtt.simple")
require("upysh")
require("ssd1306")

