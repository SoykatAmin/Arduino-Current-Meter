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
    printf("Hour Stats:\n");
    for (uint8_t i = 0; i < HOUR_STATS; i++) {
        // Print out the hour stats
        printf("%f ", hourStats[i]);
    }
    printf("\n");
    // Print out day
    printf("Day Stats:\n");
    for (uint8_t i = 0; i < DAY_STATS; i++) {
        // Print out the day stats
        printf("%f ", dayStats[i]);
    }
    printf("\n");
    // Print out month
    printf("Month Stats:\n");
    for (uint8_t i = 0; i < MONTH_STATS; i++) {
        // Print out the month stats
        printf("%f ", monthStats[i]);
    }
    printf("\n");
    // Print out year
    printf("Year Stats:\n");
    for (uint8_t i = 0; i < YEAR_STATS; i++) {
        // Print out the year stats
        printf("%f ", yearStats[i]);
    }
}

void store_statistics(char *data){
    float value = atof(data);
    hourStats[minuteIndex++] = value;
    if (minuteIndex >= HOUR_STATS) {
        minuteIndex = 0;

        float hourAvg = 0;
        for (uint8_t i = 0; i < HOUR_STATS; i++) {
            hourAvg += hourStats[i];
        }
        hourAvg /= HOUR_STATS;

        dayStats[hourIndex++] = hourAvg;
        if (hourIndex >= DAY_STATS) {
            hourIndex = 0;

            float dayAvg = 0;
            for (uint8_t i = 0; i < DAY_STATS; i++) {
                dayAvg += dayStats[i];
            }
            dayAvg /= DAY_STATS;

            monthStats[dayIndex++] = dayAvg;
            if (dayIndex >= MONTH_STATS) {
                dayIndex = 0;

                float monthAvg = 0;
                for (uint8_t i = 0; i < MONTH_STATS; i++) {
                    monthAvg += monthStats[i];
                }
                monthAvg /= MONTH_STATS;

                yearStats[monthIndex++] = monthAvg;
                if (monthIndex >= YEAR_STATS) {
                    monthIndex = 0;
                }
            }
        }
    }
}