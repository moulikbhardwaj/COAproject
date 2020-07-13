#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKENLENGTH 20

/*          ---------------Global Variables--------------                   */
FILE *file;
FILE *out;
FILE *symbolFile;
int error;
int ret;
char errorBuffer[256];
char lineBuffer[256];
int symbolTableLength;
int lineNo;
int eof;
char registerSymbols[7][3];
__uint8_t p0, p1;
char inputFileName[256];
char outputFileName[256];
char symbolTableFileName[256];
// struct opcode opCodes[16];

/*          ---------------Structures--------------                   */

struct s_opcode{
    __uint8_t opcode;
    char function[MAXTOKENLENGTH+1];
    int paramNum;
} opCodes[16];

enum operandType{Null, NotNull};
struct s_OpCodeList{
    char mnemonic[MAXTOKENLENGTH+1];
    int paramLength;
    enum operandType op1;
    enum operandType op2;
} mneopcodes[16];


struct s_SymbolTable{
    char literal[MAXTOKENLENGTH+1];
    int LC;
}symbolTable[256];



/*          ---------------Function Declarations--------------                   */

// initialises values to suitable starting values;
void init();

// Writes error stored in errorBuffer into stdin
void writeError();

// returns line from the FILE
char *getLine();

// Returns length upto next white space or ';', or ',', whichever comes first
int wordLength(char * line);

// puts token in token variable, starting from current pointer of line.
void getToken(char* line, char* token);

// Final cleanup of program, and show results if flags are set.
void cleanup();

// Returns a pointer pointing to first non white space character in string.
char* skipWhiteSpace(char * line);

// Returns whether given line is a comment or not.
int isComment(char *line);

// Returns whether given token is an opcode or not.
int isOpcode(char * token);

// Returns 0 if token is not a label, 1 if a new label, 2 if label is already seen but not declared, 3 if label is already seen and declared.
int isLabel(char* token);

// Returns whether token is a directive or not.
int isDirective(char *token);

// Returns whether given token is a register or not
int isRegister(char *token);

// Retruns whether token is a number or not.
int isNumber(char *token);

// Adds the label to symbol table.
void addLabelToSymbolTable(char *label, int LC);

// The main reading cycle for Pass 1
void pass1();

void pass2();

int getAddr(char* label);

int getOpcodeIdx(char* opcode);