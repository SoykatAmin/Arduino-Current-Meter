#include "sample.h"

volatile long sumOfSquares = 0;
volatile uint16_t sampleCount = 0;

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

void transmit_current_reading(uint16_t current_reading) {
    char buffer[5];
    sprintf(buffer, "%04X", current_reading);
    UART_putString((uint8_t*)buffer);
}