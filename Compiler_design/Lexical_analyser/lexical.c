#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main (){
    FILE *output1 , *input;
    char ch , str[20];
    int i , j , flag , line=1 , token =0;
    char KEYWORD [][20] = {"int" , "if" , "else" , "for" , "while" , "do" , "main" , "char" , "float" , "default"};
    int Keycount = sizeof(KEYWORD) / sizeof(KEYWORD[0]);
    printf("%d" , Keycount);

    input = fopen("input.txt" , "r");
    output1 = fopen("output1.txt" , "w");

    fprintf(output1 , "Line no.\tToken no.\tToken\tLexeme\n");
    //operator -> special symbol -> digit -> identifier/keyword
    while(ch = (fgetc(input) != EOF)){
        if(ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "%"){
            fprintf(output1 , "%d\t\t%d\t\tOPERATOR\t%c" ,line , token++ , ch);
        }
        else if(ch == ";" || ch == "," || ch =="@" || ch =="?" || ch =="(" || ch ==")" ){
            fprintf(output1 , "%d\t\t%d\t\tSPEIAL SYMBOLS\t%c" ,line , token++ , ch);
        }
        else if (isdigit){
            fprintf(output1 , "%d\t\t%d\t\tDIGIT\t%c" ,line , token++ , ch);
        }
        else if (isalpha(ch)){
            i=0;
            str[i++] = ch;
            while(ch = fgetc(input) != EOF && isalnum(ch)){
                str[i++] = ch;
            }
            str[i] = '\0';
            flag =0;
            for(j=0 ; j<=Keycount ; j++ ){
                flag = 1;
                break;
            }
            if(flag){
                fprintf(output1 , "%d\t\t%d\t\tKEYWORD\t%c" ,line , token++ , ch);
            }else{
                fprintf(output1 , "%d\t\t%d\t\tIDENTIFIER\t%c" ,line , token++ , ch);
            }
        }
        else if (ch == '\n')
        {
            line++;
        }
    }

    fclose(output1);
    fclose(input);
}
