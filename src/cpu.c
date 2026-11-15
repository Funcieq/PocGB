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

uint8_t cpu_read_r8(CPU *cpu, Bus *bus, uint8_t reg) {
    switch (reg) {
        case 0: return cpu->b;
        case 1: return cpu->c;
        case 2: return cpu->d;
        case 3: return cpu->e;
        case 4: return cpu->h;
        case 5: return cpu->l;
        case 6: return bus_read(bus, cpu_get_hl(cpu));
        case 7: return cpu->a;
        default: return 0;
    }
}

uint16_t cpu_fetch16(CPU *cpu, const Bus *bus) {
    uint16_t value = bus_read(bus, cpu->pc++);
    value |= bus_read(bus, cpu->pc++) << 8;
    return value;
}

void cpu_write_r8(CPU *cpu, Bus *bus, uint8_t reg, uint8_t value) {
    switch (reg) {
        case 0: cpu->b = value; break;
        case 1: cpu->c = value; break;
        case 2: cpu->d = value; break;
        case 3: cpu->e = value; break;
        case 4: cpu->h = value; break;
        case 5: cpu->l = value; break;
        case 6: bus_write(bus, cpu_get_hl(cpu), value); break;
        case 7: cpu->a = value; break;
    }
}

void cpu_execute(CPU *cpu, Bus *bus, uint8_t opcode) {
    // ADD A, r8
    if (opcode >= 0x80 && opcode <= 0x87) {
        uint8_t reg = opcode & 0x07;
        uint8_t value = cpu_read_r8(cpu, bus, reg);

        cpu_add_a(cpu, value);
        return;
    }
    // LD r8, r8
    if (opcode >= 0x40 && opcode <= 0x7F && opcode != 0x76) {
        uint8_t dst = (opcode >> 3) & 0x07;
        uint8_t src = opcode & 0x07;
        uint8_t value = cpu_read_r8(cpu, bus, src);
        cpu_write_r8(cpu, bus, dst, value);
        return;
    }

    // LD r8, d8
    if ((opcode & 0xC7) == 0x06){
        uint8_t dst = (opcode >> 3) & 0x07;
        uint8_t value = bus_read(bus, cpu->pc++);
        cpu_write_r8(cpu, bus, dst, value);
        return;
    }

    // LD r16, d16
    if ((opcode & 0xCF) == 0x01) {
        uint8_t dst = (opcode >> 4) & 0x03;
        uint16_t value = cpu_fetch16(cpu, bus);
        switch (dst) {
            case 0: cpu_set_bc(cpu, value); break;
            case 1: cpu_set_de(cpu, value); break;
            case 2: cpu_set_hl(cpu, value); break;
            case 3: cpu_set_sp(cpu, value); break;
        }
        return;
    }

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
    }
}


void cpu_step(CPU *cpu, Bus *bus) {
    uint8_t opcode = cpu_fetch(cpu, bus);
    cpu_execute(cpu, bus, opcode);
}

//arithmetic operations

void cpu_add_a(CPU *cpu, uint8_t value){
    uint16_t result = cpu->a + value;

    //C Flag
    if(result > 0xFF){ //0xFF looks more cool than 255 lmao
        cpu_set_flag(cpu, FLAG_C);
    } else {
        cpu_clear_flag(cpu, FLAG_C);
    }
    //Z Flag
    if((result & 0xFF) == 0){
        cpu_set_flag(cpu, FLAG_Z);
    } else {
        cpu_clear_flag(cpu, FLAG_Z);
    }

    //N Flag
    cpu_clear_flag(cpu, FLAG_N);

    //H Flag
    if(((cpu->a & 0xF) + (value & 0xF)) > 0xF){
        cpu_set_flag(cpu, FLAG_H);
    } else {
        cpu_clear_flag(cpu, FLAG_H);
    }
    cpu->a = (uint8_t)result;
}
