#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

No * cab_linha(Matriz * ap_mat, int nlin){
  No* atual_linha = ap_mat->cabeca->abaixo;
  while(atual_linha!= ap_mat -> cabeca && atual_linha->linha < nlin){ // CORREÇÃO
    atual_linha = atual_linha -> abaixo;
  }
  if(atual_linha->linha == nlin)   return atual_linha;
  else{
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no -> coluna = -1;
    novo_no -> linha = nlin;
    novo_no -> abaixo = atual_linha;
    novo_no -> acima = atual_linha -> acima;
    novo_no -> direita = novo_no;
    novo_no -> esquerda  = novo_no;
    atual_linha -> acima -> abaixo = novo_no;
    atual_linha -> acima = novo_no;
    atual_linha = novo_no;
  }
  return atual_linha;
}

No * cab_coluna(Matriz * ap_mat, int ncol){
  No* atual_coluna = ap_mat ->cabeca -> direita;
  while(atual_coluna!= ap_mat -> cabeca && atual_coluna->coluna < ncol){  // CORREÇÃO
    atual_coluna = atual_coluna -> direita;
  }
  if(atual_coluna->coluna == ncol)   return atual_coluna;
  else{
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no -> linha = -1;
    novo_no -> coluna = ncol;
    novo_no -> direita= atual_coluna;
    novo_no -> esquerda = atual_coluna -> esquerda;
    novo_no -> abaixo = novo_no;
    novo_no -> acima  = novo_no;
    atual_coluna -> esquerda-> direita= novo_no;
    atual_coluna -> esquerda = novo_no;
    atual_coluna = novo_no;
  }
  return atual_coluna;
}

/* Inicializa uma matriz de zeros com nlin linhas e ncol colunas. 
 * Supõe que não há nada a ser desalocado. */
void inicializa_matriz(Matriz * ap_mat, int nlin, int ncol){

  (ap_mat->cabeca) = ( No*) malloc(sizeof(No));

  (ap_mat -> cabeca) -> direita = ap_mat-> cabeca;
  (ap_mat -> cabeca) -> esquerda = ap_mat-> cabeca;
  (ap_mat -> cabeca) -> acima = ap_mat-> cabeca;
  (ap_mat -> cabeca) -> abaixo = ap_mat-> cabeca;

  ap_mat -> n_linhas = nlin;

  ap_mat -> n_colunas = ncol;
}

No* insere_novo(int nlin, int ncol, int val){
  No* novo_no =(No*) malloc(sizeof(No));

  novo_no -> valor = val;
  novo_no -> coluna = ncol;
  novo_no -> linha = nlin;

  return novo_no;
}

/* Define que o elemento na linha lin e coluna col valerá val. 
   O parâmetro lin está em [0,n_linhas-1] e ncol em [0,n_colunas-1].*/
void define_elemento(Matriz mat, int lin, int col, int val){
//No* cab_col = cab_coluna(&mat,col);
  No* cab_lin = cab_linha(&mat,lin);
//No* atual_coluna = cab_col -> abaixo;
  No* atual_linha = cab_lin-> direita;
  if(cab_lin == atual_linha){
    No* novo_no = insere_novo(lin,col,val);
    novo_no -> esquerda = cab_lin;
    novo_no -> direita = cab_lin -> direita;
    cab_lin -> direita -> esquerda = novo_no;
    cab_lin -> direita = novo_no;
    return;
  }

  while(atual_linha->coluna < col && atual_linha != cab_lin){  // CORREÇÃO
    atual_linha = atual_linha ->  direita;
  }
  if((atual_linha -> coluna) == col){
    atual_linha -> valor = val;
  }
  else{
    No* novo_no = insere_novo(lin,col,val);
    novo_no -> direita = atual_linha;
    novo_no -> esquerda = atual_linha -> esquerda;

    atual_linha -> esquerda -> direita = novo_no;
    atual_linha -> esquerda = novo_no;
  }

}

/* Computa a soma das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
 bool soma(Matriz *ap_res, Matriz a, Matriz b){
 return true;
 }

/* Computa a subtracao das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
 bool subtrai(Matriz *ap_res, Matriz a, Matriz b){
  return true;
 }

/* Computa a multiplicacao das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
 bool multiplica(Matriz *ap_res, Matriz a, Matriz b){
  return true;
 }

/* Imprime a matriz mat no formato do exemplo abaixo
 * (nlin=100,ncol=200,[0,3]=5,[0,8]=10,[2,9]=50,[5,3]=10,[5,15]=20,[99,0]=33)
 * onde esta matriz tem 100 linhas e 200 colunas, e seus únicos
 * elementos não zero são os seguintes:
 * - da linha 0 coluna 3, com valor 5
 * - da linha 0 coluna 8, com valor 10
 * - da linha 2 coluna 9, com valor 50
 * - da linha 5 coluna 3, com valor 10
 * - da linha 5 coluna 15, com valor 20
 * - da linha 99 coluna 0, com valor 33.
 * Os elementos devem ser impressos em ordem crescente de linhas e dois 
 * elementos da mesma linha em ordem crescente de coluna. 
 */
void imprime(Matriz mat){

  printf("(");
  printf("nlin=%d,ncol=%d",mat.n_linhas,mat.n_colunas);
  No* cab_linha = (mat.cabeca)-> abaixo;

  while(cab_linha != mat.cabeca){
    No* atual = cab_linha -> direita;
    while(atual != cab_linha){
      printf(",");
      printf("[%d,%d]=%d",atual->linha,atual->coluna,atual->valor);

      atual = atual -> direita;
    }
    cab_linha = cab_linha -> abaixo;
  }
  printf(")\n");
}

/* Desaloca toda a memória alocada da matriz. */
void desaloca_matriz(Matriz *ap_mat){
  // desaloca linhas 
  No *atual = (ap_mat -> cabeca) ->abaixo;
  while(atual != ap_mat->cabeca){
    No* at_lin = atual-> esquerda;
    while (at_lin !=atual){
      No* no_remov = at_lin;
      at_lin = at_lin -> esquerda;
      free(no_remov);
    }
    No* remov_cab = atual;
    atual = atual -> abaixo;
    free(remov_cab);
  }
  //Desaloca Colunas
  atual = (ap_mat -> cabeca) -> esquerda;
  while(atual != ap_mat->cabeca){
    No* remov_cab = atual;
    atual = atual -> esquerda;
    free(remov_cab);
  }
  free(ap_mat ->cabeca);
}

/* Desaloca a memória atualmente utilizada por *mat. Em seguida, 
   inicializa *mat para ser uma matriz de zeros com nlin linhas e
   ncol colunas.  */
void zera(Matriz *ap_mat, int nlin, int ncol){

  desaloca_matriz(ap_mat);
  inicializa_matriz(ap_mat, nlin, ncol);

}

/* Abaixo uma gambiarra necessaria para o run.codes */
//#include "lab04.c"
