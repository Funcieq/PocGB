#include <cpu.h>

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