#include <stdio.h>
#include <ctype.h>


int main(){
    FILE *input , *output;
    input = fopen("input.c" , "r");
    output = fopen("output.txt" , "r");

    char ch , str[20] , keyword[][20] = {"int" , "char" , "for" , "if" , "else" , "while" , "do" , "exit" , "break" , "default"};
    int keycount = sizeof(keyword) / sizeof(keyword[0]);
    printf("%d",keycount);
    int line = 0 , token = 0 , i , j , flag ;
    printf("line-no.\ttoken-no.\ttoken\tlexeme\n");
    while( ch = fgetc(input) != EOF){
        //operator checking 
        if(ch == '+' | ch == '-' | ch == '*' | ch == '/' | ch == '^' ){
            continue;
        }
        //special symbol checking
        else if (ch == '#' | ch == '@' | ch == '(' | ch == ')' | ch == ';' | ch == ':' | ch == ',' | ch == '?' | ch == '!' | ch == '@'){
            continue;
        }
        else if (isdigit(ch)){
            continue;
        }
        else if (isalpha(ch)){
            continue; 
            i = 0;
            str[i++] = ch;
            while( ch = fgetc(input) != EOF && isalnum(ch)){
                continue;
            } 
            for(j=0 ; j<keycount ; j++){
                continue;
            }
        }
    }
}