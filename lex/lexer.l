%{
    #include<stdio.h>
%}

%%
"int"|"else"|"if"|"while"|"for"|"char"|"break"|"void"|"return" { printf ("%s\t\tKeyword\n", yytext); }

[a-zA-Z][a-zA-Z0-9]* { printf ("%s\t\tIdentifier\n", yytext); }

"+"|"-"|"*"|"/"|"="|"<"|">"|"^"|"%" { printf ("%s\t\tOperator\n", yytext); }

"("|")"|"{"|"}"|";"|","|"#"|":" { printf ("%s\t\tSpecial Symbol\n", yytext); }

[0-9]+ { printf ("%s\t\tNumber\n", yytext); }

[ \t\n]+ { /* ignore */ }

. { /* ignore */ }
%%

int yywrap(){
    return 1;
}

int main(){
    yyin = fopen ("input.txt" , "r");
    printf("Token\t\tType\n");
    yylex();
    return 0;
}