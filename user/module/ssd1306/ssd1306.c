
#include "py/runtime.h" // Include MicroPython API.
#include "py/mphal.h"   // Used to get the time in the Timer class example1.

#include "ssd1306.h"
#include "font8x8_basic.h"

STATIC mp_obj_t mpy_ssd1306_init(void)
{
    SSD1306_t dev;
    int center, top, bottom;
    char lineChar[20];
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	ssd1306_display_text_x3(&dev, 0, "Hello", 5, false);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(ssd1306_init_obj, mpy_ssd1306_init);

// This is the function which will be called from Python as cexample1.add_ints(a, b).
STATIC mp_obj_t example1_add_ints(mp_obj_t a_obj, mp_obj_t b_obj)
{
    // Extract the ints from the micropython input objects.
    int a = mp_obj_get_int(a_obj);
    int b = mp_obj_get_int(b_obj);

    // Calculate the addition and convert to MicroPython object.
    return mp_obj_new_int(a + b);
}
// Define a Python reference to the function above.
STATIC MP_DEFINE_CONST_FUN_OBJ_2(example1_add_ints_obj, example1_add_ints);

// This structure represents Timer instance objects.
typedef struct _example1_Timer_obj_t
{
    // All objects start with the base.
    mp_obj_base_t base;
    // Everything below can be thought of as instance attributes, but they
    // cannot be accessed by MicroPython code directly. In this example1 we
    // store the time at which the object was created.
    mp_uint_t start_time;
} example1_Timer_obj_t;

// This is the Timer.time() method. After creating a Timer object, this
// can be called to get the time elapsed since creating the Timer.
STATIC mp_obj_t example1_Timer_time(mp_obj_t self_in)
{
    // The first argument is self. It is cast to the *example1_Timer_obj_t
    // type so we can read its attributes.
    example1_Timer_obj_t *self = MP_OBJ_TO_PTR(self_in);

    // Get the elapsed time and return it as a MicroPython integer.
    mp_uint_t elapsed = mp_hal_ticks_ms() - self->start_time;
    return mp_obj_new_int_from_uint(elapsed);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(example1_Timer_time_obj, example1_Timer_time);

// This represents Timer.__new__ and Timer.__init__, which is called when
// the user instantiates a Timer object.
STATIC mp_obj_t example1_Timer_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // Allocates the new object and sets the type.
    example1_Timer_obj_t *self = mp_obj_malloc(example1_Timer_obj_t, type);

    // Initializes the time for this Timer instance.
    self->start_time = mp_hal_ticks_ms();

    // The make_new function always returns self.
    return MP_OBJ_FROM_PTR(self);
}

// This collects all methods and other static class attributes of the Timer.
// The table structure is similar to the module table, as detailed below.
STATIC const mp_rom_map_elem_t example1_Timer_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_time), MP_ROM_PTR(&example1_Timer_time_obj)},
};
STATIC MP_DEFINE_CONST_DICT(example1_Timer_locals_dict, example1_Timer_locals_dict_table);

// This defines the type(Timer) object.
MP_DEFINE_CONST_OBJ_TYPE(
    example1_type_Timer,
    MP_QSTR_Timer,
    MP_TYPE_FLAG_NONE,
    make_new, example1_Timer_make_new,
    locals_dict, &example1_Timer_locals_dict);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t example1_module_globals_table1[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_cexample1)},
    {MP_ROM_QSTR(MP_QSTR_add_ints), MP_ROM_PTR(&example1_add_ints_obj)},
    {MP_ROM_QSTR(MP_QSTR_Timer), MP_ROM_PTR(&example1_type_Timer)},
    {MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&ssd1306_init_obj)},
};
STATIC MP_DEFINE_CONST_DICT(example1_module_globals, example1_module_globals_table1);

// Define module object.
const mp_obj_module_t example1_user_cmodule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&example1_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_cexample1, example1_user_cmodule);
