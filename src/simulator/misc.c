#include "simulator.h"

int *accessMemroy(int location){
    return &memory[location];
}

void readbits(__uint8_t *field){
    *field = memory[LC];
}

void incrementLC(){
    LC++;
}

void decodeOpcode(){
    __uint8_t tmp = (*opcode)>>4;
    switch (tmp){
    // MOV
    case 0b0000:
        myStrcpy(function,"MOV");
        requiredOperands=2;
        break;

    // ADD
    case 0b0001:
        myStrcpy(function,"ADD");
        requiredOperands=2;
        break;

    // SUB
    case 0b0010:
        myStrcpy(function,"SUB");
        requiredOperands=2;
        break;

    // CMP
    case 0b0011:
        myStrcpy(function,"CMP");
        requiredOperands=2;
        break;

    // RSH
    case 0b0100:
        myStrcpy(function,"RSH");
        requiredOperands=2;
        break;

    // CMPL
    case 0b0101:
        myStrcpy(function,"CMPL");
        requiredOperands=1;
        break;

    // PUSH
    case 0b0110:
        myStrcpy(function,"PUSH");
        requiredOperands=1;
        break;

    // POP
    case 0b0111:
        myStrcpy(function,"POP");
        requiredOperands=0;
        break;
    
    // MCP
    case 0b1000:
        myStrcpy(function,"MCP");
        requiredOperands=2;
        break;
    
    // CALL
    case 0b1001:
        myStrcpy(function,"CALL");
        requiredOperands=1;
        break;

    // RET
    case 0b1010:
        myStrcpy(function,"RET");
        requiredOperands=0;
        break;

    // JG
    case 0b1011:
        myStrcpy(function,"JG");
        requiredOperands=1;
        break;

    // JGE
    case 0b1100:
        myStrcpy(function,"JGE");
        requiredOperands=1;
        break;

    // JL
    case 0b1101:
        myStrcpy(function,"JL");
        requiredOperands=1;
        break;

    // JLE
    case 0b1110:
        myStrcpy(function,"JLE");
        requiredOperands=1;
        break;

    // JMP
    case 0b1111:
        myStrcpy(function,"JMP");
        requiredOperands=1;
        break;
    }
    int tmp0 = (*opcode&(0b00001100))>>2;
    int tmp1 = (*opcode&(0b00000011));
    if(requiredOperands==0){
        p0=p_Null;
        p1=p_Null;
    }
    if(requiredOperands>=1){
        switch (tmp0){
        case 0b00:
            p0=p_Register;
            break;
        case 0b01:
            p0=p_Immidiate;
            break;
        case 0b10:
            p0=p_Dereference;
            break;
        case 0b11:
            p0=p_Memory;
            break;
        }
    }
    if(requiredOperands==2){
        switch (tmp1){
        case 0b00:
            p1=p_Register;
            break;
        case 0b01:
            p1=p_Immidiate;
            break;
        case 0b10:
            p1=p_Dereference;
            break;
        case 0b11:
            p1=p_Memory;
            break;
        }
    }
}

int* resolveRegister(__uint8_t reg){
    if(reg==0b00000000){
        return SP;
    }
    else if(reg==0b00000001){
        return registerA;
    }
    else if(reg==0b00000010){
        return registerB;
    }
    else if(reg==0b00000011){
        return registerC;
    }
    else if(reg==0b00000100){
        return registerD;
    }
    else if(reg==0b00000101){
        return registerMA;
    }
    else if(reg==0b00000110){
        return registerMB;
    }
    return NULL;
}

void myStrcpy(char* dest, char* src){
    snprintf(dest,5,"%s",src);
}

void executeOpcode(){
    if(requiredOperands==0){
        if(!strcmp("POP",function)){
            POP();
        }
        else if(!strcmp("RET",function)){
            RET();
        }
    }
    else if(requiredOperands==1){
        if(!strcmp("CMPL",function)){
            CMPL();
        }
        else if(!strcmp("PUSH",function)){
            PUSH();
        }
        else if(!strcmp("CALL",function)){
            CALL();
        }
        else if(!strcmp("JG",function)){
            JG();
        }
        else if(!strcmp("JGE",function)){
            JGE();
        }
        else if(!strcmp("JL",function)){
            JL();
        }
        else if(!strcmp("JLE",function)){
            JLE();
        }
        else if(!strcmp("JMP",function)){
            JMP();
        }
    }
    else{
        if(!strcmp("MOV",function)){
            MOV();
        }
        else if(!strcmp("MCP",function)){
            MCP();
        }
        else if(!strcmp("ADD",function)){
            ADD();
        }
        else if(!strcmp("SUB",function)){
            SUB();
        }
        else if(!strcmp("CMP",function)){
            CMP();
        }
        else if(!strcmp("RSH",function)){
            RSH();
        } 
    }
}

void POP(){
    SP++;
}

void RET(){
    LC = *SP;
    SP++;
}

void CMPL(){
    int* memoryCell0 = (int*)malloc(sizeof(int));
    int* deleter = memoryCell0;
    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Dereference){
        memoryCell0 = accessMemroy(*param0);
    }
    *memoryCell0 = (-1)^(*memoryCell0);
    free(deleter);
    return ;
}

void PUSH(){
    int* memoryCell0 = (int*)malloc(sizeof(int));
    int* deleter = memoryCell0;
    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        *memoryCell0 = *param0;
    }
    else if(p0==p_Memory){
        if(*param0==0b0000){
            memoryCell0 = SP;
        }
        else if(*param0==0b0101){
            memoryCell0 = registerMA;
        }
        else if(*param0==0b0110){
            memoryCell0 = registerMB;
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }
    else if(p0==p_Dereference){
        if(*param0==0b0000){
            memoryCell0 = accessMemroy(*SP);
        }
        else if(*param0==0b0101){
            memoryCell0 = accessMemroy(*registerMA);
        }
        else if(*param0==0b0110){
            memoryCell0 = accessMemroy(*registerMB);
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }
    SP--;
    *SP = *memoryCell0;
    free(deleter);
    return ;
}

void CALL(){
    SP--;
    *SP = LC;
    LC = *param0+(((*opcode)&0b00000011)<<8);
}


void JG(){
    if(*registerA>0){
        LC = *param0+(((*opcode)&0b00000011)<<8);
    }
}

void JGE(){
    if(*registerA>=0){
        LC = *param0 + (((*opcode) & 0b00000011) << 8);
    }
}

void JL(){
    if(*registerA<0){
        LC = *param0+(((*opcode)&0b00000011)<<8);
    }
}

void JLE(){
    if(*registerA<=0){
        LC = *param0+(((*opcode)&0b00000011)<<8);
    }
}

void JMP(){
    LC = *param0+(((*opcode)&0b00000011)<<8);
}

void MOV(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *memoryCell1 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    int *deleter1 = memoryCell1;

    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
        exit(1);
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = resolveRegister(*param0);
        }
        else{
            fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
            exit(1);
        }
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = accessMemroy(*resolveRegister(*param0));
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }

    if(p1==p_Register){
        *memoryCell1 = *resolveRegister(*param1);
    }
    else if(p1==p_Immidiate){
        *memoryCell1 = *param1;
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *resolveRegister(*param1); 
        }
        else{
            *memoryCell1 = *param1;
        }
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *accessMemroy(*resolveRegister(*param1));
        }
        else{
            *memoryCell1 = *accessMemroy(*param1);
        }
    }

    *memoryCell0 = *memoryCell1;
    free(deleter0);
    free(deleter1);
}

void MCP(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    if(!(p0==p_Register || p0==p_Memory)){
        fprintf(stderr, "Error: lval expected to be register at token %d\n", LC-2);
        exit(1);
    }
    if(p0==p_Memory){
        if(resolveRegister(*param0)==NULL){
            fprintf(stderr, "Error: lval expected to be register at token %d\n", LC-2);
            exit(1);
        }
        memoryCell0 = resolveRegister(*param0);
    }
    if(p1!= p_Memory){
        fprintf(stderr, "Error: rval expected to be memory at token %d\n", LC-1);
        exit(1);
    }
    if(*param1==0b0000){
        *memoryCell0 = SP-memory;
    }
    else{
        *memoryCell0 = *param1;
    }

    free(deleter0);
}

void ADD(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *memoryCell1 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    int *deleter1 = memoryCell1;

    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
        exit(1);
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = resolveRegister(*param0);
        }
        else{
            fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
            exit(1);
        }
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = accessMemroy(*resolveRegister(*param0));
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }

    if(p1==p_Register){
        *memoryCell1 = *resolveRegister(*param1);
    }
    else if(p1==p_Immidiate){
        *memoryCell1 = *param1;
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *resolveRegister(*param1); 
        }
        else{
            *memoryCell1 = *param1;
        }
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *accessMemroy(*resolveRegister(*param1));
        }
        else{
            *memoryCell1 = *accessMemroy(*param1);
        }
    }

    *memoryCell0 += *memoryCell1;
    free(deleter0);
    free(deleter1);
}

void SUB(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *memoryCell1 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    int *deleter1 = memoryCell1;

    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
        exit(1);
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = resolveRegister(*param0);
        }
        else{
            fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
            exit(1);
        }
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = accessMemroy(*resolveRegister(*param0));
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }

    if(p1==p_Register){
        *memoryCell1 = *resolveRegister(*param1);
    }
    else if(p1==p_Immidiate){
        *memoryCell1 = *param1;
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *resolveRegister(*param1); 
        }
        else{
            *memoryCell1 = *param1;
        }
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *accessMemroy(*resolveRegister(*param1));
        }
        else{
            *memoryCell1 = *accessMemroy(*param1);
        }
    }

    *memoryCell0 -= *memoryCell1;
    free(deleter0);
    free(deleter1);
}

void CMP(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *memoryCell1 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    int *deleter1 = memoryCell1;

    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
        exit(1);
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = resolveRegister(*param0);
        }
        else{
            fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
            exit(1);
        }
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = accessMemroy(*resolveRegister(*param0));
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }

    if(p1==p_Register){
        *memoryCell1 = *resolveRegister(*param1);
    }
    else if(p1==p_Immidiate){
        *memoryCell1 = *param1;
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *resolveRegister(*param1); 
        }
        else{
            *memoryCell1 = *param1;
        }
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *accessMemroy(*resolveRegister(*param1));
        }
        else{
            *memoryCell1 = *accessMemroy(*param1);
        }
    }

    *registerA = (*memoryCell0 - *memoryCell1);
    free(deleter0);
    free(deleter1);
}

void RSH(){
    int *memoryCell0 = (int *)malloc(sizeof(int));
    int *memoryCell1 = (int *)malloc(sizeof(int));
    int *deleter0 = memoryCell0;
    int *deleter1 = memoryCell1;

    if(p0==p_Register){
        memoryCell0 = resolveRegister(*param0);
    }
    else if(p0==p_Immidiate){
        fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
        exit(1);
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = resolveRegister(*param0);
        }
        else{
            fprintf(stderr, "Error: Invalid lval at token %d\n", LC-2);
            exit(1);
        }
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            memoryCell0 = accessMemroy(*resolveRegister(*param0));
        }
        else{
            memoryCell0 = accessMemroy(*param0);
        }
    }

    if(p1==p_Register){
        *memoryCell1 = *resolveRegister(*param1);
    }
    else if(p1==p_Immidiate){
        *memoryCell1 = *param1;
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *resolveRegister(*param1); 
        }
        else{
            *memoryCell1 = *param1;
        }
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            *memoryCell1 = *accessMemroy(*resolveRegister(*param1));
        }
        else{
            *memoryCell1 = *accessMemroy(*param1);
        }
    }

    *memoryCell0 >>= *memoryCell1;
    free(deleter0);
    free(deleter1);
}

void writeDT(){
    char token0[25];
    char token1[25];
    if(p0==p_Register){
        switch (*param0){
        case 0b0000:
            myStrcpy(token0,"SP");
            break;
        case 0b0001:
            myStrcpy(token0, "A");
            break;
        case 0b0010:
            myStrcpy(token0, "B");
            break;
        case 0b0011:
            myStrcpy(token0, "C");
            break;
        case 0b0100:
            myStrcpy(token0, "D");
            break;
        case 0b0101:
            myStrcpy(token0, "MA");
            break;
        case 0b0110:
            myStrcpy(token0, "MB");
            break;
        }
    }
    else if(p0==p_Immidiate){
        snprintf(token0,25,"$%d",*param0);
    }
    else if(p0==p_Dereference){
        if(resolveRegister(*param0)!=NULL){
            switch(*param0){
                case 0b0000:
                    snprintf(token0,25,"[SP]");
                    break;
                case 0b0001:
                    snprintf(token0,25, "[A]");
                    break;
                case 0b0010:
                    snprintf(token0,25, "[B]");
                    break;
                case 0b0011:
                    snprintf(token0,25, "[C]");
                    break;
                case 0b0100:
                    snprintf(token0,25, "[D]");
                    break;
                case 0b0101:
                    snprintf(token0,25, "[MA]");
                    break;
                case 0b0110:
                    snprintf(token0,25, "[MB]");
                    break;
            }
        }
        else{
            int ln = 0;
            for(int i = 0; i < symbolTableLength; i++){
                if(table[i].addr==*param0){
                    ln = i;
                    break;
                }
            }
            snprintf(token0, 25, "[%s]",table[ln].symbol);
        }
    }
    else if(p0==p_Memory){
        if(resolveRegister(*param0)!=NULL){
            switch(*param0){
                case 0b0000:
                    snprintf(token0,25,"SP");
                    break;
                case 0b0001:
                    snprintf(token0,25, "A");
                    break;
                case 0b0010:
                    snprintf(token0,25, "B");
                    break;
                case 0b0011:
                    snprintf(token0,25, "C");
                    break;
                case 0b0100:
                    snprintf(token0,25, "D");
                    break;
                case 0b0101:
                    snprintf(token0,25, "MA");
                    break;
                case 0b0110:
                    snprintf(token0,25, "MB");
                    break;
            }
        }
        else{
            int ln = 0;
            for(int i = 0; i < symbolTableLength; i++){
                if(table[i].addr==*param0){
                    ln = i;
                    break;
                }
            }
            snprintf(token0, 25, "%s",table[ln].symbol);
        }
    }
    if(p1==p_Register){
        switch (*param1){
        case 0b0000:
            myStrcpy(token1,"SP");
            break;
        case 0b0001:
            myStrcpy(token1, "A");
            break;
        case 0b0010:
            myStrcpy(token1, "B");
            break;
        case 0b0011:
            myStrcpy(token1, "C");
            break;
        case 0b0100:
            myStrcpy(token1, "D");
            break;
        case 0b0101:
            myStrcpy(token1, "MA");
            break;
        case 0b0110:
            myStrcpy(token1, "MB");
            break;
        }
    }
    else if(p1==p_Immidiate){
        snprintf(token1,25,"$%d",*param1);
    }
    else if(p1==p_Dereference){
        if(resolveRegister(*param1)!=NULL){
            switch(*param1){
                case 0b0000:
                    snprintf(token1,25,"[SP]");
                    break;
                case 0b0001:
                    snprintf(token1,25, "[A]");
                    break;
                case 0b0010:
                    snprintf(token1,25, "[B]");
                    break;
                case 0b0011:
                    snprintf(token1,25, "[C]");
                    break;
                case 0b0100:
                    snprintf(token1,25, "[D]");
                    break;
                case 0b0101:
                    snprintf(token1,25, "[MA]");
                    break;
                case 0b0110:
                    snprintf(token1,25, "[MB]");
                    break;
            }
        }
        else{
            int ln = 0;
            for(int i = 0; i < symbolTableLength; i++){
                if(table[i].addr==*param1){
                    ln = i;
                    break;
                }
            }
            snprintf(token1, 25, "[%s]",table[ln].symbol);
        }
    }
    else if(p1==p_Memory){
        if(resolveRegister(*param1)!=NULL){
            switch(*param1){
                case 0b0000:
                    snprintf(token1,25,"SP");
                    break;
                case 0b0001:
                    snprintf(token1,25, "A");
                    break;
                case 0b0010:
                    snprintf(token1,25, "B");
                    break;
                case 0b0011:
                    snprintf(token1,25, "C");
                    break;
                case 0b0100:
                    snprintf(token1,25, "D");
                    break;
                case 0b0101:
                    snprintf(token1,25, "MA");
                    break;
                case 0b0110:
                    snprintf(token1,25, "MB");
                    break;
            }
        }
        else{
            int ln = 0;
            for(int i = 0; i < symbolTableLength; i++){
                if(table[i].addr==*param1){
                    ln = i;
                    break;
                }
            }
            snprintf(token1, 25, "%s",table[ln].symbol);
        }
    }
    int n = memory[11];
    fprintf(OPfile,"*tokenNo:%d, line:%s %s %s, A:%d, B:%d, C:%d, D:%d, MA:%d, MB:%d, SP:%d, SIZE:%d, ARRAY:{", LC, function, token0, token1, (*registerA)&0b1111111111, (*registerB)&0b1111111111, (*registerC)&0b1111111111, (*registerD)&0b1111111111, (*registerMA)&0b1111111111, (*registerMB)&0b1111111111, *SP&0b1111111111, n);
    for(int i = 0; i < n; i++){
        fprintf(OPfile,"%d ", memory[12+i]&0b1111111111);
    }
    fprintf(OPfile,"}*\n");
}