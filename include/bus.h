#pragma once
#include <stdint.h>

typedef struct {
    uint8_t memory[0x10000]; // 64KB of memory 0x10000 looks smoother tho
} Bus;