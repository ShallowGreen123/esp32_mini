#include "uart.h"

uint8_t recv_flag = 0;

static void uart_cmd_oper(int32_t cmd)
{
    if (recv_flag == 0) {
        return;
    }

    switch (cmd) {
        case 0x01: {
            printf("up\n");
        } break;
        case 0x02: {
            printf("down\n");
        } break;
        case 0x03: {
            printf("back\n");
        } break;
        default:
            break;
    }

    recv_flag = 0;
}

static void echo_task(void *arg)
{
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);
    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        // Write data back to the UART

        if (len > 0) {
            recv_flag = 1;
            uart_cmd_oper(data[0]);
            uart_write_bytes(ECHO_UART_PORT_NUM, (const char *)data, len);
        }
    }
}

void uart_init(void)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate  = ECHO_UART_BAUD_RATE,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(ECHO_UART_PORT_NUM, &uart_config);
    uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

    xTaskCreate(echo_task, "uart_echo_task", 4096, NULL, 10, NULL);
}
