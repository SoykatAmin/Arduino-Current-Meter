#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include "./my_uart/my_uart.h"
#include <stdint.h>
#include <math.h>

/*
    1000:1 ratio. 1A -> 1mA
    50 ohm resistor
    1mA * 50 ohm = 50mV
    ADC value = 50mV / 5V * 1024 = 10.24
    Calibration constant = 1 / 10.24 = 0.09765625
*/
#define CALIBRATION_CONST 355.55

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

void init_adc(void);
uint16_t read_adc();
float get_rms(void);
void transmit_current_reading(uint16_t current_reading);
