#include "asm.h"

int main(){
    error=0;
    symbolTableLength=0;
    file = fopen("../code.bak","r");
    pass1();
    if(error!=0){
        return 1;
    }
    // pass2();
    return 0;
}