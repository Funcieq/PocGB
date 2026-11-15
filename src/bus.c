#include <bus.h>

uint8_t bus_read(const Bus *bus, uint16_t address) {
    return bus->memory[address];
}

void bus_write(Bus *bus, uint16_t address, uint8_t value) {
    bus->memory[address] = value;
}