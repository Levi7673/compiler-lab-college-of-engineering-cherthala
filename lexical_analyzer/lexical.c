# include <stdio.h>
#include <string.h>
# include <ctype.h>

int main(){
    char ch , str[20] , keyword[][20] = {"int" , "float" , "char" , "while" , "for" , "if" , "do" , "return" , "break" , "continue" , "exit" , "default"};
    int i , j , flag , line = 1 , token = 0 ,keycount = sizeof(keyword) / sizeof(keyword[0]);
    //file pointer
    FILE *input , *output;

    input = fopen("input.txt" , "r");
    output = fopen("output.txt" , "w");

    fprintf(output , "%s\t\t%s\t\t%s\t\t%s\n", "line-no.","token-no.","token","lexeme");
    //while loop to scan each char 
    while((ch = fgetc(input)) != EOF ){
        //check whather it is a new line 
        if (ch == '\n'){
            line ++;
            continue;
        }
        //check weather it is a spaces or tab 
        if (ch == ' ' || ch == '\t'){
            continue;
        }
        //check if this is a operator 
        if (ch == '+' || ch == '-' ||ch == '*' ||ch == '/' ||ch == '=' ||ch == '^' ||ch == '%'){
            fprintf (output , "%d\t\t%d\t\t%s\t\t%c\n",line,token++,"Operator",ch);
            continue;
        }
        //check if this is a speacial char 
        if (ch == '!' || ch == '@' ||ch == '#' ||ch == '-' ||ch == '$' ||ch == '&' ||ch == ')'||ch == '('||ch == '{' ||ch == '}'){
        fprintf (output , "%d\t\t%d\t\t%s\t\t%c\n",line,token++,"Special symbol",ch);
        continue;
        }

        //isalpha()
        if (isalpha(ch)){
            i = 0;
            str[i++] = ch;
            flag = 0;
            while (isalnum(ch = fgetc(input))){
                str[i++] = ch;
            }
            ungetc(ch,input);
            str[i++] = '\0';
            
            //keyword matching 
            for (j=0 ; j<keycount ; j++){
                if (strcmp(str , keyword[j]) == 0){
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                fprintf(output , "%d\t\t%d\t\t%s\t\t%s\n",line,token++,"keyword",str);
            }
            else {
                fprintf(output , "%d\t\t%d\t\t%s\t\t%s\n",line,token++,"Identifier",str);
            }
        }

        //isdigit()
        if (isdigit(ch)){
            i = 0;
            str[i] = ch;
            while (isdigit(ch = fgetc(input))){
                str[i++] = ch;
            }
            ungetc(ch , input);
            str[i] = '\0';
            fprintf(output , "%d\t\t%d\t\t%s\t\t%s\n",line,token++,"Number",str);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}