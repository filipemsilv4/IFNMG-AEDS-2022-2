#include "lista.h"
#include <stdlib.h>

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
    *ap_lista = calloc(1, sizeof(No));
    (*ap_lista)->antec = *ap_lista;
    (*ap_lista)->prox = *ap_lista;
    return;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_fim(Lista ap_lista, TipoDado valor){
    No *novono = malloc(sizeof(No));
    novono->valor = valor;
    novono->antec = ap_lista->antec;
    novono->prox = ap_lista;

    ap_lista->antec->prox = novono;
    ap_lista->antec = novono;
}

/* Insere valor no inicio da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_inicio(Lista ap_lista, TipoDado valor){
    No *novono = malloc(sizeof(No));
    novono->valor = valor;
    novono->antec = ap_lista;
    novono->prox = ap_lista->prox;

    ap_lista->prox->antec = novono;
    ap_lista->prox = novono;
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_fim(Lista ap_lista){
    No *tmp = ap_lista->antec;
    TipoDado val = ap_lista->antec->valor;

    if (ap_lista->antec != ap_lista){
        ap_lista->antec->antec->prox = ap_lista;
        ap_lista->antec = ap_lista->antec->antec;
        free(tmp);
    }

    return val;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_inicio(Lista ap_lista){
    No *tmp = ap_lista->prox;
    TipoDado val = ap_lista->prox->valor;

    if (ap_lista->prox != ap_lista){
        ap_lista->prox->prox->antec = ap_lista;
        ap_lista->prox = ap_lista->prox->prox;
        free(tmp);
    }

    return val;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas. */
int remove_ocorrencias(Lista ap_lista, TipoDado valor){
    int ocorrencias = 0;
    No *percorreLista = ap_lista;
    No *tmp;

    while (percorreLista->prox != ap_lista){
        percorreLista = percorreLista->prox;
        if (percorreLista->valor.grau == valor.grau && percorreLista->valor.coef == valor.coef){
            tmp = percorreLista;
            percorreLista->antec->prox = percorreLista->prox;
            percorreLista->prox->antec = percorreLista->antec;
            ocorrencias++;
            free(tmp);
        }
    }

    return ocorrencias;
}

/* Busca elemento valor na lista. 
   Retorna a posição da primeira ocorrencia de valor na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado. */
int busca(Lista lista, TipoDado valor){
    int posicao = 0;
    for (No *percorreLista = lista->prox; percorreLista != lista; percorreLista = percorreLista->prox){
        if (percorreLista->valor.grau == valor.grau && percorreLista->valor.coef == valor.coef){
            return posicao;
        }
        posicao++;
    }
    return -1;
}

/* Retorna o campo coef do primeiro no que contenha grau igual ao parametro grau, 
   e 0 (zero) caso nao encontre um tal no.  */
int coeficiente_do_grau(Lista lista, int grau){
    for (No *percorreLista = lista->prox; percorreLista != lista; percorreLista = percorreLista->prox){
        if (percorreLista->valor.grau == grau){
            return percorreLista->valor.coef;
        }
    }
    return 0;
}

/* Imprime a lista na saida padrao, no formato:
   [(1,3),(2,3),(4,2),(3,1),(4,17)]
   em uma linha separada. */
void imprime(Lista lista){
    No *percorreLista = lista->prox;
    printf("[");

    if (percorreLista != lista){
        printf("(%i,%i)", percorreLista->valor.grau, percorreLista->valor.coef);
    }
    for (percorreLista = lista->prox->prox; percorreLista != lista; percorreLista = percorreLista->prox){
        printf(",(%i,%i)", percorreLista->valor.grau, percorreLista->valor.coef);
    }
    printf("]\n");
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    (*ap_lista)->antec->prox = NULL; // Quebra a ligação entre o ultimo elemento e o no cabeca

    while (*ap_lista != NULL){
        No *percorreLista = (*ap_lista)->prox;
        free(*ap_lista);
        *ap_lista = percorreLista;
    }
}
