#include <iostream>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    *reg=( ( ( (*reg>>0) & 1) ^ ((*reg>>2) & 1) ^ ((*reg>>3) & 1) ^ ((*reg>>5)&1)) <<15) | (*reg>>1);
}

