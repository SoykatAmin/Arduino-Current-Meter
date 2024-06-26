#include "../include/stats.h"

// Definizione dello storage per le statistiche
float hourStats[HOUR_STATS];
float dayStats[DAY_STATS];
float monthStats[MONTH_STATS];
float yearStats[YEAR_STATS];

// Definizione degli indici per le statistiche
uint8_t minuteIndex = 0;
uint8_t hourIndex = 0;
uint8_t dayIndex = 0;
uint8_t monthIndex = 0;

void clear_statistics(void) {
    for (uint8_t i = 0; i < HOUR_STATS; i++) hourStats[i] = 0;
    for (uint8_t i = 0; i < DAY_STATS; i++) dayStats[i] = 0;
    for (uint8_t i = 0; i < MONTH_STATS; i++) monthStats[i] = 0;
    for (uint8_t i = 0; i < YEAR_STATS; i++) yearStats[i] = 0;
    minuteIndex = hourIndex = dayIndex = monthIndex = 0;
}

void query_statistics(void) {
    // Print out hour
    for (uint8_t i = 0; i < HOUR_STATS; i++) {
        // Print out the hour stats
    }
    // Print out day
    for (uint8_t i = 0; i < DAY_STATS; i++) {
        // Print out the day stats
    }
    // Print out month
    for (uint8_t i = 0; i < MONTH_STATS; i++) {
        // Print out the month stats
    }
    // Print out year
    for (uint8_t i = 0; i < YEAR_STATS; i++) {
        // Print out the year stats
    }
}