#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
char s[100] ;
int i = 0;
/*  E  → T E'
    E' → + T E' | - T E' | ε
    T  → F T'
    T' → * F T' | / F T' | ε
    F  → - F | ( E ) | id | num*/
void error(){
    printf("Invalid Expresssion!\n");
    exit (0);
}
void E() ; void EPRIME() ; void T() ; void TPRIME() ; void F();
//E  → T E'
void E(){ T() ; EPRIME() ;}
//    E' → + T E' | - T E' | ε
void EPRIME(){
    if (s[i] == '+'){
        i++;
        T();
        EPRIME();
    }
    else if(s[i] == '-'){
        i++;
        T();
        EPRIME();
    }else return ;
}
//    T  → F T'
void T(){
    F();
    TPRIME();
}

//    T' → * F T' | / F T' | ε
void TPRIME(){
    if(s[i] == '*'){
        i++;
        F();
        TPRIME();
    }
    else if(s[i]=='/'){
        i++;
        F();
        TPRIME();
    }else return;
}
//    F  → - F | ( E ) | id | num
void F(){
    if(s[i]=='-'){
        i++;
        F();
    }else if(s[i] == '('){
        i++;
        E();
        if(s[i] == ')'){
            i++;
        }else error();
    }else if (isalpha(s[i])){
        while(isalnum(s[i])) i++;
    }else if (isdigit(s[i])){
        while(isdigit(s[i])) i++;
    }
    else error();
}
int main(){
printf("Enter the expression :");
scanf("%s",s);
E();
if (s[i] == '\0') printf("Accepted");
else printf("Rejected");
}