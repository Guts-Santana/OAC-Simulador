#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Memory.h"

enum REGISTERS {
    ZERO=0, RA=1,	SP=2,	GP=3,
    TP=4,	T0=5,	T1=6,	T2=7,
    S0=8,	S1=9,	A0=10,	A1=11,
    A2=12,	A3=13,	A4=14,	A5=15,
    A6=16,	A7=17,  S2=18,	S3=19,
    S4=20,	S5=21, 	S6=22,	S7=23,
    S8=24,	S9=25,  S10=26,	S11=27,
    T3=28,	T4=29,	T5=30,	T6=31
};

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

enum opcodes{
    ILoad = 0x03, //LB, LW, LBU
    ILA   = 0x13, //ADDI, ANDI, SLLI, SRAI, SRLI, ORI
    Rtype = 0x33, //ADD, SLT, SLTU, XOR, AND, OR, SUB
    Btype = 0x63, //BEQ, BNE, BGE, BGEU, BLT, BLTU
    Stype = 0x23, //SB, SW
    AUIPC = 0x17,
    ECALL = 0x73,
    JAL   = 0x6F,
    JALR  = 0x67,
    LUI   = 0x37

};

enum funct3{
    BEQ = 0x00, BNE = 0x01, BGE = 0x05,  //Btype
    BGEU = 0x07, BLT = 0x04, BLTU = 0x06,//Btype
    LB = 0x00, LW = 0x02, LBU = 0x4, //ILOAD
    ADDI = 0x00, ANDI = 0x07, SLLI = 0x01, //ILA
    SRAI_SRLI = 0x05, ORI = 0x06,  //ILA
    ADD_SUB = 0x00, SLTU = 0x03, //Rtype
    XOR = 0x04, AND = 0x07, OR = 0x06, SLT = 0x02, //Rtype
    SB = 0x00, SW = 0x02 //Stype

};

enum funct7{
    SUB7 = 0x20,
    SRAI7 = 0x20
};

int32_t funct_Im();

void step();

void step();

void fetch();

void decode();

void execute();