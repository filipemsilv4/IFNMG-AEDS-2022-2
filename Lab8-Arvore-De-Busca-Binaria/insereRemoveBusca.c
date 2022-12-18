#include <stdlib.h>
#include "Arvore.h"

No* alocaNo(int x){
    No *novono = malloc(sizeof(No));
    novono->valor = x;
    novono->esq   = NULL;
    novono->dir   = NULL;
    
    return novono;
}

/** Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x){
    if (*ap_arv == NULL){
       *ap_arv = alocaNo(x);
        return true;
    }
    if (x < (*ap_arv)->valor)     { return insere(&((*ap_arv)->esq), x); }
    else if (x > (*ap_arv)->valor){ return insere(&((*ap_arv)->dir), x); }
    else                          { return false; }
}

/** Remove valor x da árvore de busca binária. Em caso de nó com dois filhos, deve-se trocar de posição com o antecessor do nó removido e então removê-lo.  */
bool remove_(Arvore* ap_arv, int x){
    // Se a árvore estiver vazia, retorna falso
    if (*ap_arv == NULL){ return false; }
    // Se o valor for menor que o valor do nó atual, procura na subárvore esquerda
    if (x < (*ap_arv)->valor)     { return remove_(&((*ap_arv)->esq), x); }

    // Se o valor for maior que o valor do nó atual, procura na subárvore direita
    else if (x > (*ap_arv)->valor){ return remove_(&((*ap_arv)->dir), x); }

    // Se o valor for igual ao valor do nó atual, remove o nó
    else{
        // Se o nó for uma folha, remove-o
        if ((*ap_arv)->esq == NULL && (*ap_arv)->dir == NULL){
            free(*ap_arv);
            *ap_arv = NULL;
            return true;
        }
        // Se o nó tiver apenas o filho direito, remove-o e substitui pelo filho direito
        else if ((*ap_arv)->esq == NULL){
            No *aux = *ap_arv;
            *ap_arv = (*ap_arv)->dir;
            free(aux);
            return true;
        }
        // Se o nó tiver apenas o filho esquerdo, remove-o e substitui pelo filho esquerdo
        else if ((*ap_arv)->dir == NULL){
            No *aux = *ap_arv;
            *ap_arv = (*ap_arv)->esq;
            free(aux);
            return true;
        }
        // Se o nó tiver dois filhos, remove-o e substitui pelo antecessor
        else{
            No *aux = (*ap_arv)->esq;  // aux aponta para o filho esquerdo do nó atual
            
            // Encontra o antecessor do nó atual
            while (aux->dir != NULL){ aux = aux->dir; }

            // Troca o valor do nó atual com o valor do antecessor
            (*ap_arv)->valor = aux->valor;
            return remove_(&((*ap_arv)->esq), aux->valor);
        }
    }
}

/** Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x){
    if (arv == NULL){ return false; }
    if (x < arv->valor)     { return busca(arv->esq, x); }
    else if (x > arv->valor){ return busca(arv->dir, x); }
    return true;
}






void imprime_rec(Arvore arv) {
  if (arv == NULL) {
    printf(".");
    return;
  }
  printf("[%d:e=", arv->valor);
  imprime_rec(arv->esq);
  printf(",d=");
  imprime_rec(arv->dir);
  printf("]");
}

void imprime(Arvore arv) {
  imprime_rec(arv);
  printf("\n");
}
