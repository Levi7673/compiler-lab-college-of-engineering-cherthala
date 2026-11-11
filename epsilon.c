#include<stdio.h>

int main(){
    int k , i , j , n , eps[20][20] = {0} ;
    printf("Enter the number of states :");
    scanf("%d",&n);
    printf("Enter epsilon transition matrix:");
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<n ; j++)
            scanf("%d",&eps[i][j]);

    for(j=0 ; j<n ; j++) eps[j][j] = 1;

    //kij
    for(k=0 ; k<n ; k++)
        for(i=0 ; i<n ; i++)
            for(j=0 ; j<n ; j++)
                if(eps[i][k] && eps[k][j]) eps[i][j] = 1 ;
    printf("Epsilon closure : \n");   
    for(i=0 ; i<n ; i++){
        printf("Epsion closure of q%d -> {",i);
        for(j=0;j<n;j++)
            if(eps[i][j])
                printf("q%d ",j);
            printf("}\n");
    }
    return 0;
}