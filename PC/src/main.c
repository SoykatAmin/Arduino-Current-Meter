#include <stdio.h>
#include <stdlib.h>
#include "../include/stats.h"
#include "../include/utils.h"
#include <pthread.h>

int main(){
    int serial_port = init_serial(SERIAL_PORT);
    char cmd[10];
    int open = 1;

    pthread_t thread;
    printf("PC Client Initialized\n");

    while (open) {
        printf("Enter command (o=online, f=offline, c=clear, q=query, e=exit): ");
        fgets(cmd, sizeof(cmd), stdin);
        switch (cmd[0]) {
            case 'o':
                if(!online_mode){
                    set_online_mode(serial_port);
                    if(pthread_create(&thread, NULL, serial_read, (void *)&serial_port)){
                        error_exit("Error creating thread");
                    }
                }
                break;
            case 'f':
                set_offline_mode(serial_port);
                break;
            case 'c':
                clear_statistics();
                printf("Statistics Cleared\n");
                break;
            case 'q':
                query_statistics();
                break;
            case 'e':
                open = 0;
                online_mode = 0;
                break;
            default:
                printf("Unknown Command\n");
                break;
        }
    }
    
    pthread_join(thread, NULL);
    close(serial_port);
    return 0;
}