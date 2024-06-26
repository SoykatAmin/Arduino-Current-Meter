#pragma once

#include <stdint.h>
#include <math.h>
#include "sample.h"

float get_rms_current(void){
    float meanSquare = sumOfSquares / (float)sampleCount;
    sumOfSquares = 0;
    sampleCount = 0;
    return sqrt(meanSquare);
}

uint16_t read_adc(uint8_t pin){
    pin &= 0x07;
    ADMUX = (ADMUX & 0xF8) | pin;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}