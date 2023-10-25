#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


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

int32_t reg[32];

uint32_t pc;
uint32_t ri;
uint32_t sp;
uint32_t gp;

uint32_t funct7;
uint32_t rs2;
uint32_t rs1;
uint32_t funct3;
uint32_t rd;
uint32_t opcode;
int32_t imm;
uint8_t shamt;

enum opcodes{
    ILoad = 0x03,
    ILA = 0x13,
    Rtype = 0x33,
    Btype = 0x63,
    Stype = 0x23,
    AUIPC = 0x17,
    ECALL = 0x73,
    JAL = 0x6F,
    JALR = 0x67,
    LUI = 0x37

};

enum funct3{
    BEQ = 0x00, BNE = 0x01, BGE = 0x05,
    BGEU = 0x07, BLT = 0x04, BLTU = 0x06,
    LB = 0x00, LW = 0x02, LBU = 0x4,
    ADDI = 0x00, ANDI = 0x07, SLLI = 0x01,
    SRAI_SRLI = 0x05, ORI = 0x06,
    ADD_SUB = 0x00, SLTU = 0x03,
    XOR = 0x04, AND = 0x07, OR = 0x06, SLT = 0x02,
    SB = 0x00, SW = 0x02

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

void clear_mem();

void load_mem(char* dado, char* texto);

int32_t lb(uint32_t address, int32_t kte);

int32_t lw(uint32_t address, int32_t kte);

int32_t lbu(uint32_t address, int32_t kte);

void sb(uint32_t address, int32_t kte, int8_t dado);

void sw(uint32_t address, int32_t kte, int32_t dado);