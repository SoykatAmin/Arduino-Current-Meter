#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include "./my_uart/my_uart.h"

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
void setupSerial();
void sampleCurrent(uint16_t sample);
void handleSerial();