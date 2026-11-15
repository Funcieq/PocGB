#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <bus.h>
typedef struct {
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
} CPU;

typedef enum {
    FLAG_Z = 1 << 7,
    FLAG_N = 1 << 6,
    FLAG_H = 1 << 5,
    FLAG_C = 1 << 4
} CPUFlag;

//declarations from cpu.c
uint16_t cpu_get_pc(const CPU *cpu);
uint16_t cpu_get_sp(const CPU *cpu);
uint16_t cpu_get_bc(const CPU *cpu);
uint16_t cpu_get_de(const CPU *cpu);
uint16_t cpu_get_hl(const CPU *cpu);
uint16_t cpu_get_af(const CPU *cpu);
void cpu_step(CPU *cpu, Bus *bus);
void cpu_set_pc(CPU *cpu, uint16_t value);
void cpu_set_sp(CPU *cpu, uint16_t value);
void cpu_set_bc(CPU *cpu, uint16_t value);
void cpu_set_de(CPU *cpu, uint16_t value);
void cpu_set_hl(CPU *cpu, uint16_t value);
void cpu_set_af(CPU *cpu, uint16_t value);
void cpu_set_flag(CPU *cpu, CPUFlag flag);
void cpu_clear_flag(CPU *cpu, CPUFlag flag);
bool cpu_get_flag(const CPU *cpu, CPUFlag flag);
uint8_t cpu_fetch(CPU *cpu, const Bus *bus);
void cpu_execute(CPU *cpu, Bus *bus, uint8_t opcode);
void cpu_add_a(CPU *cpu, uint8_t value);

