#include "asm.h"

int idx;

void write(__uint8_t dt){
    fprintf(out, "%c",dt);
}

void debugp2(){
    if(lineNo==128){
        fprintf(stderr,"DEbug");
    }
}

void pass2(){
    while(!eof){
        char* line = getLine();
        lineNo++;
        debugp2();
        char token[MAXTOKENLENGTH+1];
        line = skipWhiteSpace(line);
        if((strlen(line)==0) || (*line==';')){continue;}
        getToken(line,token);
        if(isDirective(token)){
            line += strlen(token);
            line = skipWhiteSpace(line);
            getToken(line,token);
            line += strlen(token);
            line = skipWhiteSpace(line);
            while(!(strlen(line)==0 || *line == ';')){
                getToken(line,token);
                char* end;
                __uint8_t dt = strtol(token,&end,10);
                write(dt);
                line+=strlen(token);
                line = skipWhiteSpace(line);
                line++;
            }
            continue;
        }
        if(isLabel(token)){
            line+=strlen(token);
            line = skipWhiteSpace(line);
            getToken(line,token);
        }
        if(isOpcode(token)){
            char* opcode = token;
            idx =getOpcodeIdx(opcode);
            line+=strlen(token);
            __uint8_t dt = opCodes[idx].opcode << 4;
            line = skipWhiteSpace(line);
            if(opCodes[idx].paramNum==0){
                dt|=0b00000000;
            }
            if(opCodes[idx].paramNum>=1){
                getToken(line,token);
                line+=strlen(token);
                line=skipWhiteSpace(line);
                p0=0b00000000;
                if(isRegister(token) && strcmp(token,"SP") && strcmp(token,"MA")  && strcmp(token,"MB")){
                    dt|=0b00000000;
                    if(!strcmp("SP",token)){
                        p0 = 0b00000000;
                    }
                    else if(!strcmp("MA",token)){
                        p0 = 0b00000101;
                    }
                    else if(!strcmp("MB",token)){
                        p0 = 0b00000110;
                    }
                    else if(!strcmp("A",token)){
                        p0 = 0b00000001;
                    }
                    else if(!strcmp("B",token)){
                        p0 = 0b00000010;
                    }
                    else if(!strcmp("C",token)){
                        p0 = 0b00000011;
                    }
                    else if(!strcmp("D",token)){
                        p0 = 0b00000100;
                    }
                }
                else if(*token=='$'){
                    char* tmp;
                    p0 = strtol(token+1,&tmp,10);
                    dt|=0b00000100;
                }
                else if(*token == '['){
                    dt|=0b00001000;
                    char *tmp = token+1;
                    tmp[strlen(tmp)-1]='\0';
                    snprintf(token,strlen(tmp)+1,"%s",tmp);
                    if(!isRegister(token)){
                        error++;
                        snprintf(errorBuffer,256,"%s", "Error: Expected a register");
                        writeError();
                        continue;
                    }
                    if(!strcmp("SP",token)){
                        p0 = 0b00000000;
                    }
                    else if(!strcmp("MA",token)){
                        p0 = 0b00000101;
                    }
                    else if(!strcmp("MB",token)){
                        p0 = 0b00000110;
                    }
                    else if(!strcmp("A",token)){
                        p0 = 0b00000001;
                    }
                    else if(!strcmp("B",token)){
                        p0 = 0b00000010;
                    }
                    else if(!strcmp("C",token)){
                        p0 = 0b00000011;
                    }
                    else if(!strcmp("D",token)){
                        p0 = 0b00000100;
                    }
                }
                else{
                    if(isRegister(token)){
                        dt|=0b00000000;
                        if(!strcmp(token,"SP")){
                            p0=0b0000000;
                        }
                        else if(!strcmp(token,"MA")){
                            p0=0b00000101;
                        }
                        else if(!strcmp(token,"MB")){
                            p0=0b00000110;
                        }
                    }
                    else{
                        int addr = getAddr(token);
                        if(opCodes[idx].opcode>=0b1010 && addr>=512){
                            dt|=0b00000010;
                            addr-=512;
                        }
                        if(opCodes[idx].opcode>=0b1010 && addr>=256){
                            dt|=0b00000001;
                            addr-=256;
                        }
                        dt |=0b00001100;
                        p0 = getAddr(token);
                    }
                }
            }
            if(opCodes[idx].paramNum==2){
                getToken(line,token);
                line+=strlen(token);
                line=skipWhiteSpace(line);
                p1=0b00000000;
                if(isRegister(token) && strcmp(token,"SP") && strcmp(token,"MA")  && strcmp(token,"MB")){
                    dt|=0b00000000;
                    if(!strcmp("SP",token)){
                        p1 = 0b00000000;
                    }
                    else if(!strcmp("MA",token)){
                        p1 = 0b00000101;
                    }
                    else if(!strcmp("MB",token)){
                        p1 = 0b00000110;
                    }
                    else if(!strcmp("A",token)){
                        p1 = 0b00000001;
                    }
                    else if(!strcmp("B",token)){
                        p1 = 0b00000010;
                    }
                    else if(!strcmp("C",token)){
                        p1 = 0b00000011;
                    }
                    else if(!strcmp("D",token)){
                        p1 = 0b00000100;
                    }
                }
                else if(*token=='$'){
                    char* tmp;
                    p1 = strtol(token+1,&tmp,10);
                    dt|=0b00000001;
                }
                else if(*token == '['){
                    dt|=0b00000010;
                    char *tmp = token+1;
                    tmp[strlen(tmp)-1]='\0';
                    snprintf(token,strlen(tmp)+1,"%s",tmp);
                    if(!isRegister(token)){
                        error++;
                        snprintf(errorBuffer,256,"%s", "Error: Expected a register");
                        writeError();
                        continue;
                        if(!strcmp("SP",token)){
                            p1 = 0b00000000;
                        }
                        else if(!strcmp("MA",token)){
                            p1 = 0b00000101;
                        }
                        else if(!strcmp("MB",token)){
                            p1 = 0b00000110;
                        }
                        else if(!strcmp("A",token)){
                            p1 = 0b00000001;
                        }
                        else if(!strcmp("B",token)){
                            p1 = 0b00000010;
                        }
                        else if(!strcmp("C",token)){
                            p1 = 0b00000011;
                        }
                        else if(!strcmp("D",token)){
                            p1 = 0b00000100;
                        }
                    }
                }
                else{
                    if(isRegister(token)){
                        if(!strcmp("SP",token)){
                            p1 = 0b00000000;
                        }
                        else if(!strcmp("MA",token)){
                            p1 = 0b00000101;
                        }
                        else if(!strcmp("MB",token)){
                            p1 = 0b00000110;
                        }
                    }
                    else{
                        dt |=0b00000011;
                        p1 = getAddr(token);
                    }
                }
            }
            write(dt);
            if(opCodes[idx].paramNum>=1){
                write(p0);
            }
            if(opCodes[idx].paramNum>=2){
                write(p1);
            }
        }
    }
}