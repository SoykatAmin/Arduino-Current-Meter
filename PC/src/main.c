#include <stdio.h>
#include <stdlib.h>
#include "../include/stats.h"
#include "../include/utils.h"
#include<unistd.h>

#define BUFFER_SIZE 256

int main(){
    int serial_port = init_serial(SERIAL_PORT);
    printf("Enter command (o=online, c=clear, q=query): ");
    char cmd[10];
    fgets(cmd, sizeof(cmd), stdin);
    while (1) {
        
        switch (cmd[0]) {
            case 'o':
                set_online_mode(serial_port);
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
        if(online_mode){
            char buffer[BUFFER_SIZE];
            serial_read(serial_port, buffer, BUFFER_SIZE);
            if(buffer[0] != '\0')
                printf("Received: %s\n", buffer);
        }
    }

    return 0;
}