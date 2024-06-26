#pragma once

#include <stdint.h>
#include <math.h>
#include "sample.h"

float get_rms_current(void){
    float meanSquare = sumOfSquares / (float)sampleCount;
    sumOfSquares = 0;
    sampleCount = 0;
    return sqrt(meanSquare);
}