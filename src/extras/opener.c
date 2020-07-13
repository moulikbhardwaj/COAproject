#include <stdio.h>

int main(int argc, char** argv){
    FILE *ramdump;
    if(argc==1){
        ramdump = fopen("ramdump","r");
    }
    else{
        ramdump = fopen(argv[1],"r");
    }
    fseek(ramdump,0,SEEK_END);
    int fsize = ftell(ramdump);
    fseek(ramdump,0,SEEK_SET);
    for(int i = 0; i < fsize; i++){
        unsigned char dt = getc(ramdump);
        int tmp = dt;
        char buffer[8];
        for(int i = 0; i < 8; i++){
            buffer[7-i]=(dt%2)+'0';
            dt/=2;
        }
        printf("token:%d\t\t%s\t\t%d\n",i,buffer,tmp);
    }
}