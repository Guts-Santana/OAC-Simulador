#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void clear_mem()
{
	for (int i = 0; i < MEM_SIZE; ++i)
	{
		mem[i]=0;
	}
}

int load_mem(const char *fn, int start) {
    FILE *fptr;
    int *m_ptr = mem + (start >> 2);
    int size = 0;

    fptr = fopen(fn, "rb");
    if (!fptr) {
        printf("Arquivo nao encontrado!");
        return -1;
    } else {
        while (!feof(fptr)) {
            fread(m_ptr, 4, 1, fptr);
            m_ptr++;
            size++;
        }
        fclose(fptr);
    }
    return size;
}

int32_t lb(int32_t address, int32_t kte) {
    if ((address + kte) > 4*MEM_SIZE) {
        printf("%x address", address);
        return 0;
    }
    int32_t pos = address + kte;
    int8_t *memoria8 = (int8_t *) mem;
    int32_t dado;
    dado = (int32_t) memoria8[pos];
    return dado;
}
int32_t lw(int32_t address, int32_t kte){
    int32_t dado;
    if ((address+kte) > 4*MEM_SIZE){
        printf("Erro1");
        return 0;
    }

    dado = mem[(address/4+kte)];
    return dado;
}

int32_t lbu(int32_t address, int32_t kte){
    uint32_t dado;
    if ((address + kte) > MEM_SIZE*4) {
        printf("Erro2");
        return 0;
    }
    int32_t pos = address + kte;
    uint8_t *memoria8 = (uint8_t *) mem;
    dado = (uint32_t) memoria8[pos];
    return dado;
    

    return dado;
}

void sb(uint32_t address, int32_t kte, int8_t dado)
{
	int8_t* memoria8 = (int8_t*) mem;
	//pointer += address+kte;

	if ((address + kte) > 4*MEM_SIZE ){
		printf("Erro sb:%d\t%d\n",address, kte);
		return;
	}
	memoria8[address+kte] = dado;
}

void sw(int32_t address, int32_t kte, int32_t dado){
    int32_t pos;
    if (address + kte > 4*MEM_SIZE || (address+kte)%4 != 0)
        printf("Erro4");
    pos = (address + kte)/4;
    mem[pos] = dado;
}