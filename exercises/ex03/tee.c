#include <stdio.h>
#include <string.h>
#include <stdlib.h>

main(int argc, char *argv[]){

FILE *fp, *fp1;
char buffer;

if(argc != 4){
    printf("\nError");
    printf("\nSintaxis: tee [archivo1] [archivo2]\n");
    exit(0);
}

if(strcmp(argv[1], "tee") == 0){
    fp = fopen(argv[2], "r");
    fp1 = fopen(argv[3], "w");

    printf("\Content in %s:\n", argv[2]);

    while(!feof(fp)){
        buffer = fgetc(fp);
        fputc(buffer, fp1);
        printf("%c", buffer);
    }

    printf("\n\n%s received %s\n", argv[3], argv[2]);   

    fclose(fp);
    fclose(fp1);
    }
    else
        printf("\nThe first argument have to be tee\n");
}
