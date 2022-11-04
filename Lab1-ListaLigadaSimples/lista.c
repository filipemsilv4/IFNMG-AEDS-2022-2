#include "lista.h"
#include <stdlib.h>

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
    *ap_lista = NULL;
    return;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o inicio da lista. */
void insere_fim(Lista * ap_lista, int valor){
    No *tmp_ap_lista = *ap_lista;

    while (tmp_ap_lista != NULL && tmp_ap_lista->proximo != NULL){
        tmp_ap_lista = tmp_ap_lista->proximo;
    }

    No *novo_item = malloc(sizeof(No));

    novo_item->valor = valor;
    novo_item->proximo = NULL;

    if (tmp_ap_lista != NULL){
        tmp_ap_lista->proximo = novo_item;
    } else {
        *ap_lista = novo_item;
    }
}

/* Insere valor no inicio da lista apontada por ap_lista. */
void insere_inicio(Lista * ap_lista, int valor){
    No *novo_item = malloc(sizeof(No));

    novo_item->valor = valor;
    novo_item->proximo = *ap_lista;
    *ap_lista = novo_item;
    return;
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
int remove_fim(Lista * ap_lista){
    No *ultimo_ap_lista = *ap_lista;
    No *penultimo_ap_lista = *ap_lista;
    int val = ultimo_ap_lista->valor;

    // se não houver nós
    if(*ap_lista == NULL){ return val; }
    // se houver apenas 1 nó - credito:
    if(ultimo_ap_lista->proximo == NULL){
        *ap_lista = NULL;
        return val;}

    while (ultimo_ap_lista != NULL && ultimo_ap_lista->proximo != NULL){
        penultimo_ap_lista = ultimo_ap_lista;
        ultimo_ap_lista = ultimo_ap_lista->proximo;
    }

    val = ultimo_ap_lista->valor;

    free(ultimo_ap_lista);
    penultimo_ap_lista->proximo = NULL;

    return val;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
int remove_inicio(Lista * ap_lista){
    
    if (!ap_lista || *ap_lista == NULL){
        return -1;}
    
    No *old_ap_lista = *ap_lista;
    *ap_lista = (*ap_lista)->proximo;

    int val = old_ap_lista->valor;

    free(old_ap_lista);
    return val;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista.
 * Retorna o numero de ocorrencias removidas.
 */
int remove_ocorrencias(Lista *ap_lista, int valor){
    if (!ap_lista){
        return 0;}
    int qtt_ocorrencias = 0;
    
    while (*ap_lista && (*ap_lista)->valor == valor){
        qtt_ocorrencias++;
        *ap_lista = (*ap_lista)->proximo;}
    
    No *atual = *ap_lista, *anterior = NULL;

    while (atual){
        if (atual->valor == valor){
            qtt_ocorrencias++;
            anterior->proximo = atual->proximo;
        } else {
            anterior = atual;
        }
        atual = atual->proximo;
    }
    return qtt_ocorrencias;
}

/* Busca elemento valor na lista.
   Retorna a posição na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado.
*/
int busca(Lista lista, int valor){
    int pos = 0;
    for (No *atual = lista; atual != NULL; atual = atual->proximo){
        if (atual->valor == valor){
            return pos;
        }
        pos++;
    }
    return -1;
}

/* Imprime a lista na saida padrao, no formato:
   (1,3,2,3,4,2,3,1,4)
   em uma linha separada.
 */
void imprime(Lista lista){
    No *tmp = lista;

    if (tmp == NULL){
        printf("()\n");
        return;}

    printf("(%i", tmp->valor);
    
    for (tmp = lista->proximo; tmp != NULL; tmp = tmp->proximo){
        printf(",%i", tmp->valor);}
    printf(")\n");
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    while(*ap_lista){
        No *tmp = (*ap_lista)->proximo;
        free(*ap_lista);
        *ap_lista = tmp;
    }
}