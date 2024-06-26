#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include "./my_uart/my_uart.h"
#include <stdint.h>
#include <math.h>
/*
    Idea: Use 2 timers. One for sampling every seconds, 
    and one for updating the statistics every minutes.
    We sample the current every second and store the 
    sum of squares of the current in a buffer.
    We will then calculate the RMS value of the current
    every minute and store it in the statistics buffers.
*/ 

extern volatile long sumOfSquares;
extern volatile uint16_t sampleCount;

// prototypes

void store_sample(void);
uint16_t read_adc(uint8_t pin);
float get_rms_current(void);
void transmit_current_reading(uint16_t current_reading);