#pragma once
#include <stdint.h>

typedef struct {
    uint8_t memory[0x10000]; // 64KB of memory 0x10000 looks smoother tho
} Bus;

//declarations from bus.c
uint8_t bus_read(const Bus *bus, uint16_t address);
void bus_write(Bus *bus, uint16_t address, uint8_t value);
