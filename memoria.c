#include "memoria.h"
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

void load_mem(char* texto, char* dado){
        FILE *code;
    code = fopen(texto, "rb");
    if (code == NULL){
        printf("Arquivo não encontrado \n");
        return;
    }
    int text = 0x0;
    while (!feof(code)) {
        fread(mem+text, sizeof(int32_t), 1, code);
        text++;
    }
    fclose(code);

    FILE *data;
    data = fopen(dado, "rb");
    if (data == NULL) {
        printf("Arquivo não encontrado \n");
        return;
    }
    int dados = 0x2000;
    while (!feof(data)) {
        fread(mem+dados, sizeof(int32_t), 1, data);
        dados++;
    }
    fclose(data);



}

int32_t lb(uint32_t address, int32_t kte) {
    if ((address + kte) > MEM_SIZE*4) {
        printf("Erro");
        return 0;
    }
    
    int8_t *memoria8 = (int8_t*) mem;
    int32_t dado;
    dado = (int32_t) memoria8[(address+kte)/4];
    return dado;
}
int32_t lw(uint32_t address, int32_t kte){
    int32_t dado;
    if ((address+kte) > 4*MEM_SIZE){
        printf("Erro1");
        return 0;
    }

    dado = mem[(address+kte)/4];
    return dado;
}

int32_t lbu(uint32_t address, int32_t kte){
    int8_t dado;
    if ((address + kte) > MEM_SIZE*4) {
        printf("Erro2");
        return 0;
    }
    
    int8_t *memoria8 = (int8_t*) mem;
    dado = (uint32_t) memoria8[(address/4+kte)];
    return dado;
}

void sb(uint32_t address, int32_t kte, int8_t dado){
    if ((address + kte) > MEM_SIZE*4) {
        printf("Erro3");
    }
    
    int8_t *dado8 = (int8_t *)&dado;
    
    int8_t *memoria8 = (int8_t *)mem;
    int32_t pos;
    pos = address + kte;
    memoria8[pos] = *dado8;
}

void sw(uint32_t address, int32_t kte, int32_t dado){
    int32_t pos;
    if (address + kte > 4*MEM_SIZE || (address+kte)%4 != 0)
        printf("Erro4");
    pos = (address + kte)/4;
    mem[pos] = dado;
}