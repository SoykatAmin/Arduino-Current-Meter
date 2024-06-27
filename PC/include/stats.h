#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define HOUR_STATS  60
#define DAY_STATS   24
#define MONTH_STATS 30
#define YEAR_STATS  12

// Storage for statistics
extern float hourStats[];
extern float dayStats[];
extern float monthStats[];
extern float yearStats[];

// Indexes for statistics
extern uint8_t minuteIndex;
extern uint8_t hourIndex;
extern uint8_t dayIndex;
extern uint8_t monthIndex;

// Function declarations
void clear_statistics(void);
void query_statistics(void);
void store_statistics(char *data);