#pragma once
#include "sample.h"
#include "./my_uart/my_uart.h"

#define BAUD 19200
#define MYUBRR F_CPU/16/BAUD-1

int main(void) {

    while (1) {
        sample_flag = 1;
        if (sample_flag) {
            sample_flag = 0;
            current_reading = 65520;
            UART_putString(current_reading >> 8);
            UART_putString(current_reading & 0xFF);
        }
        _delay(1000);
    }
    return 0;
}