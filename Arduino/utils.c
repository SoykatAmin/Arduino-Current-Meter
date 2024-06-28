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

void setupSerial(){
    // Set baud rate
    UBRR0H = (unsigned char)(MYUBRR >> 8);
    UBRR0L = (unsigned char)MYUBRR;
    // Enable receiver and transmitter and receiver interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void sampleCurrent(uint16_t sample) {
    // Read current sensor value
    currentSample = sample;

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

void handleSerial() {
    char command = UDR0; // Read received command

    switch (command) {
        case 'o':  // Set online mode
            // Implementation for online mode
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
            char buffer[3];
            for (uint8_t i = 0; i < 60; i++) {
                //send minuteData[i]
                itoa(minuteData[i], buffer, 10);
                UART_putString(buffer);
                UART_putChar(type);
                UART_putChar(i);
            }
            type = 2;
            for (uint8_t i = 0; i < 24; i++) {
                //send HourData[i]
                itoa(hourData[i], buffer, 10);
                UART_putString(buffer);
                UART_putChar(type);
                UART_putChar(i);
            }
            type = 3;
            for (uint8_t i = 0; i < 30; i++) {
                //send dayData[i]
                itoa(dayData[i], buffer, 10);
                UART_putString(buffer);
                UART_putChar(type);
                UART_putChar(i);
            }
            type = 4;
            for (uint8_t i = 0; i < 12; i++) {
                //send monthData[i]
                itoa(monthData[i], buffer, 10);
                UART_putString(buffer);
                UART_putChar(type);
                UART_putChar(i);
            }

            // Similarly send hourData, dayData, and monthData
            break;
        default:
            break;
    }
}