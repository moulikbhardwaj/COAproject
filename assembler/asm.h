#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKENLENGTH 20

/*          ---------------Forward References--------------                   */
struct opcode;
struct SymbolTable;


/*          ---------------Global Variables--------------                   */
FILE *file;
FILE *out;
int error;
int ret;
char errorBuffer[256];
struct SymbolTable{
    char literal[MAXTOKENLENGTH+1];
    int LC;
};
char lineBuffer[256];
struct SymbolTable symbolTable[256];
int symbolTableLength;
int lineNo;
char registerSymbols[7][3];

/*          ---------------Structures--------------                   */
struct opcode{
    char opcode[MAXTOKENLENGTH+1];
    char function[MAXTOKENLENGTH+1];
    char rmode0[MAXTOKENLENGTH+1];
    char rmode1[MAXTOKENLENGTH+1];
};

enum operandType{Null, NotNull};
struct opCodeList{
    char mnemonic[MAXTOKENLENGTH+1];
    int paramLength;
    enum operandType op1;
    enum operandType op2;
};



/*          ---------------Function Declarations--------------                   */

// General:

// initialises values to suitable starting values;
void init();

// Writes error stored in errorBuffer into stdin
void writeError();

// For pass-1

// Returns a pointer pointing to first non white space character in string.
char* skipWhiteSpace(char *);

// Returns whether given line is a comment or not.
int isComment(char *);

// Returns whether given token is an opcode or not.
int isOpcode(char *);

// Returns 0 if token is not a label, 1 if a new label, 2 if label is already seen but not declared, 3 if label is already seen and declared.
int isLabel(char* );

// Returns whether token is a directive or not.
int hasDirective(char *);

// Returns whether given token is a register or not
int isRegister(char *);

// Retruns whether token is a number or not.
int isNumber(char *);

// Returns length upto next white space or ';', or ',', whichever comes first
int wordLength(char *);

// puts token in token variable, starting from current pointer of line.
void getToken(char*, char*);

// returns line from the FILE
char* getLine();

// Adds the label to symbol table.
void addLabelToSymbolTable(char *, int);

// The main reading cycle for Pass 1
void pass1();


// For Pass-2

// void pass2();