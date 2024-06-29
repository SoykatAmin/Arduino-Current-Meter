#include "utils.h"

// Storage arrays
volatile uint16_t minuteData[60];
volatile uint16_t hourData[24];
volatile uint16_t dayData[30];
volatile uint16_t monthData[12];

// Variables
volatile uint8_t minuteIndex = 0;
volatile uint8_t hourIndex = 0;
volatile uint8_t dayIndex = 0;
volatile uint8_t monthIndex = 0;
volatile uint16_t currentSample = 0;
volatile uint8_t type = 0;
uint8_t online_mode = 0;
volatile uint8_t online_rate = 0;

char buffer[BUFFER_SIZE];
uint16_t bufferIndex = 0;

/**
 * Stores the current sensor value and updates the data arrays.
 *
 * @param sample The current sensor value to be stored.
 */
void storeCurrent(uint16_t sample) {
    // Read current sensor value
    currentSample = sample;
    UART_putString("Current sample: ");
    char dataBuffer[6];
    itoa(currentSample, dataBuffer, 10);
    UART_putString(dataBuffer);
    UART_putString("\n");
    // Store value in minute data
    minuteData[minuteIndex++] = currentSample;
    if (minuteIndex >= 60) {
        minuteIndex = 0;

        // Average minute data to hour data
        uint32_t sum = 0;
        for (uint8_t i = 0; i < 60; i++) {
            sum += minuteData[i];
        }
        hourData[hourIndex++] = sum / 60;
        if (hourIndex >= 24) {
            hourIndex = 0;

            // Average hour data to day data
            sum = 0;
            for (uint8_t i = 0; i < 24; i++) {
                sum += hourData[i];
            }
            dayData[dayIndex++] = sum / 24;
            if (dayIndex >= 30) {
                dayIndex = 0;

                // Average day data to month data
                sum = 0;
                for (uint8_t i = 0; i < 30; i++) {
                    sum += dayData[i];
                }
                monthData[monthIndex++] = sum / 30;
                if (monthIndex >= 12) {
                    monthIndex = 0;
                }
            }
        }
    }
}

/**
 * Handles the serial command received from the PC.
 *
 * @param command The command character received from the PC.
 */
void handleSerial(char command) {
    uint16_t space = 0;
    switch (command) {
        case 'o':  // Set online mode
            // Implementation for online mode
            online_mode = 1;
            char temp[10];
            UART_getString(temp);
            online_rate = atoi(temp);
            uartFlush();
            break;
        case 'f':  // Set offline mode
            // Implementation for offline mode
            online_mode = 0;
            online_rate = 0;
            break;
        case 'c':  // Clear statistics
            cli(); // Disable interrupts to safely clear data
            memset((void*)minuteData, 0, sizeof(minuteData));
            memset((void*)hourData, 0, sizeof(hourData));
            memset((void*)dayData, 0, sizeof(dayData));
            memset((void*)monthData, 0, sizeof(monthData));
            sei(); // Re-enable interrupts
            break;
        case 'q':  // Query statistics
            // Send statistics data to the PC

            type = 1;
            // 60 * 5 = 300 bytes
            for (uint8_t i = 0; i < 60; i++) {
                addToBuffer(minuteData[i]);
            }
            type = 2;
            // 24 * 5 = 120 bytes
            for (uint8_t i = 0; i < 24; i++) {
                addToBuffer(hourData[i]);
            }
            type = 3;
            // 30 * 5 = 150 bytes
            for (uint8_t i = 0; i < 30; i++) {
                addToBuffer(dayData[i]);
            }
            type = 4;
            // 12 * 5 = 60 bytes
            for (uint8_t i = 0; i < 12; i++) {
                addToBuffer(monthData[i]);
            }
            UART_putString(buffer);
            bufferIndex = 0;

            // Total: 300 + 120 + 150 + 60 = 630 bytes

            // Similarly send hourData, dayData, and monthData
            break;
        default:
            break;
    }
}

/**
 * Adds the given data to the buffer.
 * 
 * @param data The data to be added to the buffer.
 */
void addToBuffer(uint16_t data) {
    char dataBuffer[6];
    itoa(data, dataBuffer, 10);
    uint8_t dataLength = strlen(dataBuffer);
    
    // Check if there is enough space in the buffer
    if (bufferIndex + dataLength + 1 >= BUFFER_SIZE) {
        // Buffer is full, send the buffer and reset the index
        UART_putString(buffer);
        bufferIndex = 0;
    }
    
    // Add the data to the buffer
    for (uint8_t i = 0; i < dataLength; i++) {
        buffer[bufferIndex++] = dataBuffer[i];
    }
    
    // Add separator character '|'
    buffer[bufferIndex++] = '|';
}

/**
 * Flushes the UART receive buffer by reading and discarding any available data.
 */
void uartFlush() {
    while (UCSR0A & (1 << RXC0)) {
        char t = UDR0;
    }
}