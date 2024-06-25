#include "stats.h"

void clear_statistics(void) {
    for (uint8_t i = 0; i < hour_stats; i++) hourStats[i] = 0;
    for (uint8_t i = 0; i < day_stats; i++) dayStats[i] = 0;
    for (uint8_t i = 0; i < month_stats; i++) monthStats[i] = 0;
    for (uint8_t i = 0; i < year_stats; i++) yearStats[i] = 0;
    minuteIndex = hourIndex = dayIndex = monthIndex = 0;
}

void query_statistics(void) {
    // Print out hour
    for (uint8_t i = 0; i < hour_stats; i++) {
        // Print out the hour stats
    }
    // Print out day
    for (uint8_t i = 0; i < day_stats; i++) {
        // Print out the day stats
    }
    // Print out month
    for (uint8_t i = 0; i < month_stats; i++) {
        // Print out the month stats
    }
    // Print out year
    for (uint8_t i = 0; i < year_stats; i++) {
        // Print out the year stats
    }
}