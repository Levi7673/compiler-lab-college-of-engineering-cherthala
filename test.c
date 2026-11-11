
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("input.c", "r");

    int ch, next;
    char str[100], keyword[][10] = {
        "int","char","float","long","if","else",
        "while","for","return","void","break",
        "continue","switch","case","do"
    };

    int keycount = 15, line = 1, token = 0;
    int i, j, flag, quote;

    if(fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    printf("Line\tToken\tType\t\t\tLexeme\n");

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
        {
            line++;
            continue;
        }

        if(isspace(ch))
            continue;

        // Keyword, Identifier and Function Name
        if(isalpha(ch) || ch == '_')
        {
            i = 0;
            str[i++] = ch;

            while(isalnum(ch = fgetc(fp)) || ch == '_')
                str[i++] = ch;

            str[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            flag = 0;

            for(j = 0; j < keycount; j++)
            {
                if(strcmp(str, keyword[j]) == 0)
                    flag = 1;
            }

            if(flag)
                printf("%d\t%d\tKeyword\t\t\t%s\n", line, ++token, str);

            else if(ch == '(')
                printf("%d\t%d\tFunction Name\t\t%s\n", line, ++token, str);

            else
                printf("%d\t%d\tIdentifier\t\t%s\n", line, ++token, str);

            continue;
        }

        // Numeric Literal
        if(isdigit(ch))
        {
            i = 0;
            str[i++] = ch;

            while(isdigit(ch = fgetc(fp)) || ch == '.')
                str[i++] = ch;

            str[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            printf("%d\t%d\tNumeric Literal\t\t%s\n", line, ++token, str);
            continue;
        }

        // String and Character Literal
        if(ch == '"' || ch == '\'')
        {
            quote = ch;
            i = 0;
            str[i++] = ch;

            while((ch = fgetc(fp)) != quote && ch != EOF)
            {
                str[i++] = ch;

                if(ch == '\\')
                {
                    ch = fgetc(fp);

                    if(ch == EOF)
                        break;

                    str[i++] = ch;
                }

                if(ch == '\n')
                    line++;
            }

            if(ch == quote)
                str[i++] = ch;

            str[i] = '\0';

            if(quote == '"')
                printf("%d\t%d\tString Literal\t\t%s\n", line, ++token, str);
            else
                printf("%d\t%d\tCharacter Literal\t%s\n", line, ++token, str);

            continue;
        }

        // Single-line Comment and Division Operator
        if(ch == '/')
        {
            next = fgetc(fp);

            if(next == '/')
            {
                while((ch = fgetc(fp)) != '\n' && ch != EOF);

                if(ch == '\n')
                    line++;

                continue;
            }
            else
            {
                if(next == '=')
                    printf("%d\t%d\tOperator\t\t\t/=\n", line, ++token);
                else
                {
                    printf("%d\t%d\tOperator\t\t\t/\n", line, ++token);

                    if(next != EOF)
                        ungetc(next, fp);
                }

                continue;
            }
        }

        // Operators
        if(strchr("+-*=<>!&|%", ch))
        {
            int op = ch;
            next = fgetc(fp);

            if((op == '=' && next == '=') ||
               (op == '!' && next == '=') ||
               (op == '<' && (next == '=' || next == '<')) ||
               (op == '>' && (next == '=' || next == '>')) ||
               (op == '+' && (next == '+' || next == '=')) ||
               (op == '-' && (next == '-' || next == '=')) ||
               (op == '*' && next == '=') ||
               (op == '%' && next == '=') ||
               (op == '&' && (next == '&' || next == '=')) ||
               (op == '|' && (next == '|' || next == '=')))
            {
                printf("%d\t%d\tOperator\t\t\t%c%c\n",
                       line, ++token, op, next);
            }
            else
            {
                printf("%d\t%d\tOperator\t\t\t%c\n",
                       line, ++token, op);

                if(next != EOF)
                    ungetc(next, fp);
            }

            continue;
        }

        // Special Symbols
        if(strchr("(){}[];,#@,.", ch))
        {
            printf("%d\t%d\tSpecial Symbol\t\t%c\n",
                   line, ++token, ch);
            continue;
        }

        // Unknown Characters
        printf("%d\t%d\tUnknown\t\t\t%c\n", line, ++token, ch);
    }

    fclose(fp);
    return 0;
}
