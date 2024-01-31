#ifndef KEY_INCLUDE_H
#define KEY_INCLUDE_H
#include "user.h"


// uart num
#define UART0_TX             (GPIO_NUM_1)
#define UART0_RX             (GPIO_NUM_3)
// #define UART1_TX (GPIO_NUM_10)
// #define UART1_RX (GPIO_NUM_9)
#define UART2_TX             (GPIO_NUM_17)
#define UART2_RX             (GPIO_NUM_16)

#define ECHO_TEST_TXD        (UART0_TX)
#define ECHO_TEST_RXD        (UART0_RX)
#define ECHO_TEST_RTS        (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS        (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM   (UART_NUM_0)
#define ECHO_UART_BAUD_RATE  (115200)

#define BUF_SIZE             (1024)

void uart_init(void);


#endif