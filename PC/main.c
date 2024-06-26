#pragma once
#include "stats.h"
#include "./my_uart/my_uart.h"

int main(){

    char command;
    while (1) {
        switch (command) {
            case 'o':
                // Set to online mode
                break;
            case 'c':
                clear_statistics();
                UART_putString("Statistics Cleared\n");
                break;
            case 'q':
                query_statistics();
                break;
            default:
                UART_putString("Unknown Command\n");
                break;
        }
    }

    return 0;
}