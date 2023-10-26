#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 4096

int32_t mem[MEM_SIZE];

void clear_mem();

int load_mem(const char *fn, int start);

int32_t lb(int32_t address, int32_t kte);

int32_t lw(int32_t address, int32_t kte);

int32_t lbu(int32_t address, int32_t kte);

void sb(uint32_t address, int32_t kte, int8_t dado);

void sw(int32_t address, int32_t kte, int32_t dado);