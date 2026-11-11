#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(){
    char str[100] , keywords[][20]={"int","float","do","for","break","continue","while","typedef","return","if","else","default"};
    int ch , op , next ,line = 1 ,flag , token = 0,quote, i ,keycount = sizeof(keywords)/sizeof(keywords[0]) ;

    FILE *fp = fopen("input.c","r");
    if(fp == NULL){
        printf("File not found error.\n");
        exit(0);
    }

    printf("LINE\t\t TOKEN\t\t TYPE\t\t LEXEME\n");
    while((ch = getc(fp))!=EOF){
        //newline  
        if(ch == '\n'){
            line ++;
            continue;
        }
        //space tab
        if(ch == ' ' || ch=='\t'){
            continue;
        }
        //keywords identifies function
        if(isalpha(ch) || ch == '_'){
            i = 0;
            str[i++] = ch;
            while(isalnum(ch=getc(fp)) || ch == '_') str[i++]=ch;
            str[i]='\0';

            flag=0;
            for(i=0 ;i<keycount ; i++){
                if(strcmp(str,keywords[i])==0){
                    flag=1;
                    break;
                }
            }
            if(ch != EOF){
                ungetc(ch,fp);
            }

            if(flag)
                printf("%d\t\t%d\t\t KEYWORD\t\t%s\n",line,token++,str);
            else if (ch == '(')
                printf("%d\t\t%d\t\t FUNCTION\t\t%s\n",line,token++,str);
            else
                printf("%d\t\t%d\t\t IDENTIFIER\t\t%s\n",line,token++,str);
            continue;
        }
        //numeric literal
        if(isdigit(ch)){
            i = 0;
            str[i++] = ch;
            while(isdigit(ch=getc(fp)) || ch == '.') str[i++]=ch;
            str[i]='\0';

            if(ch != EOF){
                ungetc(ch,fp);
            }
            printf("%d\t\t%d\t\t NUMERIC LITERAL\t\t%s\n",line,token++,str);
            continue;
        }
        //sting literals
        if(ch=='"' || ch == '\''){
            quote = ch;
            i = 0;
            str[i++] = ch;
            while((ch=getc(fp))!=quote){ 
                str[i++]=ch;
                if(ch=='\\'){
                    ch == getc(fp);
                    if(ch == EOF){
                        break;
                    }
                    str[i++] = ch;
                }
            }

            if(quote == ch){
                str[i++] = quote; 
            }
            str[i]='\0';

            if(quote == '"')
                printf("%d\t\t%d\t\t STRING LITERAL\t\t%s\n",line,token++,str);
            else
                printf("%d\t\t%d\t\t CHARATER LITERAL\t\t%s\n",line,token++,str);
            continue;
        }
        //comments
        if(ch=='\\'){
            next = getc(fp);
            if(next == '\\'){
                while((ch=getc(fp))!=EOF){
                    if(ch=='\n') line++;
                }
            }
            if(next != EOF){
                ungetc(next,fp);
            }
            continue;
        }
        //operands
        if(strchr("!=*/+-&",ch)){
            op = ch;
            next = getc(fp);

             if(((op=='+') && (next=='+' || next=='=')) ||
                ((op=='-') && (next=='-' || next=='=')) ||
                ((op=='>') && (next=='>' || next=='=')) ||
                ((op=='<') && (next=='<' || next=='=')) ||
                ((op=='!') && (next=='=')) ||
                ((op=='=') && (next=='=')) ) printf("%d\t\t%d\t\t OPERATOR\t\t%c%c\n",line,token++,op,next);
                else {
                     if(next != EOF){
                ungetc(next,fp);
            }
                    printf("%d\t\t%d\t\t OPERATOR\t\t%c\n",line,token++,op);
                }
                continue;
        }
        
        //special charaters
        if(strchr("@#$^({[';:?.,]})",ch)){
            printf("%d\t\t%d\t\t FUNCTION\t\t%c\n",line,token++,ch);
        }
    }
    return 0;
}