#include "sample.h"

/*
    Sampling idea: Calculate RMS value of tension every minute.
    Than we will calculate current RMS value by multiplying the
    tension RMS value by the calibration const.
    We will then transmit the current RMS value to the UART.
    We will use the ADC to sample the value every second.
*/

uint16_t maxValue = 0;
uint16_t minValue = 1024;
uint16_t avgCurrent = 0;
uint8_t numSamples = 0;

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

/**
 * Calculates and returns the voltage based on the maximum value obtained from the analog input.
 * 
 * @return The calculated voltage.
 */
uint16_t get_volt(void){
    uint16_t result = ((maxValue-minValue) * 5000.0) / 1024.0;

    maxValue = 0; 
    minValue = 1024;

    return result;
}

uint16_t get_rms(void){
    uint16_t VPP = get_volt();
    uint16_t rms = VPP / (2*sqrt(2));
    /*
    UART_putString((uint8_t*)"RMS: ");
    char buffer[5];
    itoa(rms, buffer, 10);
    UART_putString((uint8_t*)buffer);
    UART_putString((uint8_t*)"\n");
    */

    uint16_t currWire = rms * CALIBRATION_CONST;
    // New average = old average * (n-1)/n + new value /n
    numSamples++;
    avgCurrent = (avgCurrent * (numSamples - 1) + currWire) / numSamples;
    /*
    UART_putString((uint8_t*)"Current: ");
    itoa(currWire, buffer, 10);
    UART_putString((uint8_t*)buffer);
    UART_putString((uint8_t*)"\n");
    */

    return currWire;
}

void transmit_current_reading(uint16_t current_reading) {
    char buffer[5];
    itoa(current_reading, buffer, 10);
    UART_putString((uint8_t*)buffer);
}

void update_sample(uint16_t sample){
    if (sample > maxValue) {
        maxValue = sample;
    }
    if (sample < minValue) {
        minValue = sample;
    }
}