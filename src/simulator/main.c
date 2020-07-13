#include "simulator.h"

void init(){
    nm=0;
    registerA = (int*)malloc(sizeof(int));
    registerB = (int*)malloc(sizeof(int));;
    registerC = (int*)malloc(sizeof(int));;
    registerD = (int*)malloc(sizeof(int));;
    registerMA = (int*)malloc(sizeof(int));;
    registerMB = (int*)malloc(sizeof(int));;
    SP = (int*)malloc(sizeof(int));;
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
    free(SP);
    free(opcode);
    free(param0);
    free(param1);
}

int main(int argc, char** argv){
    init();
    if(argc==2){
        binFile = fopen(argv[1],"r");
    }
    else{
        binFile = fopen("binFile","r");
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
        fprintf(stderr, "function to be executed: %s\n", function);
        if(requiredOperands>=1){
            readbits(param0);
            incrementLC();
        }
        if(requiredOperands>=2){
            readbits(param1);
            incrementLC();
        }
        // execution cycle
        // if(LC==24){
        //     printf(" ");
        // }
        executeOpcode();
    }
    FILE *ramdump = fopen("ramdump","w");
    for(int i = 0; i < fsize; i++){
        char dt = memory[i];
        fprintf(ramdump,"%c",dt);
    }
    cleanup();
    return 0;
}