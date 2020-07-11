#include "asm.h"

void writeError(){
    printf("At line %d,\033[0;31m %s\033[0m\n", lineNo, errorBuffer);
}


void init(){
    error = 0;
    symbolTableLength = 0;
    file = fopen("../code.bak", "r");
    strcpy(registerSymbols[0],"A");
    strcpy(registerSymbols[1],"B");
    strcpy(registerSymbols[2],"C");
    strcpy(registerSymbols[3],"D");
    strcpy(registerSymbols[4],"SP");
    strcpy(registerSymbols[5],"MA");
    strcpy(registerSymbols[6],"MB");
}