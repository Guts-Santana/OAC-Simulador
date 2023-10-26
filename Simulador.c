#include "Memory.h"
#include "Instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int32_t reg[32];

extern int32_t pc;
extern int32_t ri;
extern uint32_t sp;
extern uint32_t gp;

extern int32_t funct7;
extern int32_t rs2;
extern int32_t rs1;
extern int32_t funct3;
extern int32_t rd;
extern int32_t opcode;
extern int32_t imm;
extern int32_t shamt;
extern int fim;

void init() {
    clear_mem();
    pc = 0;
    ri = 0;
    reg[SP] = 0x3ffc;
    reg[GP] = 0x1800;
    
    load_mem("code.bin", 0);
    load_mem("data.bin", 0x2000);
}

int main(){
    init();
    while (pc < MEM_SIZE && fim == 0) {
    step();
    }

    return 0;
}