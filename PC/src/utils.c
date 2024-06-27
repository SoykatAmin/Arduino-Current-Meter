#include "../include/utils.h"

int online_mode = 0;

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int init_serial(const char *port_name){
    int serial_port = open(port_name, O_RDWR);
    if (serial_port == -1) {
        error_exit("Error opening the serial port");
    }
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        error_exit("Error getting the serial port attributes");
    }

    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE; // Clear the size bits
    tty.c_cflag |= CS8; // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS; // No hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable reading and ignore control lines

    tty.c_lflag &= ~ICANON; // Disable canonical mode
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable newline echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable special handling of received bytes

    tty.c_oflag &= ~OPOST; // Disable output processing
    tty.c_oflag &= ~ONLCR; // Disable newline conversion

    tty.c_cc[VTIME] = 0; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received
    tty.c_cc[VMIN] = 0; // Return as soon as any data is received

    cfsetispeed(&tty, BAUD_RATE);
    cfsetospeed(&tty, BAUD_RATE);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        close(serial_port);
        error_exit("Error setting the serial port attributes");
    }
    return serial_port;
}

void set_online_mode(int serial_port) {
    const char command = 'o';
    online_mode = 1;
    write(serial_port, &command, 1);
}

void set_offline_mode(int serial_port) {
    const char command = 'f';
    online_mode = 0;
    write(serial_port, &command, 1);
}

void* serial_read(void* args){
    printf("Serial Read Thread Started\n");
    int serial_port = *(int*)args;
    char buffer[BUFFER_SIZE];
    while (online_mode) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = read(serial_port, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            store_statistics(buffer);
            printf("Received: %s\n", buffer);
        }
    }
    return NULL;
}


