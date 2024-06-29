#include <stdio.h>
#include <stdlib.h>
#include "../include/stats.h"
#include "../include/utils.h"
#include <pthread.h>

int main(){
    int serial_port = init_serial(SERIAL_PORT);
    serialFlush(serial_port);
    char cmd[10];
    int open = 1;

    pthread_t thread;
    printf("PC Client Initialized\n");

    while (open) {
        printf("Enter command (o=online, f=offline, c=clear, q=query, p=print, e=exit): ");
        fgets(cmd, sizeof(cmd), stdin);
        switch (cmd[0]) {
            case 'o':
                set_online_mode(serial_port);
                printf("Select sampling rate (1-255): ");
                char input[255];
                fgets(input, sizeof(input), stdin);
                online_rate = atoi(input);
                if(online_rate < 1 || online_rate > 255){
                    printf("Invalid sampling rate\n");
                    break;
                }
                sendCommand(serial_port, input);
                if(pthread_create(&thread, NULL, serial_read, (void *)&serial_port)){
                    error_exit("Error creating thread");
                }
                break;
            case 'f':
                set_offline_mode(serial_port);
                pthread_join(thread, NULL);
                break;
            case 'c':
                if(online_mode){
                    printf("Cannot clear statistics in online mode. Set offline.\n");
                    break;
                }
                clear_statistics(serial_port);
                printf("Statistics Cleared\n");
                break;
            case 'q':
                if(online_mode){
                    printf("Cannot query statistics in online mode. Set offline.\n");
                    break;
                }
                query_statistics(serial_port);
                break;
            case 'p':
                if(online_mode){
                    printf("Cannot query statistics in online mode. Set offline.\n");
                    break;
                }
                print_statistics();
                break;
            case 'e':
                open = 0;
                set_offline_mode(serial_port);
                break;
            default:
                printf("Unknown Command\n");
                break;
        }
    }
    
    pthread_join(thread, NULL);
    serialFlush(serial_port);
    close(serial_port);
    return 0;
}