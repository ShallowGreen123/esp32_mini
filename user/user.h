#ifndef USER_INCLUDE_H
#define USER_INCLUDE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

// Peripherals
#include "driver/uart.h"
#include "driver/gpio.h"

void user_task(void *pvParameter);
#endif