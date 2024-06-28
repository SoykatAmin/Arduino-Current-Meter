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

void clear_local_statistics() {
    memset(hourStats, 0, sizeof(hourStats));
    memset(dayStats, 0, sizeof(dayStats));
    memset(monthStats, 0, sizeof(monthStats));
    memset(yearStats, 0, sizeof(yearStats));
    minuteIndex = 0;
    hourIndex = 0;
    dayIndex = 0;
    monthIndex = 0;
}

void query_statistics(int fd) {
    sendCommand(fd, "q");
}

void store_statistics(char *data){
    uint16_t value = (uint16_t)atoi(data);
    if (value != 0) {
        printf("Storing value: %d\n", value);
    }
    
    if(minuteIndex<HOUR_STATS)
        hourStats[minuteIndex++] = value;
    else{
        if(hourIndex<DAY_STATS)
            dayStats[hourIndex++] = value;
        else{
            if(dayIndex<MONTH_STATS)
                monthStats[dayIndex++] = value;
            else{
                if(monthIndex<YEAR_STATS)
                    yearStats[monthIndex++] = value;
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