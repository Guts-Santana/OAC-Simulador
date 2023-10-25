#include "codigo.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int32_t funct_Im() {
    int32_t im;
    int32_t tmp;
    switch (opcode)
    {
    case (ILoad || ILA):
        im = ri>>20;
        break;
    case Stype:
        im = (ri >>7) & 0x1F;
        tmp = (ri & 0xFE000000)>>18;
        im = im | tmp;
        break;
    case Btype:
        im = (ri>>8)& 0x1E;
        tmp = (ri>>17)& 0xFE0;
        im = im | tmp;
        tmp = (ri>>7)&0x1;
        im = im | tmp;
        tmp = (ri >> 19)&0x200;
        im = im | tmp;
        break;
    case AUIPC:
        im = ri & 0xFFFFF000;
        break;
    case LUI:
        im = ri & 0xFFFFF000;
        break;
    default:
        return 0;
    }

    return (int32_t)im;
}
void fetch(){
    ri = lw(pc,0);
    pc += 4;
}

void decode(){
    opcode = (ri & 0x7F);
    rd = (ri >> 7) & 0x1F;
    rs2 = ((ri >> 20) & 0x1F);
    rs1 = ((ri >> 15) & 0x1F);
    shamt = ((ri >> 20) & 0x1F);
    imm = funct_Im();
}

void execute(){

    reg[0] = 0;
    switch (opcode) {
    case ILoad:
            switch (funct3)
            {
            case LB:
                reg[rd] = lb(rs1, imm);
                break;
            case LW:
                reg[rd] = lw(rs1, imm);
                break;
            case LBU:
                reg[rd] = lbu(rs1, imm);
                break;
            }
        break;
    case ILA:
        switch (funct3)
        { //ADDI, ANDI, SLLI, SRAI, SRLI, ORI
        case ADDI:
            reg[rd] = reg[rs1] + imm;
            break;
        case ANDI:
            reg[rd] = reg[rs1] & shamt;
            break;

        case SLLI:
            reg[rd] = reg[rs1] << shamt;
            break;

        case SRAI_SRLI:
            switch (funct7)
            {
            case SRAI7:
                reg[rd] = (int32_t)reg[rs1] >> shamt;
                reg[rd] = (uint32_t)reg[rd];
                break;

            case !SRAI7:
                reg[rd] = reg[rs1] >> shamt;
                break;
            }
            break;

        case ORI:
            reg[rd] = reg[rs1] | imm;
            break;
        }
        break;

    case Rtype:
        switch (funct3)//ADD, SLT, SLTU, XOR, AND, OR, SUB
        {
        case ADD_SUB:
            switch (funct7)
            {
            case SUB7:
                reg[rd] = reg[rs1] - reg[rs2];
                break;

            case !SUB7:
                reg[rd] = reg[rs1] + reg[rs2];
                break;
            }
            break;

        case SLT:
            if (reg[rs1] < reg[rs2])
                reg[rd] = 1;
            else reg[rd] = 0;

            break;

        case SLTU:
            if (reg[rs1] < reg[rs2])
                reg[rd] = 1;
            else reg[rd] = 0;
            break;

        case XOR:
            reg[rd] = reg[rs1] ^ reg[rs2];
            break;

        case AND:
            reg[rd] = reg[rs1] & reg[rs2];
            break;

        case OR:
            reg[rd] = reg[rs1] | reg[rs2];
            break;
        }
        break;

    case Stype:
        switch (funct3)
        {
        case SB:
            sb(reg[rs2], imm, reg[rs1]);
            break;

        case SW:
            sw(reg[rs2], imm, reg[rs1]);
            break;
        }
        break;
    case Btype:
        switch (funct3)
        { //BEQ, BNE, BGE, BGEU, BLT, BLTU
        case BEQ:
            if (reg[rs1] == reg[rs2])
                pc = pc + imm;

            break;
        case BNE:
            if (reg[rs1] != reg[rs2])
                pc = pc + imm;
            break;

        case BGE:
            if (reg[rs1] > reg[rs2])
                pc = pc + imm;

            break;

        case BGEU:
            if ((uint32_t)reg[rs1] > (uint32_t)reg[rs2])
                pc = pc + imm;
            break;

        case BLT:
            if (reg[rs1] < reg[rs2])
                pc = pc + imm;
            break;

        case BLTU:
            if ((uint32_t)reg[rs1] < (uint32_t)reg[rs2])
                pc = pc + imm;
            break;
        }
        break;
    case AUIPC:
        reg[rd] = reg[rd] | imm;
        break;
    case ECALL:
        switch (reg[A7])
        {
        case 1:
            printf("%i\n", reg[A0]);
            break;

        case 4:
            char *string = (char*)(intptr_t)reg[A0];
            printf("%s,\n", string);
            break;
        case 10:
            printf("-- program is finished running (0) --\n");
        }
        break;
    case LUI:
        reg[rd] = imm;
        break;
    case JAL:
        reg[rd] = pc + 4;
        reg[pc] = pc + imm;
        break;
    case JALR:
        reg[RA] = pc + 4;
        reg[pc] = pc + imm;
        break;
    default:
        printf("Erro no opcode");
        break;
    }
}

void step(){
    fetch();
    decode();
    execute();
}

int main(){
    load_mem("code.bin", "data.bin");
    while (pc < 4096)
    {
        step();
    }
    return 0;
}
