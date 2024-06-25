#include "stats.h"

void clear_statistics(void) {
    for (uint8_t i = 0; i < HOUR_STATS; i++) hourStats[i] = 0;
    for (uint8_t i = 0; i < DAY_STATS; i++) dayStats[i] = 0;
    for (uint8_t i = 0; i < MONTH_STATS; i++) monthStats[i] = 0;
    for (uint8_t i = 0; i < YEAR_STATS; i++) yearStats[i] = 0;
    minuteIndex = hourIndex = dayIndex = monthIndex = 0;
}