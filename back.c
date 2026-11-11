#include<stdio.h>
#include<stdlib.h>

#define MAX 30
int main(){
    char arg1[MAX] , arg2[MAX] , result , op;

    FILE *fp;
    fp = fopen("input.txt" , "r");

    if (fp == NULL){
        printf("File not found !\n");
        exit(0);
    } 
    while(fscanf(fp , " %c = %s %c %s" , &result , arg1 , &op , arg2)==4){
        printf("MOV AX , %s\n",arg1);

        if(op == '+') printf("ADD AX , %s\n",arg2);
        else if(op == '-') printf("SUB AX , %s\n",arg2);
        else if(op == '*'){
            printf("MOV BX , %s\n",arg2);
            printf("MUL BX\n");
        }
        else if(op == '/'){
            printf("MOV BX , %s\n",arg2);
            printf("MOV DX , 0\n");
            printf("DIV BX\n");
        }
        else{
            printf("Unsupported operator!\n");
            return 1;
        }
        printf("MOV %c , AX\n\n", result);
    }
    return 0;
}