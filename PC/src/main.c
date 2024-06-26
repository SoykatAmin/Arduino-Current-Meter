#include <stdio.h>
#include <stdlib.h>
#include "../include/stats.h"

#define SERIAL_PORT "/dev/ttyUSB0"
#define BAUD_RATE B19600

int main(){

    while (1) {
        printf("Enter command (o=online, c=clear, q=query): ");
        char cmd[10];
        fgets(cmd, sizeof(cmd), stdin);
        switch (cmd[0]) {
            case 'o':
                // Set to online mode
                break;
            case 'c':
                clear_statistics();
                printf("Statistics Cleared\n");
                break;
            case 'q':
                query_statistics();
                break;
            default:
                printf("Unknown Command\n");
                break;
        }
    }

    return 0;
}