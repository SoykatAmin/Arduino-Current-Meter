#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERIAL_PORT "/dev/ttyUSB0"
#define BAUD_RATE B19200

extern int online_mode;

int init_serial(const char *port_name);
void close_serial(int serial_port);
void set_online_mode(int serial_port);
void set_offline_mode(int serial_port);
void error_exit(const char *message);
void serial_read(int serial_port, char *buffer, int buffer_size);