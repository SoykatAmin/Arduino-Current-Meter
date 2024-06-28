#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define HOUR_STATS  60
#define DAY_STATS   24
#define MONTH_STATS 30
#define YEAR_STATS  12

// Storage for statistics
extern uint16_t hourStats[];
extern uint16_t dayStats[];
extern uint16_t monthStats[];
extern uint16_t yearStats[];

// Indexes for statistics
extern uint8_t minuteIndex;
extern uint8_t hourIndex;
extern uint8_t dayIndex;
extern uint8_t monthIndex;

// Function declarations
void query_statistics(int fd);
void clear_statistics(int fd);
void store_statistics(char *data);
void print_statistics();