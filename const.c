#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char var[100] , val[100][100] , temp[100] , right[100];
    int n , i , j , k , pos ,len;

    printf("Enter the number of statements:");
    scanf("%d",&n);
    printf("Enter the statements:\n");
    for(i=0;i<n;i++){
        scanf(" %c = %s",&var[i],right);
        strcpy(temp , "");
        for(k=0 ; right[k]!='\0';k++){
            pos = -1;
            if(isalpha(right[k])){
                for(j=i-1;j>=0;j--){
                    if(var[j] == right[k]){
                        pos = j;
                        break;
                    }
                }
            }
                if (pos!=-1){
                    strcat(temp,val[pos]);
                }else{
                    len = strlen(temp);
                    temp[len] = right[k];
                    temp[len+1] = '\0';
                }
        }
        strcpy(val[i],temp);
    }
    printf("After constant propagation:\n");
    for(i=0;i<n;i++){
        printf("%c = %s\n",var[i] , val[i]);
    }
    return 0;
}