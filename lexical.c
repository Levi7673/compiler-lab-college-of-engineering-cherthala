#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define MAX 20

int main(){
    char str[MAX] , ch , keywords[][MAX] = {"int" , "float" , "do" , "while" , "char" , "for" , "if" , "else" , "return"};
    int i , line = 1 , token = 1 , flag , keycount = sizeof(keywords) / sizeof(keywords[0]);

    FILE *fp;

    fp = fopen("input.c" , "r");

    if(fp == NULL){
        printf("File not found !\n");
        return 1;
    }
    
    printf("LINE\tTOKEN\t\tTYPEt\tLEXEMES\n");
    while((ch=fgetc(fp))!=EOF){
        if(ch == '\n'){ line++ ; continue ;}
        if(ch == ' '|| ch=='\t'){ continue ;}
        if(strchr("+-*<>\%=/",ch)){
            printf("%d\t%d\t\tOPERATOR\t%c\n",line , token++ , ch);
            continue;
        }
        if(strchr("!@#$^&()[]\".,;:\\{}",ch)){
            printf("%d\t%d\t\tSPECIAL SYMBOL\t%c\n",line , token++ , ch);
            continue;
        }
        if(isalpha(ch)){
            i = 0;
            str[i++] = ch;
            while(isalnum(ch=fgetc(fp)))str[i++]=ch;
            str[i] = '\0';
            flag = 0 ;
            
            for(i=0 ; i<keycount ; i++){
                if(strcmp(keywords[i],str)==0){
                    flag = 1;
                    break;
                }
            }
            
            if(flag){
                printf("%d\t%d\t\tKEYWORD\t%s\n",line , token++ , str);
            ungetc(ch , fp);
            }else if(ch == '('){
                printf("%d\t%d\t\tFUNCTION\t%s\n",line , token++ , str);
            ungetc(ch , fp);
            }else{
                printf("%d\t%d\t\tIDENTIFIER\t%s\n",line , token++ , str);
            ungetc(ch , fp);
            }
            continue;
        }
        if(isdigit(ch)){
        i = 0;
            str[i++] = ch;
            while(isalnum(ch=fgetc(fp)))str[i++]=ch;
            str[i] = '\0';
            flag = 0 ;

            ungetc(ch , fp);
            printf("%d\t%d\t\tNUMERIC LITERAL\t%s\n",line , token++ , str);
            continue;
        }
        if(ch == '"'){
        i = 0;
            str[i++] = ch;
            while((ch=fgetc(fp))!='"' && ch!=EOF)str[i++]=ch;
            str[i++] = '"';
            str[i] = '\0';
            ungetc(ch , fp);
            printf("%d\t%d\t\tNUMERIC LITERAL\t%s\n",line , token++ , str);
            continue;
        }
    }
    fclose(fp);
}