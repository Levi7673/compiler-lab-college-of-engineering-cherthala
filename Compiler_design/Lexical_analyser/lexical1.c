#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    FILE *input, *output;
    char ch, str[20];
    int line = 1, token = 0, i, j, flag;

    char keyword[][20] = {"int", "main", "if", "else", "do", "while"};
    int keyCount = sizeof(keyword) / sizeof(keyword[0]);

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    fprintf(output, "Line no.\t Token no.\t\t Token\t\t Lexeme\n\n");

    while ((ch = fgetc(input)) != EOF)
    {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            fprintf(output, "%7d\t\t %7d\t\t Operator\t %7c\n", line, token++, ch);
        }

        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' ||
                 ch == ')' || ch == '?' || ch == '@' || ch == '!' || ch == '%')
        {
            fprintf(output, "%7d\t\t %7d\t\t Special symbol\t %7c\n", line, token++, ch);
        }

        else if (isdigit(ch))
        {
            fprintf(output, "%7d\t\t %7d\t\t Literal\t\t %7c\n", line, token++, ch);
        }

        else if (isalpha(ch))
        {
            i = 0;
            str[i++] = ch;

            while ((ch = fgetc(input)) != EOF && isalnum(ch))
            {
                str[i++] = ch;
            }

            str[i] = '\0';

            flag = 0;
            for (j = 0; j < keyCount; j++)
            {
                if (strcmp(str, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag)
                fprintf(output, "%7d\t\t %7d\t\t Keyword\t %7s\n", line, token++, str);
            else
                fprintf(output, "%7d\t\t %7d\t\t Identifier\t %7s\n", line, token++, str);
        }

        else if (ch == '\n')
        {
            line++;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}