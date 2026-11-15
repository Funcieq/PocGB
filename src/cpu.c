#include <cpu.h>
#include <bus.h>
#include <stdbool.h>
#include <stdio.h>


//getters

uint16_t cpu_get_pc(const CPU *cpu) {
    return cpu->pc;
}

uint16_t cpu_get_sp(const CPU *cpu) {
    return cpu->sp;
}

uint16_t cpu_get_bc(const CPU *cpu) {
    return (cpu->b << 8) | cpu->c;
}

uint16_t cpu_get_de(const CPU *cpu) {
    return (cpu->d << 8) | cpu->e;
}

uint16_t cpu_get_hl(const CPU *cpu) {
    return (cpu->h << 8) | cpu->l;
}

uint16_t cpu_get_af(const CPU *cpu) {
    return (cpu->a << 8) | cpu->f;
}

//setters

void cpu_set_pc(CPU *cpu, uint16_t value) {
    cpu->pc = value;
}

void cpu_set_sp(CPU *cpu, uint16_t value) {
    cpu->sp = value;
}

void cpu_set_bc(CPU *cpu, uint16_t value) {
    cpu->b = (value >> 8) & 0xFF;
    cpu->c = value & 0xFF;
}

void cpu_set_de(CPU *cpu, uint16_t value) {
    cpu->d = (value >> 8) & 0xFF;
    cpu->e = value & 0xFF;
}

void cpu_set_hl(CPU *cpu, uint16_t value) {
    cpu->h = (value >> 8) & 0xFF;
    cpu->l = value & 0xFF;
}

void cpu_set_af(CPU *cpu, uint16_t value) {
    cpu->a = (value >> 8) & 0xFF;
    cpu->f = value & 0xF0;
}

//flags
void cpu_set_flag(CPU *cpu, CPUFlag flag) {
    cpu->f |= flag;
}

void cpu_clear_flag(CPU *cpu, CPUFlag flag) {
    cpu->f &= ~flag;
}

bool cpu_get_flag(const CPU *cpu, CPUFlag flag) {
    return (cpu->f & flag) != 0;
}

//fetch and execute

uint8_t cpu_fetch(CPU *cpu, const Bus *bus) {
    return bus_read(bus, cpu->pc++);
}

void cpu_execute(CPU *cpu, Bus *bus, uint8_t opcode) {
    switch (opcode) {
        case 0x00:
            //NOP
            break;
        case 0x3E:
            //LD A, d8
            cpu->a = bus_read(bus, cpu->pc++);
            break;

        case 0x06:
            // LD B, d8
            cpu->b = bus_read(bus, cpu->pc++);
            break;
        case 0x80:
            //ADD A, B
            cpu_add_a(cpu, cpu->b);
            break;
    }
}


void cpu_step(CPU *cpu, Bus *bus) {
    uint8_t opcode = cpu_fetch(cpu, bus);
    cpu_execute(cpu, bus, opcode);
}

//arithmetic operations

void cpu_add_a(CPU *cpu, uint8_t value){
    uint16_t result = cpu->a + value;

    if(result > 255){
        cpu_set_flag(cpu, FLAG_C);
    } else {
        cpu_clear_flag(cpu, FLAG_C);
    }

    cpu->a = (uint8_t)result;
}