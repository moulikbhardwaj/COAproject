#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MEMORY_SIZE 1024

// Memroy and registers
int memory[MEMORY_SIZE];
int *registerA;
int *registerB;
int *registerC;
int *registerD;
int *registerMA;
int *registerMB;
int *SP;

int nm;

FILE *binFile;
FILE *OPfile;
FILE *Symbol;

struct symbolTable{
    char symbol[21];
    int addr;
} table[256];
int symbolTableLength;

// opcode related
__uint8_t *opcode;
int requiredOperands;
int operandMux;
char function[5];

// param related
enum param{p_Null, p_Register, p_Immidiate, p_Dereference, p_Memory};
enum param p0;
enum param p1;
__uint8_t *param0;
__uint8_t *param1;

int LC;

// Function Declarations

int *accessMemroy(int location);

void readbits(__uint8_t *);

void decodeOpcode();

void incrementLC();

void myStrcpy(char* dest, char* src);

void executeOpcode();


int* resolveRegister(__uint8_t);

void MOV();

void ADD();

void SUB();

void CMP();

void RSH();

void CMPL();

void PUSH();

void PUSH();

void POP();

void CALL();

void RET();

void MCP();

void JG();

void JGE();

void JL();

void JLE();

void JMP();

void writeDT();