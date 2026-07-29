%{
#include <stdio.h>
#include <stdlib.h>

// Global counter for Serial Number
int serial_no = 1;
%}

/* Tell Lex to automatically maintain the current line number in yylineno */
%option yylineno

/* Regular Expressions for our token classes */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
NUMBER      {DIGIT}+(\.{DIGIT}+)?
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
OPERATOR    "+"|"-"|"*"|"/"|"="|"=="|"<"|">"|"<="|">="|"!="|"&&"|"||"
SEPARATOR   ";"|","|"("|")"|"{"|"}"|"["|"]"
SYMBOL      "@"|"#"|"$"|"%"|"^"|"&"|"_"|"?"|"~"

%%

{OPERATOR}    { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Operator", yytext); }
{SEPARATOR}   { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Separator", yytext); }
{NUMBER}      { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Number", yytext); }
{IDENTIFIER}  { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Identifier", yytext); }
{SYMBOL}      { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Symbol", yytext); }

[ \t\r]+      { /* Ignore spaces, tabs, and carriage returns */ }
\n            { /* Ignore explicit newline action since %option yylineno tracks it automatically */ }
.             { printf("%-6d %-8d %-12s %-s\n", serial_no++, yylineno, "Unknown", yytext); }

%%

int main() {
    // Open input.txt for reading
    yyin = fopen("input.txt", "r");

    // Check if the file exists and was opened successfully
    if (yyin == NULL) {
        printf("Error: Could not open file input.txt\n");
        return 1;
    }

    // Print the Table Header
    printf("%-6s %-8s %-12s %-s\n", "Sl.No", "Line No", "Token", "Lexeme");
    printf("---------------------------------------------\n");

    // Start lexical analysis on the opened file
    yylex();

    // Close the file stream after scanning finishes
    fclose(yyin);
    return 0;
}

int yywrap() {
    return 1;
}