#include <stdio.h>
#include <stdlib.h>
#include "../include/stats.h"
#include "../include/utils.h"

int main(){
    int serial_port = init_serial(SERIAL_PORT);

    while (1) {
        printf("Enter command (o=online, c=clear, q=query): ");
        char cmd[10];
        fgets(cmd, sizeof(cmd), stdin);
        switch (cmd[0]) {
            case 'o':
                set_online_mode(serial_port, 1);
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