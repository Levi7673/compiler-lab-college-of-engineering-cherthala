#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX 100

int main(){
    char var[MAX] , val[MAX][100] , right[MAX] , temp[MAX];
    int i , j , k , pos , len , n;

    printf("Enter the number of statement:");
    scanf("%d",&n);
    printf("Enter the expression :");
    for(i=0 ; i<n ; i++){
        scanf(" %c = %s",&var[i], right);

        strcpy(temp , "");
        for(k=0 ; right[k] != '\0' ; k++){
            pos = -1;

            if(isalpha(right[k])){
                for(j=i-1 ; j>=0 ; j--){
                    if(var[j] == right[k]){
                        pos = j;
                        break;
                    }
                }
            }
            if(pos!=-1){
                strcat(temp , val[pos]);
            }
            else {
                len = strlen(temp);
                temp[len] = right[k];
                temp[len+1] = '\0';
            }
        }
        strcpy(val[i],temp);
    }
      printf("\nAfter Constant Propagation:\n");

    for(i = 0; i < n; i++)
        printf("%c = %s\n", var[i], val[i]);

    return 0;
}