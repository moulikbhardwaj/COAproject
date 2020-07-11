#include "asm.h"

int eof=0;

struct opCodeList opcodes[] = {
    {"MOV",2,NotNull,NotNull}, {"ADD",2,NotNull,NotNull}, {"SUB",2,NotNull,NotNull}, {"CMP",2,NotNull,NotNull}, {"RSH",2,NotNull,NotNull}, {"CMPL",1,NotNull,Null}, {"PUSH",1,NotNull,Null}, {"POP",0,Null,Null},
    {"CALL",1,NotNull,Null}, {"RET",0,Null,Null}, {"JNE",1,NotNull,Null}, {"JG",1,NotNull,Null}, {"JGE",1,NotNull,Null}, {"JL",1,NotNull,Null}, {"JLE",1,NotNull,Null}, {"JMP",1,NotNull,Null}
};

char* skipWhiteSpace(char* line){
    while(isspace(*line)){
        line++;
    }
    return line;
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
        if(!strcmp(token,opcodes[i].mnemonic)){
            return 1;
        }
    }
    return 0;
}

int wordLength(char *line){
    int nn = strlen(line);
    for(int i = 0; i < nn; i++){
        if(isspace(line[i]) || line[i]==',' || line[i]==';'){return i+1;}
    }
    return nn;
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

void getToken(char *line, char* token){
    int nn = wordLength(line);
    strncpy(token,line,nn);
    token[nn-1]='\0';
    if(strlen(token)>MAXTOKENLENGTH){
        error++;
        snprintf(errorBuffer, 256, "%s", "SyntaxError: Token Length Excedded");
        writeError();
    }
}

char* getLine(){
    if(fgets(lineBuffer,256,file)==NULL){
        eof=1;
    }
    return lineBuffer;
}

void addLabelToSymbolTable(char* label, int LC){
    int match = -1;
    for(int i = 0; i < symbolTableLength; i++){
        if(!strcmp(label, symbolTable[i].literal)){
            match = i;
            break;
        }
    }
    if(match==-1){
        symbolTable[symbolTableLength].LC = LC;
        snprintf(symbolTable[symbolTableLength].literal, 256, "%s",label);
        symbolTableLength++;
    }
    else{
        symbolTable[match].LC = LC;
    }
}

int hasDirective(char* line){
    return 0;   
}

void debug(int lineNo){
    if(lineNo == 7){
        fprintf(stderr,"debug");
    }
}

int locationCount = 0;
void pass1(){
    char token[MAXTOKENLENGTH];
    for(int i = 0; i < 256; i++){
        symbolTable[i].LC=-1;
    }
    while(!eof){
        char* line = getLine();
        if(strlen(line)==0){break;}
        lineNo++;
        // debug(lineNo);
        line = skipWhiteSpace(line);
        if(strlen(line)==0 || isComment(line)){
            continue;
        }
        getToken(line,token);
        if(isDirective(token)){
            line += strlen(token);
            line = skipWhiteSpace(line);
            if(strlen(line)==0 || *line==';'){
                error++;
                snprintf(errorBuffer, 256, "%s", "Error: Expected a token");
                continue;
            }
            getToken(line,token);
            ret = isLabel(token);
            if(ret==0){
                error++;
                snprintf(errorBuffer, 256, "%s", "Error: Expected a label");
                continue;
            }
            else if(ret==3){
                error++;
                snprintf(errorBuffer, 256, "%s", "Error: Redeclaraion of label ");
                strcat(errorBuffer, token);
                writeError();
                continue;
            }
            if(token[strlen(token)-1]==':'){token[strlen(token)-1]='\0';line++;}
            addLabelToSymbolTable(token,locationCount);
            line += strlen(token);
            line = skipWhiteSpace(line);
            while(!(strlen(line)==0 || *line==';')){
                getToken(line,token);
                line+=strlen(token);
                if(token[strlen(token)-1]==','){
                    token[strlen(token)-1]='\0';
                }

                if(isNumber(token)){
                    error++;
                    snprintf(errorBuffer, 256, "%s", "Error: Expected an integer");
                    writeError();
                }
                line+=strlen(token);
                locationCount++;
                line = skipWhiteSpace(line);
            }
        continue;
        }
        getToken(line,token);
        ret = isLabel(token);
        if(ret==3){
            error++;
            snprintf(errorBuffer, 256, "%s", ("Error: Redeclaration of label "));
            strcat(errorBuffer, token);
            writeError();
            continue;
        }
        else if(ret==1 || ret == 2){
            // Label in first position, so a declaration.
            if(token[strlen(token)-1]==':'){token[strlen(token)-1]='\0';line++;}
            addLabelToSymbolTable(token,locationCount);
            line = line+strlen(token);
        }
        
        // token is now an instruction, or whitespace;
        line = skipWhiteSpace(line); 
        if(strlen(line)==0){
            continue;
        }
        if(isComment(line)){continue;}
        getToken(line,token);
        if(!isOpcode(token)){
            error++;
            snprintf(errorBuffer, 256, "%s", "Error: Expected an opcode");
            writeError();
        }
        struct opCodeList op;
        for(int i = 0; i < 16; i++){
            if(!strcmp(token,opcodes[i].mnemonic)){
                op = opcodes[i];
                break;
            }
        }
        locationCount++;
        line = line+strlen(token);
        line = skipWhiteSpace(line);
        if(op.op1==Null){
            if(strlen(line)==0){continue;}
            else if(*line==';'){continue;}
            error++;
            getToken(line,token);
            snprintf(errorBuffer, 256, "%s", "Error: Unexpected token ");
            strcat(errorBuffer,token);
            writeError();
            continue;
        }
        else{
            if(strlen(line)==0 || *line==';'){
                error++;
                snprintf(errorBuffer, 256, "%s", "Error: Expected a token");
                writeError();
                continue;
            }
            getToken(line,token);
            if(*token=='['){
                int ptr = 0;
                int er = 0;
                while(*(token+ptr)!=']'){
                    if(isspace(*(token+ptr))){
                        error++;
                        er=1;
                        snprintf(errorBuffer, 256, "%s", "Error: Unclosed ]");
                        writeError();
                        break;
                    }
                    ptr++;
                }
                if(er){continue;}
                char *tmp = token;
                tmp[ptr]='\0';
                tmp++;
                snprintf(token,MAXTOKENLENGTH,"%s",tmp);
                line+=2;
            }
            ret = isLabel(token);
            if(ret==1){
                if(token[strlen(token)-1]==':'){token[strlen(token)-1]='\0';line++;}
                addLabelToSymbolTable(token,-1);

            }
            locationCount++;
            line += strlen(token);
        }
        line = skipWhiteSpace(line);
        if(op.op2==Null){
            if(strlen(line)==0){continue;}
            else if(*line==';'){continue;}
            error++;
            getToken(line,token);
            snprintf(errorBuffer,256, "%s" ,"Error: Unexpected token ");
            strcat(errorBuffer,token);
            writeError();
            continue;
        }
        else{
            if(strlen(line) == 0 || *line == ';'){
                error++;
                snprintf(errorBuffer,256, "%s", "Error: Expected a token");
                writeError();
                continue;
            }
            getToken(line,token);
            if(*token=='['){
                int ptr = 0;
                int er = 0;
                while(*(token+ptr)!=']'){
                    if(isspace(*(token+ptr))){
                        error++;
                        er=1;
                        snprintf(errorBuffer, 256, "%s", "Error: Unclosed ]");
                        writeError();
                        break;
                    }
                    ptr++;
                }
                if(er){continue;}
                char *tmp = token;
                tmp[ptr]='\0';
                tmp++;
                snprintf(token, 256, "%s",tmp);
                line+=2;
            }
            ret = isLabel(token);
            if(token[strlen(token)-1]==':'){token[strlen(token)-1]='\0';line++;}
            if(ret==1){
                addLabelToSymbolTable(token,-1);
            }
            locationCount++;
            line += strlen(token);
        }
        line = skipWhiteSpace(line);
        if(!(strlen(line)==0 || *line == ';')){
            error++;
            getToken(line,token);
            snprintf(errorBuffer, 256, "%s", "Error: Unexpected token ");
            strcat(errorBuffer,token);
            writeError();   
        }
        continue;
    }
}

#ifdef _DEBUG
int main(){
    init();
    pass1();
    printf("\t\033[0;32mSymbol Table: \033[0m\n");
    printf("\033[0;34m%-20s %s", "Label", "LocationCounter\033[0m\n");
    for(int i = 0; i < symbolTableLength; i++){
        printf("%-21s%d\n", symbolTable[i].literal, symbolTable[i].LC);
    }
}
#endif