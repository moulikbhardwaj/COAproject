#include "asm.h"

int main(){
    init();
    pass1();
    if(error!=0){
        return error;
    }
    error=0;
    out = fopen("binFile", "w+");
    fseek(file,0,SEEK_SET);
    lineNo = 0;
    eof=0;
    pass2();
    cleanup();
    return error;
}