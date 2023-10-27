#include "Instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Banco de Registradores
int32_t reg[32];

//Dados importantes
int32_t pc;
int32_t ri; //Word lida da memoria

//Dados da WORD
int32_t opcode;
int32_t rd; //Registrador destino
int32_t funct3; //Funct3
int32_t rs1; //Registrador usado
int32_t rs2; //Registrador usado
int32_t funct7; //Funct7


int32_t imm; //Imediato
int32_t shamt; //Shamt
int fim = 0; //Para encerrar o programa;

void clear_reg(){
    for (int i = 0; i < 32; i++)
    {
        reg[i] = 0;
    }
    
}
int32_t funct_Im() {
    int32_t im;
    int32_t tmp;
    switch (opcode)
    {
    case ILoad:
        im = ri>>20; //12:0
        break;
    case ILA:
        im = ri>>20; //12:0
        break;
    case Stype:
        im = (ri >>7) & 0x1F;
        tmp = (ri & 0xFE000000)>>18;
        im = im | tmp;
        break;
    case Btype:
        im = (ri>>7)& 0x1E; //4:0
        tmp = (ri>>20)& 0x7E0; //10:5
        im = im | tmp; //10:0
        tmp = ((ri>>7)&0x1)<<11; //1
        im = im | tmp; //11:0
        tmp = ((ri >> 31)&0x1)<<12; //12
        im = im | tmp; //12:0
        if (im >> 12){ // Para Im negativo;
        im = im + 0xFFFFE000;
        }
        break;
    case AUIPC:
        im = (ri & 0xFFFFF000); //31:12
        break;
    case LUI:
        im = (ri & 0xFFFFF000); //31:12
        break;
    
    case JALR:
        im = ri>>20 & 0xFFF; //12:0
        break;

    case JAL:
        im = ri >> 20 & 0x7FE; //10:0
        tmp = ri >> 9 & 0x800;
        im = im + tmp; //11:0
        tmp = ri & 0x000FF000;
        im = im + tmp;
        tmp = (ri >> 31 & 0x1)<<20;
        im = im+tmp;
        if (im>>20){
            im = im + 0xFFE00000;
        }
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
    funct3 = ri >> 12 & 0x7;
    funct7 = ri >> 25 & 0xEF;

    // printf("%x, %x, %x, %x, %x, %x, \n",opcode, rd, rs1, rs2, shamt, imm);
    // printf("%i\n", pc/4);
}

void execute(){

    reg[0] = 0;
    switch (opcode) {
    case ILoad: //LB, LW, LBU
            switch (funct3)
            {
            case LB:
                reg[rd] = lb(reg[rs1], imm);
                break;
            case LW:
                reg[rd] = lw(reg[rs1], imm);
                break;
            case LBU:
                reg[rd] = (int32_t)lbu(reg[rs1], imm);
                break;
            }
        break;
    case ILA: //ADDI, ANDI, SLLI, SRAI, SRLI, ORI
        switch (funct3)
        { 
        case ADDI:
            reg[rd] = reg[rs1] + imm;
            break;
        case ANDI:
            reg[rd] = reg[rs1] & imm;
            break;

        case SLLI:
            reg[rd] = reg[rs1] << shamt;
            break;

        case SRAI_SRLI:
            switch (funct7)
            {
            case SRAI7:
                reg[rd] = (int32_t)reg[rs1] >> shamt;
                break;

            case !SRAI7:
                reg[rd] = (int32_t)((uint32_t)reg[rs1] >> shamt);
                break;
            }
            break;

        case ORI:
            reg[rd] = reg[rs1] | imm;
            break;
        }
        break;

    case Rtype: //ADD, SLT, SLTU, XOR, AND, OR, SUB
        switch (funct3)
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
            //printf("%i, rd, %i rs1 %i rs2\n", rd,rs1,rs2);
            reg[rd] = reg[rs2] & reg[rs1];
            //printf("%x reg[rd]\n", reg[rd]);
            break;

        case OR:
            reg[rd] = reg[rs1] | reg[rs2];
            break;
        }
        break;

    case Stype: //SB, SW
        switch (funct3)
        {
        case SB:
            //printf("%x\n",reg[rs1]);
            sb(reg[rs1], imm, (reg[rs2] & 0xFF));
            break;

        case SW:
            sw(reg[rs1], imm, reg[rs2]);
            break;
        }
        break;
    case Btype: //BEQ, BNE, BGE, BGEU, BLT, BLTU
        switch (funct3)
        { 
        case BEQ:
            if (reg[rs1] == reg[rs2])
                pc = pc + imm - 4;

            break;
        case BNE:
            if (reg[rs1] != reg[rs2])
                pc = pc + imm - 4;
            break;

        case BGE:
            if (reg[rs1] > reg[rs2])
                pc = pc + imm - 4;

            break;

        case BGEU:
            if ((uint32_t)reg[rs1] > (uint32_t)reg[rs2])
                pc = pc + imm - 4;
            break;

        case BLT:
            if (reg[rs1] < reg[rs2])
                pc = pc + imm - 4;
            break;

        case BLTU:
            if ((uint32_t)reg[rs1] < (uint32_t)reg[rs2])
                pc = pc + imm - 4;
            break;
        }
        break;

    case AUIPC:
        reg[rd] = pc - 4 + imm;
        break;

    case ECALL:
        switch (reg[A7])
        {
        case 1:
            printf("%i", reg[A0]);
            break;

        case 4:
            int32_t reg_aux = reg[A0];
            //printf("%x, character\n", *(mem+reg[A0]/4));
            int32_t character = lb(reg_aux,0);     
            while (character != 00)
            {
                character = lb(reg_aux,0);     
                printf("%c", character);
                reg_aux+=1;
            }
            break;
        case 10:
            printf("-- program is finished running (0) --\n");
            fim = 1;
        }
        break;

    case LUI:
        reg[rd] = imm;
        break;

    case JAL:
        reg[rd] = pc;
        pc = pc + imm - 4;
        //printf("%x imm", imm);
        //printf("%x pc jal\n",pc);

        break;
    case JALR:
        pc = reg[rs1];
        reg[rd] = reg[rs1] + imm - 4;
        break;
    }
}

void step(){
    fetch();
    decode();
    execute();
}
