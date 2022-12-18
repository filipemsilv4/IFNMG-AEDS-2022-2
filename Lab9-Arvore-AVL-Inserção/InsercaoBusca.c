#include <stdlib.h>

#include "Arvore_AVL.h"

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

// Função auxiliar para calcular a altura máxima entre duas subárvores
int max(int a, int b) { return a > b ? a : b; }

// Função auxiliar para calcular a altura de um nó
int altura(Arvore arv) {
  if (arv == NULL) { return -1; }
  return arv->altura;
}

// Rotações
Arvore rotacao_esquerda(Arvore arv) {
  Arvore aux = arv->dir;
  arv->dir = aux->esq;
  aux->esq = arv;
  arv->altura = max(altura(arv->esq), altura(arv->dir)) + 1;
  aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;
  return aux;
}
Arvore rotacao_direita(Arvore arv) {
  Arvore aux = arv->esq;
  arv->esq = aux->dir;
  aux->dir = arv;
  arv->altura = max(altura(arv->esq), altura(arv->dir)) + 1;
  aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;
  return aux;
}
Arvore rotacao_dupla_esquerda(Arvore arv) {
  arv->dir = rotacao_direita(arv->dir);
  return rotacao_esquerda(arv);
}
Arvore rotacao_dupla_direita(Arvore arv) {
  arv->esq = rotacao_esquerda(arv->esq);
  return rotacao_direita(arv);
}

// Insere na Árvore AVL
bool insere(Arvore* ap_arv, int x) {
  // Se a árvore estiver vazia, insere o valor
  if (*ap_arv == NULL) {
    *ap_arv = (Arvore) malloc(sizeof(No));
    (*ap_arv)->valor = x;
    (*ap_arv)->altura = 0;  // A altura de um nó folha é 0
    (*ap_arv)->esq = NULL;
    (*ap_arv)->dir = NULL;
    return true;
  }

  if (x < (*ap_arv)->valor) {  // Se o valor for menor que o valor do nó atual
    if (insere(&(*ap_arv)->esq, x)) {  // Insere na subárvore esquerda
      if (altura((*ap_arv)->esq) - altura((*ap_arv)->dir) == 2) {  // Se a altura da subárvore esquerda for maior que a da subárvore direita em 2
        if (x < (*ap_arv)->esq->valor) {  // Se o valor for menor que o valor do nó da subárvore esquerda
          *ap_arv = rotacao_direita(*ap_arv);  // Faz uma rotação simples à direita
        } else {
          *ap_arv = rotacao_dupla_direita(*ap_arv); // Faz uma rotação dupla à direita
        }
      }
    } else {  // Se o valor já estiver na árvore, retorna falso
      return false;
    }
  } else if (x > (*ap_arv)->valor) {  // Se o valor for maior que o valor do nó atual
    if (insere(&(*ap_arv)->dir, x)) {  // Insere na subárvore direita
      if (altura((*ap_arv)->dir) - altura((*ap_arv)->esq) == 2) {  // Se a altura da subárvore direita for maior que a da subárvore esquerda em 2
        if (x > (*ap_arv)->dir->valor) {  // Se o valor for maior que o valor do nó da subárvore direita
          *ap_arv = rotacao_esquerda(*ap_arv);  // Faz uma rotação simples à esquerda
        } else {
          *ap_arv = rotacao_dupla_esquerda(*ap_arv);  // Faz uma rotação dupla à esquerda
        }
      }
    } else {
      return false;  // Se o valor já estiver na árvore, retorna falso
    }
  } else {
    return false;  // Se o valor já estiver na árvore, retorna falso
  }
  (*ap_arv)->altura = max(altura((*ap_arv)->esq), altura((*ap_arv)->dir)) + 1;  // Atualiza a altura do nó
  return true;
}

// Busca na Árvore AVL
bool busca(Arvore arv, int x){
  if (arv == NULL) { return false; }
  if (x < arv->valor) { return busca(arv->esq, x); }
  if (x > arv->valor) { return busca(arv->dir, x); }
  return true;
}