#include "driver/gpio.h"
// Include MicroPython API.
#include "py/runtime.h"

// Used to get the time in the Timer class example.
#include "py/mphal.h"   

#define BLINK_GPIO 2

STATIC mp_obj_t led_on(void)
{
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(BLINK_GPIO, 1);
    return mp_const_true;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(led_on_obj, led_on);

STATIC mp_obj_t led_off(void)
{
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(BLINK_GPIO, 0);
    return mp_const_true;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(led_off_obj, led_off);

STATIC mp_obj_t led_blink(void)
{
    int level = gpio_get_level(BLINK_GPIO);
    gpio_set_level(BLINK_GPIO, !level);
    return mp_const_true;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(led_blink_obj, led_blink);

STATIC const mp_rom_map_elem_t mpy_led_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
    { MP_ROM_QSTR(MP_QSTR_on),       MP_ROM_PTR(&led_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off),      MP_ROM_PTR(&led_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_blink),    MP_ROM_PTR(&led_blink_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mpy_led_local_dict, mpy_led_local_dict_table);

// Define module object.
const mp_obj_module_t example_usermod_led = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mpy_led_local_dict,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_led, example_usermod_led);
