#include "sample.h"

/*
    Sampling idea: Calculate RMS value of tension every minute.
    Than we will calculate current RMS value by multiplying the
    tension RMS value by the calibration const.
    We will then transmit the current RMS value to the UART.
    We will use the ADC to sample the value every second.
*/

volatile long sumOfSquares = 0;
volatile uint16_t sampleCount = 0;

/**
 * Initializes the ADC (Analog-to-Digital Converter) module.
 * This function sets the reference voltage to AVCC, sets the prescaler to 128,
 * and enables the ADC.
 */
void init_adc(void){
    // Set the ADC port as input
    PORTA = 0x00;
    // Set reference voltage to AVCC
    ADMUX |= (1 << REFS0);
    // Seleziona il canale ADC0 (porta A0)
    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);
    // Abilita l'ADC e imposta il prescaler a 128 (16 MHz / 128 = 125 kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/**
 * Reads the analog value from the specified ADC channel.
 *
 * @param channel The ADC channel to read from (0-7).
 * @return The 16-bit ADC value.
 */
uint16_t read_adc(){
    ADCSRA |= (1 << ADSC);
    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));
    uint16_t adcValue = ADC;
    return adcValue;
}

// Calculates the root mean square (RMS) tension value.
// Resets the sum of squares and sample count variables.
// Returns the RMS tension value.
float get_rms(void){
    float meanSquare = sumOfSquares / (float)sampleCount;
    sumOfSquares = 0;
    sampleCount = 0;
    return sqrt(meanSquare);
}

void transmit_current_reading(uint16_t current_reading) {
    char buffer[5];
    sprintf(buffer, "%04X", current_reading);
    UART_putString((uint8_t*)buffer);
}