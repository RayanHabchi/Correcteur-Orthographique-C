#include "Levenshtein.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int L/*evenshtein*/(char * un, char * deux){
    int n = strlen(un), m = strlen(deux);
    int D[n+1][m+1], Cout[n][m];
    int i,j;

    for(i=0; i<=n; i++){/*ligne 0*/
        D[i][0] = i;
    }
    for(j=0; j<=m; j++){/*colonne 0*/
        D[0][j] = j;
    }

    for(j=0; j<m; j++){/*Matrice cout*/
        for(i=0; i<n; i++){
            if(un[i]==deux[j]){
                Cout[i][j] = 0;
            }
            else{
                Cout[i][j] = 1;
            }
        }
    }

    for(j=1; j<=m; j++){/*on remplis le reste de D*/
        for(i=1; i<=n; i++){
            D[i][j] = minimum((D[i-1][j] + 1), (D[i][j-1] + 1), (D[i-1][j-1] + Cout[i-1][j-1]));
        }
    }

    return D[n][m];
}

int minimum(int a, int b, int c){
    if( (a<=b)&&(a<=c) ){
        return a;
    }
    if( (b<=a)&&(b<=c) ){
        return b;
    }
    if( (c<=b)&&(c<=a) ){
        return c;
    }
    return 0;
}