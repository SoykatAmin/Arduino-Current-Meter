#include "../include/utils.h"

int online_mode = 0;
char bufferFinal[BUFFER_SIZE];
int bufferIndex = 0;
int online_rate = 0;

/**
 * Prints an error message and exits the program with a failure status.
 *
 * @param message The error message to be printed.
 */
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * Flushes the serial input and output buffers.
 *
 * This function flushes the input and output buffers of the specified serial port.
 *
 * @param fd The file descriptor of the serial port.
 */
void serialFlush(int fd) {
    if(tcflush(fd, TCIFLUSH) != 0) {
        error_exit("tcflush");
    }
}

/**
 * Initializes the serial port with the specified port name.
 * 
 * @param port_name The name of the serial port to initialize.
 * @return The file descriptor of the opened serial port, or -1 if an error occurred.
 */
int init_serial(const char *port_name){
    int serial_port = open(port_name, O_RDWR);
    if (serial_port == -1) {
        error_exit("Error opening the serial port");
    }
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr(serial_port, &tty) != 0) {
        error_exit("Error getting the serial port attributes");
    }

    // Configure serial port settings
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
    
    // Clear input and output buffers
    serialFlush(serial_port);
    
    return serial_port;
}

/**
 * Sets the online mode for the specified serial port.
 *
 * @param serial_port The serial port to set the online mode for.
 */
void set_online_mode(int serial_port) {
    serialFlush(serial_port);
    const char command = 'o';
    online_mode = 1;
    write(serial_port, &command, 1);
}

/**
 * Sets the device to offline mode.
 *
 * @param serial_port The serial port to communicate with the device.
 */
void set_offline_mode(int serial_port) {
    serialFlush(serial_port);
    const char command = 'f';
    online_mode = 0;
    write(serial_port, &command, 1);
}

/**
 * Reads data from a serial port and performs certain operations based on the received data.
 * 
 * @param args A pointer to the serial port number.
 * @return NULL
 */
void* serial_read(void* args){
    int serial_port = *(int*)args;
    int temp = 0;
    char buffer[BUFFER_SIZE];
    while (!online_mode) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = read(serial_port, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            //store_statistics(buffer);
            for (int i = 0; i < n; i++) {
                if (buffer[i] != '\n' || buffer[i] != '\r' || buffer[i] != '\0') {
                    bufferFinal[bufferIndex] = buffer[i];
                    bufferIndex++;
                }
                if (buffer[i] == '|'){
                    temp++;
                }
                if(temp == 126) {
                    bufferFinal[bufferIndex] = '\0';
                    bufferIndex = 0;
                    temp = 0;
                    break;
                }
            }
            int num = isReady(bufferFinal);
            if(num == 126){
                clear_local_statistics();
                sendStatistics(bufferFinal);
                memset(bufferFinal, 0, BUFFER_SIZE);
                bufferIndex = 0;
            }
        }
    }
    while(online_mode){
        memset(buffer, 0, BUFFER_SIZE);
        int n = read(serial_port, buffer, BUFFER_SIZE - 1);
        if (n > 0) {
            if(buffer[0] != 'c'){
                printf("Sample: %s\n", buffer);
            }
        }
    }
    serialFlush(serial_port);
    return NULL;
}

/**
 * Sends a command to a file descriptor.
 *
 * @param fd The file descriptor to send the command to.
 * @param command The command to send.
 */
void sendCommand(int fd, const char *command) {
    write(fd, command, strlen(command));
}

/**
 * Counts the number of substrings separated by '|' in the given input string.
 *
 * @param input The input string to be processed.
 * @return The number of substrings in the input string.
 */
int isReady(const char* input){
    char* inputCopy = strdup(input);
    if (!inputCopy) {
        error_exit("strdup failed");
    }
    char* token = strtok(inputCopy, "|");
    int num = 0;
    while (token != NULL) {
        //processSubstring(token);
        token = strtok(NULL, "|");
        num++;
    }

    free(inputCopy);
    return num;
}

/**
 * Sends statistics to be stored.
 *
 * @param input The input string containing the statistics.
 */
void sendStatistics(const char* input){
    char* inputCopy = strdup(input);
    if (!inputCopy) {
        error_exit("strdup failed");
    }
    char* token = strtok(inputCopy, "|");
    while (token != NULL) {
        store_statistics(token);
        token = strtok(NULL, "|");
    }
    free(inputCopy);
}
