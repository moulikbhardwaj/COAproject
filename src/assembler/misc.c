#include "asm.h"

void writeError(){
    printf("At line %d,\033[0;31m %s\033[0m\n", lineNo, errorBuffer);
}

void addOpcode(int idx, char *function, __uint8_t opcode, int paramNum){
    snprintf(opCodes[idx].function, MAXTOKENLENGTH, "%s", function);
    opCodes[idx].opcode = opcode;
    opCodes[idx].paramNum=paramNum;
    snprintf(mneopcodes[idx].mnemonic,MAXTOKENLENGTH,"%s",function);
    mneopcodes[idx].paramLength=paramNum;

    if(paramNum==0){
        mneopcodes[idx].op1=Null;
        mneopcodes[idx].op2=Null;
    }
    if(paramNum==1){
        mneopcodes[idx].op1=NotNull;
        mneopcodes[idx].op2=Null;
    }
    if(paramNum==2){
        mneopcodes[idx].op1=NotNull;
        mneopcodes[idx].op2=NotNull;
    }
}

char* getLine(){
    memset((void*)(lineBuffer),0,256);
    if(fgets(lineBuffer,256,file)==NULL){
        eof=1;
    }
    return lineBuffer;
}

void init(){
    error = 0;
    symbolTableLength = 0;
    file = fopen(inputFileName, "r+");
    out = fopen(outputFileName, "w+");
    symbolFile = fopen(symbolTableFileName, "w+");
    strcpy(registerSymbols[0],"A");
    strcpy(registerSymbols[1],"B");
    strcpy(registerSymbols[2],"C");
    strcpy(registerSymbols[3],"D");
    strcpy(registerSymbols[4],"SP");
    strcpy(registerSymbols[5],"MA");
    strcpy(registerSymbols[6],"MB");

    addOpcode(0,"MOV" , 0b0000,2);
    addOpcode(1,"ADD" , 0b0001,2);
    addOpcode(2,"SUB" , 0b0010,2);
    addOpcode(3,"CMP" , 0b0011,2);
    addOpcode(4,"RSH" , 0b0100,2);
    addOpcode(5,"CMPL", 0b0101,1);
    addOpcode(6,"PUSH", 0b0110,1);
    addOpcode(7,"POP" , 0b0111,0);
    addOpcode(8,"MCP" , 0b1000,2);
    addOpcode(9,"CALL", 0b1001,1);
    addOpcode(10,"RET", 0b1010,0);
    addOpcode(11,"JG" , 0b1011,1);
    addOpcode(12,"JGE", 0b1100,1);
    addOpcode(13,"JL" , 0b1101,1);
    addOpcode(14,"JLE", 0b1110,1);
    addOpcode(15,"JMP", 0b1111,1);
}

int wordLength(char *line){
    int nn = strlen(line);
    for(int i = 0; i < nn; i++){
        if(isspace(line[i]) || line[i]==',' || line[i]==';'){return i+1;}
    }
    return nn;
}

void getToken(char *line, char* token){
    int nn = wordLength(line);
    // strncpy(token,line,nn);
    snprintf(token,nn,"%s",line);
    token[nn-1]='\0';
    if(strlen(token)>MAXTOKENLENGTH){
        error++;
        snprintf(errorBuffer, 256, "%s", "SyntaxError: Token Length Excedded");
        writeError();
    }
}

void cleanup(){
    #ifdef _SHOW_SYMBOL_TABLE
        printf("\t\033[0;32mSymbol Table: \033[0m\n");
        printf("\033[0;34m%-20s %s", "Label", "LocationCounter\033[0m\n");
        for(int i = 0; i < symbolTableLength; i++){
            printf("%-21s%d\n", symbolTable[i].literal, symbolTable[i].LC);
        }
    #endif
    fclose(file);
    fclose(out);
    fclose(symbolFile);
    if(error!=0){
        system(outputFileName);
        system(symbolTableFileName);
    }
}

int isComment(char *line){
    if(*line==';'){return 1;}
    return 0;
}

int isDirective(char *line){
    return !strcmp(line,".data");
}

int isOpcode(char* token){
    for(int i = 0; i < 16; i++){
        if(!strcmp(token,mneopcodes[i].mnemonic)){
            return 1;
        }
    }
    return 0;
}


int isRegister(char* token){
    for(int i = 0; i < 7; i++){
        if(!strcmp(registerSymbols[i],token)){return 1;}
    }
    return 0;
}

int isLabel(char* token){
    if(*token=='$'){return 0;}
    if(isOpcode(token)){return 0;}
    if(isRegister(token)){return 0;}
    for(int i = 0; i < symbolTableLength; i++){
        if(!strcmp(token,symbolTable[i].literal)){
            if(symbolTable[i].LC==-1){
                return 2;
            }
            return 3;
        }
    }
    return 1;
}

int isNumber(char* token){
    char *nptr;
    ret = strtol(token,&nptr,10);
    return !(token+strlen(token)==nptr);
}

int getOpcodeIdx(char *opcode){
    for(int i = 0; i < 16; i++){
        if(!strcmp(opCodes[i].function,opcode)){return i;}
    }
    return 0;
}

int getAddr(char* label){
    for(int i = 0; i < symbolTableLength; i++){
        if(!strcmp(label, symbolTable[i].literal)){
            return symbolTable[i].LC;
        }
    }
    return -1;
}