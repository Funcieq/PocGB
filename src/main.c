#include <stdio.h>
#include <cpu.h>
#include <bus.h>

int main(void) {
    CPU cpu = {0};
    Bus bus = {0};

    uint8_t program[] = {
        0x3E, 0x42,
        0x06, 0x12,
        0x00
    };

    for (size_t i = 0; i < sizeof(program); i++) {
    bus_write(&bus, i, program[i]);
}

for (int i = 0; i < 3; i++) {
    cpu_step(&cpu, &bus);
}
    
    //just testing something
    printf("A:  0x%02X\n", cpu.a);
    printf("B:  0x%02X\n", cpu.b);
    printf("PC: 0x%04X\n", cpu.pc);

    return 0;
}
