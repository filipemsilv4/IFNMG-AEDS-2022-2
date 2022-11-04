#include "polinomio.h"
#include <stdlib.h>

/* Inicializa um polinômio vazio. */
void inicializa_polinomio(Polinomio * ap_pol){
    *ap_pol = calloc(1, sizeof(No));
    (*ap_pol)->antec = *ap_pol;
    (*ap_pol)->prox = *ap_pol;
}

/* Insere um no no fim da lista*/
void insere_fim(Polinomio pol, int grau, int coef){
    No* novono = malloc(sizeof(No));

    novono->antec = pol->antec;
    novono->prox = pol;

    novono->valor.coef = coef;
    novono->valor.grau = grau;

    pol->antec->prox = novono;
    pol->antec = novono;
}

/* Define que o coeficiente de grau grau do polinomio pol eh igual a coef. Deve manter os 
 * coeficientes ordenados por grau. */
void define_coeficiente(Polinomio pol, int grau, int coef){

    if (pol->prox == pol){
        insere_fim(pol, grau, coef);
        return;
    }

    for(No *percorreLista = pol->prox; percorreLista != pol; percorreLista = percorreLista->prox){
        if (percorreLista->valor.grau > grau){
            No *novono = malloc(sizeof(No));
            novono->valor.grau = grau;
            novono->valor.coef = coef;

            novono->antec = percorreLista->antec;
            novono->prox = percorreLista;

            percorreLista->antec->prox = novono;
            percorreLista->antec = novono;

            return;
        } else {
            insere_fim(pol, grau, coef);
            return;
        }
    }
}

/* Zera o polinomio, tornando-o um polinomio inicializado, mas igual a zero. Desaloca a memória liberada. */
void zera(Polinomio pol){
    // Nao entendi
    return;
}

// Operações de soma e subtração
void opera(Polinomio res, Polinomio a, Polinomio b, char op){
    No *percorreA = a->prox;
    No *percorreB = b->prox;
    int resOperacao = 0;

    while(percorreA != a && percorreB != b){
        if (op == '+'){ // Caso seja uma soma
            resOperacao = percorreA->valor.coef + percorreB->valor.coef;

        } else if (op == '-'){ // Caso seja subtracao
            resOperacao = percorreA->valor.coef - percorreB->valor.coef;
        }

        if (resOperacao != 0 && percorreA->valor.grau == percorreB->valor.grau){
            insere_fim(res, percorreA->valor.grau, resOperacao);
            percorreA = percorreA->prox;
            percorreB = percorreB->prox;
        }
        else if (percorreA->valor.grau > percorreB->valor.grau){
            insere_fim(res, percorreB->valor.grau, percorreB->valor.coef);
            percorreB = percorreB->prox;
        }
        else if (percorreA->valor.grau < percorreB->valor.grau){
            insere_fim(res, percorreA->valor.grau, percorreA->valor.coef);
            percorreA = percorreA->prox;
        } else {
            percorreA = percorreA->prox;
            percorreB = percorreB->prox;
        }
    }

    while (percorreA != a){
        insere_fim(res, percorreA->valor.grau, percorreA->valor.coef);
        percorreA = percorreA->prox;
    }
    while (percorreB != b){
        insere_fim(res, percorreB->valor.grau, percorreB->valor.coef);
        percorreB = percorreB->prox;
    }

    return;
}

/* Computa a soma dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void soma(Polinomio res, Polinomio a, Polinomio b){
    opera(res, a, b, '+');
}

/* Computa a subtracao dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void subtrai(Polinomio res, Polinomio a, Polinomio b){
    opera(res, a, b, '-');
}

/* /\* Computa a multiplicacao dos polinomios a e b colocando o resultado em res.  */
/*  * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. *\/ */
/* void multiplica(Polinomio res, Polinomio a, Polinomio b); */

/* Imprime o polinomio pol no formato do exemplo abaixo
 * [(0,2),(3,-2),(10,5)]
 * onde este polinomio tem 3 coeficientes, o de grau 0 com valor 2, o de grau 3 com valor -2 e o de
 * grau 10 com valor 5. 
 */
void imprime(Polinomio pol){
    No *percorrePol = pol->prox;
    printf("[");

    if (percorrePol != pol){
        printf("(%i,%i)", percorrePol->valor.grau, percorrePol->valor.coef);
    }
    for (percorrePol = pol->prox->prox; percorrePol != pol; percorrePol = percorrePol->prox){
        printf(",(%i,%i)", percorrePol->valor.grau, percorrePol->valor.coef);
    }
    printf("]\n");
    return;
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_polinomio(Polinomio *ap_pol){
    (*ap_pol)->antec->prox = NULL; // Quebra a ligação entre o ultimo elemento e o no cabeca

    while (*ap_pol != NULL){
        No *percorreLista = (*ap_pol)->prox;
        free(*ap_pol);
        *ap_pol = percorreLista;
    }
}