#include <cpu.h>
#include <stdbool.h>

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