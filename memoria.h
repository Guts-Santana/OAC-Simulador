#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 4096

int32_t mem[MEM_SIZE];

void clear_mem();

void load_mem(char* dado, char* texto);

int32_t lb(uint32_t address, int32_t kte);

int32_t lw(uint32_t address, int32_t kte);

int32_t lbu(uint32_t address, int32_t kte);

void sb(uint32_t address, int32_t kte, int8_t dado);

void sw(uint32_t address, int32_t kte, int32_t dado);