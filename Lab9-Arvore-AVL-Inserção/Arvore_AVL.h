#ifndef __ARVORE_H__
#define __ARVORE_H__

typedef enum{false,true} bool;

typedef struct No_aux {
  int valor;
  int altura;
  struct No_aux * esq;
  struct No_aux * dir;
} No;
typedef No* Arvore;

/** Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x);
/** Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x);
/** Imprime a árvore de busca binária */
void imprime(Arvore arv);

/* Gambiarra para o run.codes funcionar*/
#include "lab09.c"

#endif
