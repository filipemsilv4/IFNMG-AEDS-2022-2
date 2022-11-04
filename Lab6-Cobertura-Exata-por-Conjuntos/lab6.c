#include <stdio.h>
#include <stdlib.h>

#define ULTIMO_BIT (sizeof(int) * 8 - 1)
#define INSOLUVEL (1 << ULTIMO_BIT)

// Estruturas
typedef struct subcj{
    int qttElem;
    int elem;
} subconjunto;

// Globais
subconjunto *subconjs;
int qttDeSubconj;
int n, bits_n;

// Prototipo das funcoes
int fazCoisasFantasticas(int subconjsDentro, int posicao, int listaNegra);
void imprimeConjuntos(int bitmaskDeConjuntos);


int main(void){
    // Pegar o tamanho do conjunto n... 
    scanf("%i", &n);
    bits_n = 0;
    for (int bit_pos = 0; bit_pos < n; ++bit_pos){ // ...e armazenar na máscara de bits bits_n
        bits_n = bits_n | (1 << bit_pos);
    }

    // Pegar a quantidade de subconjuntos W... 
    scanf("%i", &qttDeSubconj);
    subconjs = calloc(qttDeSubconj, sizeof(subconjunto)); // ...e criar um vetor de subconjuntos, ...
    for (int bit_pos = 0; bit_pos < qttDeSubconj; ++bit_pos){ // ... populá-lo com 0s
        subconjs[bit_pos].elem = 0;
    }

    // Preencher os elementos de cada subconjunto
    int valor;
    for (int sub = 0; sub < qttDeSubconj; ++sub){  // Para cada subconjunto:
        scanf("%i", &subconjs[sub].qttElem);  // Ler quantos elementos terá
        for (int elems = 0; elems < subconjs[sub].qttElem; ++elems){  // Preencher os valores
            scanf("%i", &valor);
            subconjs[sub].elem = subconjs[sub].elem | (1 << valor);
        }
    }

    // Calcula a solucão
    int solucao = fazCoisasFantasticas(0, 0, 0);
    if   (solucao == INSOLUVEL){ printf("Insoluvel\n"); }
    else { imprimeConjuntos(solucao); }
}

// Retorna a quantidade de numeros 1 em uma máscara de bits
int quantosUns(int bitmaskDeConjuntos){
    int qtt = 0;
    for (int i = 0; i < qttDeSubconj; ++i){
        if ((bitmaskDeConjuntos & (1 << i)) != 0){ ++qtt; }
    }
    return qtt;
}

/* Imprime apenas os conjuntos presentes em uma máscara de bits
   Ex.: 010100010 -> subconjs[1], subconjs[3], subconjs[7] */
void imprimeConjuntos(int bitmaskDeConjuntos){
    printf("%i\n", quantosUns(bitmaskDeConjuntos)); // Imprime a quantidade de conjuntos na resposta final

    for (int i = 0; i < qttDeSubconj; ++i){         // Conta de 0 até a quantidade de subconjuntos
        if ((bitmaskDeConjuntos & (1 << i)) != 0){  // Se o subconjs[i] estiver marcado na bitmask:
            printf("%i", subconjs[i].qttElem);      // Imprime a quantidade de elementos do subconjunto
            for (int j = 0; j <= ULTIMO_BIT; ++j){  // Itera sobre cada bit da mascara de bits
                if ((subconjs[i].elem & (1 << j)) != 0){ printf(" %i", j); } // Itera sobre a mascara de bits DO subconjunto subconjs[i] em busca dos elementos contidos no mesmo, imprime-os
            }
            printf("\n");
        }
    }
}

/*Funcao responsavel por gerar árvores de possibilidades de combinacões dos
  conjuntos. Retorna INSOLÚVEL caso nenhuma seja capaz de "abracar" todo o
  conjunto n (0...n-1) (Marcado com [A] no codigo).

  ILUSTRACÃO 1:

  CONJUNTO 0              [0]                 [1]
                         /   \               /   \
  CONJUNTO 1          [0]     [1]         [0]     [1]
                      / \     / \         / \     / \
  CONJUNTO 2        [0] [1] [0] [1]     [0] [1] [0] [1]
  POSSIBILIDADES:   000,001,010,011,    100,101,110,111

  Obs.: A arvore não continua crescendo em uma direcão que já se mostrou
        inviável, por exemplo, se o conjunto {1,2} foi incluso em uma das
        possibilidades, o {2,3} nao poderá ser, pois possuem intersecão.
        (Marcado com [B] no codigo)*/
int fazCoisasFantasticas(int subconjsDentro, int posicao, int listaNegra){
    // Caso base, será atingido ao fim da recursão
    if (posicao >= qttDeSubconj){
        if (listaNegra == bits_n){ return subconjsDentro; } // [A]
        return INSOLUVEL;
    }

    int hold_subconjsDentro0 = INSOLUVEL;
    int hold_subconjsDentro1 = INSOLUVEL;

    // Subconjunto "posicao" nao entra. Esse caso é um [0] na ilustracão 1
    hold_subconjsDentro0 = fazCoisasFantasticas(subconjsDentro, posicao + 1, listaNegra); // Chamada recursiva apenas atualizando a posicão na mascara de bits (proxima linha na ilustracão 1, CONJUNTO 0 -> CONJUNTO 1, por exemplo).

    /*Subconjunto "posicao" entra (Esse caso é um [1] na ilustracão 1), mas
    apenas se seus elementos não fizerem intersecão com os que já estão na
    listaNegra*/
    subconjsDentro = subconjsDentro | (1 << posicao);  // Shifta 1 para a posicao "posicao" na mascara de bits
    if ((listaNegra & subconjs[posicao].elem) == 0){   // [B] - Verifica intersecão com listaNegra
        listaNegra           = listaNegra | subconjs[posicao].elem;  // Atualiza listaNegra com os elementos no novo conjunto que está entrando
        hold_subconjsDentro1 = fazCoisasFantasticas(subconjsDentro, posicao + 1, listaNegra); // Chamada recursiva atualizando a posicão na mascara de bits. Os elementos do subconjunto já foram inclídos na máscara de bits.
    }

    if   (hold_subconjsDentro0 != INSOLUVEL){ return hold_subconjsDentro0; }
    else { return hold_subconjsDentro1; }
}

/*
          Paulo Filipe M.      
    filipemsilva@outlook.com.br
*/