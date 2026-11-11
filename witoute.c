#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define MAX 20

int main(){
    int eps [MAX][MAX] = {0};
    int trans [MAX][MAX] = {0};
    int result [MAX][MAX] = {0} , i , j , k , n , from , final;

    printf("Enter the states : ");
    scanf("%d",&n);
    
    printf("Enter epsilon transition matrix : ");
    for (i=0 ; i<n ; i++)
        for (j=0 ; j<n ; j++)
            scanf("%d",&eps[i][j]);
    printf("Enter input transition matrix : ");
            for (i=0 ; i<n ; i++)
                for (j=0 ; j<n ; j++)
                    scanf("%d",&trans[i][j]);

    printf("Enter final state : ");
    scanf("%d",&final);

    for (i=0 ; i<n ; i++) eps[i][i] = 1;
    //find clousure
    for (k=0 ; k<n ; k++)
        for (i=0 ; i<n ; i++)
            for (j=0 ; j<n ; j++)
                if(eps[i][k] && eps[k][j])
                    eps[i][j] = 1;

    //ijkfrom
    for (i=0 ; i<n ; i++)
        for (j=0 ; j<n ; j++)
            if(eps[i][j])
                for (k=0 ; k<n ; k++)
                    if(trans[j][k])
                        for (from=0 ; from<n ; from++)
                            if(eps[k][from])
                                result[i][from] = 1;
    
    printf("\nNFA without epsilon transitions:\n");
    for(i=0 ; i<n ; i++){
        printf("q%d -> {",i);
        for(j=0 ; j<n ; j++)
            if(result[i][j])
                printf("q%d ",j);
        printf("}\n");
    }

    printf("\nnew Final state:");
    for (i=0 ; i<n ; i++)
        if(eps[i][final])
            printf("q%d ",i);


    return 0 ;
}