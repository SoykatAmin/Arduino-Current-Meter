#include "sample.h"
#include "utils.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile uint16_t current_reading = 0;
volatile uint8_t sec = 0;

void timer1_init(void);
void timer2_init(void);
void timer3_init(void);
ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMPA_vect);
ISR(USART_RX_vect);

int main(void) {

    cli();
    UART_init();
    timer1_init();
    timer2_init();
    init_adc();
    sei(); // Enable global interrupts

    while (1){
        if(sec>=60 && (!online_mode)){
            storeCurrent(avgCurrent);
            avgCurrent = 0;
            numSamples = 0;
            sec = 0;
        }
        if(online_rate == 0){
            UART_putChar('c');
        }
        if(online_mode && online_rate != 0){
            if(sec >= online_rate){
                char avgCurr[10];
                itoa(avgCurrent, avgCurr, 10);
                UART_putString(avgCurr);
                if(numSamples >= 60){
                    avgCurrent = 0;
                    numSamples = 0;
                }
                sec = 0;
            }
        }
    }
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
    //UART_putString("Timer1 \n");
    get_rms();
    sec++;
}

ISR(TIMER2_COMPA_vect) {
    // Read ADC value
    uint16_t adc_value = read_adc();
    update_sample(adc_value);
}

// Serial interrupt routine
ISR(USART0_RX_vect) {
    cli();
    char command = UDR0;
    handleSerial(command);
    sei();
}