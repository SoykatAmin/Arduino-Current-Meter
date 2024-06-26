#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyUSB0"
#define BAUD_RATE B19200

int init_serial(const char *port_name);
void close_serial(int serial_port);
void set_online_mode(int serial_port, int interval);
void set_offline_mode(int serial_port);
void error_exit(const char *message);