#pragma once
#include <stdint.h>

/*
    Idea: Use 2 timers. One for sampling every seconds, 
    and one for updating the statistics every minutes.
    We sample the current every second and store the 
    sum of squares of the current in a buffer.
    We will then calculate the RMS value of the current
    every minute and store it in the statistics buffers.
*/ 

volatile long sumOfSquares = 0;
volatile uint16_t sampleCount = 0;

// prototypes

void store_sample(void);
uint16_t read_adc(uint8_t pin);
float get_rms_current(void);