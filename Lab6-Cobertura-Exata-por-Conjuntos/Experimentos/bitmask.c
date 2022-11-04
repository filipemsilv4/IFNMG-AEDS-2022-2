#include <stdio.h>

int shift(int bitmask, int shift);
void imprimebit(int bitmask);

int main(void){
    int bitmask;

    // Coloca um 1 em cada posição de bitmask (uma por vez) e imprime
    for (int j = 0; j < (sizeof(int) * 8); ++j){
        bitmask = 0;
        bitmask = shift(bitmask, j);
        imprimebit(bitmask);
    }

    // Verificando valor de uma posicao numa mascara de bits
    int i = 31;
    if((bitmask&(1<<i)) != 0){
        printf("bit %i = 1\n", i);
    }
}

int shift(int bitmask, int shift){
    // Definindo uma posicao numa mascara de bits
    bitmask = bitmask|(1<<shift);
    return bitmask;
}

void imprimebit(int bitmask){
    for (int i = 0; i < (sizeof(int) * 8); ++i){    // Itera entre todas as posições (bits) do int
        if (i > 7 && i % 8 == 0){ printf(" "); }  // Apenas para espaçar a cada 8 bits
        if((bitmask&(1<<i)) != 0){ printf("1"); } // Confere se há um bit 1 na posição i, se houver, imprime 1
        else { printf("0"); }                     // Se não houver, imprime 0
    }
    printf("\n");
}