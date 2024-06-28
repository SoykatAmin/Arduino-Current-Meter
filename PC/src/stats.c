#include "../include/stats.h"

// Definizione dello storage per le statistiche
uint16_t hourStats[HOUR_STATS];
uint16_t dayStats[DAY_STATS];
uint16_t monthStats[MONTH_STATS];
uint16_t yearStats[YEAR_STATS];

// Definizione degli indici per le statistiche
uint8_t minuteIndex = 0;
uint8_t hourIndex = 0;
uint8_t dayIndex = 0;
uint8_t monthIndex = 0;

void clear_statistics(int fd) {
    sendCommand(fd, "c");
}

void query_statistics(int fd) {
    sendCommand(fd, "q");
}

void store_statistics(char *data){
    uint16_t value = (uint16_t)atoi(data);
    if (value != 0) {
        printf("Storing data: %s\n", data);
        printf("Storing value: %d\n", value);
    }
    
    hourStats[minuteIndex++] = value;
    if (minuteIndex >= HOUR_STATS) {
        minuteIndex = 0;

        uint16_t hourAvg = 0;
        for (uint8_t i = 0; i < HOUR_STATS; i++) {
            hourAvg += hourStats[i];
        }
        hourAvg /= HOUR_STATS;

        dayStats[hourIndex++] = hourAvg;
        if (hourIndex >= DAY_STATS) {
            hourIndex = 0;

            uint16_t dayAvg = 0;
            for (uint8_t i = 0; i < DAY_STATS; i++) {
                dayAvg += dayStats[i];
            }
            dayAvg /= DAY_STATS;

            monthStats[dayIndex++] = dayAvg;
            if (dayIndex >= MONTH_STATS) {
                dayIndex = 0;

                uint16_t monthAvg = 0;
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

void print_statistics(){

    printf("Minute Statistics:\n");
    for (uint8_t i = 0; i < HOUR_STATS; i++) {
        printf("%d ", hourStats[i]);
    }
    printf("\n");

    printf("Hour Statistics:\n");
    for (uint8_t i = 0; i < DAY_STATS; i++) {
        printf("%d ", dayStats[i]);
    }
    printf("\n");

    printf("Day Statistics:\n");
    for (uint8_t i = 0; i < MONTH_STATS; i++) {
        printf("%d ", monthStats[i]);
    }
    printf("\n");

    printf("Month Statistics:\n");
    for (uint8_t i = 0; i < YEAR_STATS; i++) {
        printf("%d ", yearStats[i]);
    }
    printf("\n");
}