// E → E + T
// E → T
// T → T * F
// T → F
// F → ( E )
// F → i

#include <stdio.h>

char stack[100] , *remaininginput;
int top = -1 ;

void push(char c){
    stack[++top] = c;
    stack[top+1] = '\0';
}

int reduce(){
// F → i
if(top >=0 && stack[top] == 'i'){
    stack[top] = 'F';

    stack[top+1] ='\0';
    printf("%s\t\t%s\t\tREDUCE F → i\n",stack,*remaininginput ? remaininginput : "$");
    return 1;
}
// E → E + T
if(top >=2 && 
    stack[top-2] == 'E' &&
    stack[top-1] == '+' &&
    stack[top] == 'T'){
        top -= 2;
        stack[top] = 'E';

        stack[top+1] ='\0';
        printf("%s\t\t%s\t\tREDUCE E → E + T\n",stack,*remaininginput ? remaininginput : "$");
        return 1;
}
// T → T * F
if(top >=2 && 
    stack[top-2] == 'T' &&
    stack[top-1] == '*' &&
    stack[top] == 'F'){
        top -= 2;
        stack[top] = 'T';

        stack[top+1] ='\0';
        printf("%s\t\t%s\t\tREDUCE T → T * F\n",stack,*remaininginput ? remaininginput : "$");
        return 1;
}
// T → F
if(top >=0 && stack[top] == 'F'){
    stack[top] = 'T';
    
    stack[top+1] ='\0';
    printf("%s\t\t%s\t\tREDUCE T → F\n",stack,*remaininginput ? remaininginput : "$");
    return 1;
}
// F → ( E )
if(top >=2 && 
    stack[top-2] == '(' &&
    stack[top-1] == 'E' &&
    stack[top] == ')'){
        top -= 2;
        stack[top] = 'F';
        
        stack[top+1] ='\0';
        printf("%s\t\t%s\t\tREDUCE F → ( E )\n",stack,*remaininginput ? remaininginput : "$");
        return 1;
    }
    // E → T
    if(top >=0 && stack[top] == 'T' && *remaininginput!='*'){
        stack[top] = 'E';
    
        stack[top+1] ='\0';
        printf("%s\t\t%s\t\tREDUCE E → T\n",stack,*remaininginput ? remaininginput : "$");
        return 1;
    }
return 0;
}
int main(){
    char s[100] ;
    int i =0 ;
    
    printf("Enter the expression :");
    scanf("%s",s);
    
    printf("STACK\t\tINPUT\t\tOPERATION\n");
    while(s[i] != '\0'){
        push(s[i]);
        remaininginput = s + i + 1;
        printf("%s\t\t%s\t\tSHIFT %c\n",stack,*remaininginput ? remaininginput : "$",s[i]);
        i++;

        while(reduce());
    }

    if(stack[0] == 'E' && top == 0){
        printf("%s\t\t%s\t\t%s\n",stack,"$","ACCEPT");
        printf("ACCEPTED");
    }else{
        printf("%s\t\t%s\t\t%s\n",stack,"$","REJECT");
        printf("REJECTED");
    }
    return 0;
}