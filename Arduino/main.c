#include "sample.h"
#include <util/delay.h>

int main(void) {
    UART_init();
    uint16_t current_reading = 0;
    while (1) {
        uint8_t sample_flag = 1;
        if (sample_flag) {
            sample_flag = 0;
            current_reading++;
            transmit_current_reading(current_reading);
        }
        _delay_ms(1000);
    }
    return 0;
}