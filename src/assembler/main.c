#include "asm.h"

int main(int argc, char** argv){
    if(argc!=4){
        error++;
        snprintf(errorBuffer,256,"Error: Expected InputFile, OutputFile, and file for Symbol Table");
        printf("\033[0;31m %s\033[0m\n", errorBuffer);
        return error;
    }
    snprintf(inputFileName,256,"%s",argv[1]);
    snprintf(outputFileName,256,"%s",argv[2]);
    snprintf(symbolTableFileName,256,"%s",argv[3]);
    init();
    pass1();
    if(error!=0){
        return error;
    }
    error=0;
    fseek(file,0,SEEK_SET);
    lineNo = 0;
    eof=0;
    pass2();
    fprintf(symbolFile,"%-20s %s", "Label", "LocationCounter\n");
    for(int i = 0; i < symbolTableLength; i++){
        fprintf(symbolFile,"%-21s%d\n", symbolTable[i].literal, symbolTable[i].LC);
    }
    cleanup();
    return error;
}