#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./my_uart/my_uart.h"

#define BUFFER_SIZE 1000

// Storage arrays
extern volatile uint16_t minuteData[];
extern volatile uint16_t hourData[];
extern volatile uint16_t dayData[];
extern volatile uint16_t monthData[];

// Variables
extern volatile uint8_t minuteIndex;
extern volatile uint8_t hourIndex;
extern volatile uint8_t dayIndex;
extern volatile uint8_t monthIndex;
extern volatile uint16_t currentSample;

// Function Prototypes
void storeCurrent(uint16_t sample);
void handleSerial(char command);
void addToBuffer(uint16_t data);