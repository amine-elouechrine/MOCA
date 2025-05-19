#include <stdio.h>
int main(){
    int a[5];
    int i;
    a[0]=8;
    for (i=0;i<4;i++) {
        a[i+1]=(1+a[i]*a[i])%7;
    }
    //affichier tableau
    for (i=0;i<5;i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}