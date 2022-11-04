#include <stdio.h>

void imprime(int val[]){
    int localval[2];
    localval[0] = val[0];
    localval[1] = val[1];
    
    printf("%i\n", localval[0]);
    printf("%i\n", localval[1]);
    localval[0] = 15;
    localval[1] = 25;
}

int main(void){
    int val[2];
    val[0] = 10;
    val[1] = 20;

    imprime(val);

    imprime(val);
}
