#include "Memory.h"
#include "Instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void init() {
    clear_mem();
    clear_reg();
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