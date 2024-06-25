#pragma once
#include <stdint.h>

// Buffer sizes for statistics
const uint8_t hour_stats = 60;
const uint8_t day_stats = 24;
const uint8_t month_stats = 30;
const uint8_t year_stats = 12;

// Storage for statistics
float hourStats[hour_stats];
float dayStats[day_stats];
float monthStats[month_stats];
float yearStats[year_stats];

// Indexes for statistics
uint8_t minuteIndex = 0;
uint8_t hourIndex = 0;
uint8_t dayIndex = 0;
uint8_t monthIndex = 0;

void clear_statistics(void);

void query_statistics(void);