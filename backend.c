#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    char arg1[20] , arg2[20] , op , result[20];
    fp = fopen("in.txt","r");

    if(fp == NULL){
        printf("File not found error.\n");
        exit(0);
    }

while(fscanf(fp,"%s =%s %c %s",
             result,arg1,&op,arg2) == 4) {
        printf("MOV AX , %s\n",arg1);
        
        if(op == '-'){
            printf("SUB AX , %s\n",arg2);
        }
        else if(op == '+'){
            printf("ADD AX , %s\n",arg2);
        }
        else if(op == '*'){
            printf("MOV BX , %s\n",arg2);
            printf("MUL BX\n");
        }
        else if(op == '/'){
            printf("MOV BX , %s\n",arg2);
            printf("MOV DX , 0\n");
            printf("DIV BX\n");
        }
        else {
            printf("Unsupported operator: %c\n\n", op);
            continue;
        }
        printf("MOV %s , AX\n\n",result);
    }
    fclose(fp);
    return 0;
}