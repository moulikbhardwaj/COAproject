#include "simulator.h"

void init(){
    nm=0;
    registerA = (int*)malloc(sizeof(int));
    registerB = (int*)malloc(sizeof(int));;
    registerC = (int*)malloc(sizeof(int));;
    registerD = (int*)malloc(sizeof(int));;
    registerMA = (int*)malloc(sizeof(int));;
    registerMB = (int*)malloc(sizeof(int));;
    SP = &memory[1023];
    opcode = (__uint8_t*)malloc(sizeof(__uint8_t));;
    param0 = (__uint8_t*)malloc(sizeof(__uint8_t));;
    param1 = (__uint8_t*)malloc(sizeof(__uint8_t));;
}

void cleanup(){
    free(registerA);
    free(registerB);
    free(registerC);
    free(registerD);
    free(registerMA);
    free(registerMB);
    free(opcode);
    free(param0);
    free(param1);
}

int main(int argc, char** argv){
    init();
    if(argc!=4){
        printf("Error: Expected InputFile, OutputFile, symbolTableFile");
        return 1;
    }
    binFile = fopen(argv[1],"r");
    OPfile = fopen(argv[2],"w+");
    Symbol = fopen(argv[3],"r");
    char buffer[21];
    int addr;
    symbolTableLength=0;
    fscanf(Symbol,"%s %s", buffer, buffer);
    while(fscanf(Symbol,"%s %d", buffer, &addr)>0){
        table[symbolTableLength].addr=addr;
        snprintf(table[symbolTableLength].symbol,21,"%s", buffer);
        symbolTableLength++;
    }
    fseek(binFile,0,SEEK_END);
    int fsize = (int)ftell(binFile);
    fseek(binFile,0,SEEK_SET);
    for(int i = 0; i < fsize; i++){
        __uint8_t ch = getc(binFile);
        memory[i] = ch;
    }
    fclose(binFile);
    SP=&memory[1023];
    while(LC < fsize){
        nm++;
        // Opcode Fetch
        readbits(opcode);
        incrementLC();

        // Opcode Decode
        decodeOpcode();

        // If more operators are required
        if(requiredOperands>=1){
            readbits(param0);
            incrementLC();
        }
        if(requiredOperands>=2){
            readbits(param1);
            incrementLC();
        }
        // execution cycle
        executeOpcode();
        writeDT();
    }
    cleanup();
    return 0;
}