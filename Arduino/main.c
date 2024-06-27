#include "sample.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t current_reading = 0;

void timer1_init(void);
ISR(TIMER1_COMPA_vect);

int main(void) {
    UART_init();
    timer1_init();
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

ISR(TIMER1_COMPA_vect) {
    transmit_current_reading(current_reading);
}