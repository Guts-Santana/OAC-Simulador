#include "codigo.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

    extern uint32_t pc;
    extern uint32_t ri;
    extern uint32_t sp;
    extern uint32_t gp;
void init() {
    pc = 0;
    ri = 0;
    sp = 0x3ffc;
    gp = 0x1800;
    clear_mem();
}

int main(){
    init();
    load_mem("code.bin", "data.bin");
    while (pc < MEM_SIZE){
    step();
    }

    return 0;
}