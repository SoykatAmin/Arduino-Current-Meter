#include "sample.h"
#include "utils.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile uint16_t current_reading = 0;

void timer1_init(void);
void timer2_init(void);
ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMPA_vect);

int main(void) {

    cli();
    UART_init();
    timer1_init();
    timer2_init();
    init_adc();
    sei(); // Enable global interrupts

    while (1); //polling
    return 0;
}

void timer1_init(void) {
    // Set CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);
    // Set compare value for 1 Hz interrupt (assuming 16 MHz clock and 1024 prescaler)
    OCR1A = 15624;
    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    // Start Timer1 with 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void timer2_init(void) {
    // Set CTC mode (Clear Timer on Compare Match)
    TCCR2A |= (1 << WGM21);
    // Set compare value for 1 Hz interrupt (assuming 16 MHz clock and 1024 prescaler)
    OCR2A = 249;
    // Enable Timer2 compare interrupt
    TIMSK2 |= (1 << OCIE2A);
    // Start Timer2 with 1024 prescaler
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
}

ISR(TIMER1_COMPA_vect) {
    // Calculate RMS current value
    float rms_current = get_rms();
}

ISR(TIMER2_COMPA_vect) {
    // Read ADC value
    uint16_t adc_value = read_adc();
    update_sample(adc_value);
}

// Serial interrupt routine
ISR(USART_RX_vect) {
    handleSerial();
}