#include<stdio.h>
#include<string.h>
#include "matriz.h"

int main() {
  int linha, coluna, valor, num_elem, n_linha, n_coluna;
  char comando[300];
  char matriz[123];
  char matA[123];
  char matB[123];
  char matC[123];
  Matriz M[30];
  char c;
  int i;
  for (c = 'A'; c <= 'Z'; c++) {
    inicializa_matriz(&(M[c-'A']), 0, 0);
  }
  
  while(scanf(" %s", comando) == 1) {
    if (strcmp(comando, "define_elemento") == 0) {
      if(scanf(" %s [ %d ] [ %d ] = %d", matriz, &linha, &coluna, &valor) != 4) return 1;
      define_elemento(M[matriz[0]-'A'], linha, coluna, valor);
      printf("Definido %c[%d][%d] = %d .\n", matriz[0], linha, coluna, valor);
      
    }else if (strcmp(comando, "le_matriz") == 0) {
      if(scanf(" %s %d %d %d", matriz, &n_linha, &n_coluna, &num_elem) != 4) return 1;
      zera(&M[matriz[0]-'A'], n_linha, n_coluna);
      printf("Inicializando matriz %c[n_linhas=%d][n_colunas=%d].\n", matriz[0], n_linha, n_coluna);
      for (i = 0; i < num_elem; ++i) {
	if (scanf(" %d %d %d", &linha, &coluna, &valor) != 3) return 1;
	define_elemento(M[matriz[0]-'A'], linha, coluna, valor);
	printf("Definido %c[%d][%d] = %d .\n", matriz[0], linha, coluna, valor);
      }

    }else if (strcmp(comando, "zera") == 0) {
      if(scanf(" %s %d %d", matriz, &n_linha, &n_coluna) != 3) return 1;
      zera(&M[matriz[0]-'A'], n_linha, n_coluna);
      printf("Inicializando matriz %c[n_linhas=%d][n_colunas=%d].\n", matriz[0], n_linha, n_coluna);

    }else if (strcmp(comando, "soma") == 0) {
      if(scanf(" %s = %s + %s", matA, matB, matC) != 3) return 1;
      if (soma(&(M[matA[0]-'A']), M[matB[0]-'A'], M[matC[0]-'A'])) {
	printf("Somado %c = %c + %c .\n", matA[0], matB[0], matC[0]);
      }else {
	printf("Soma impossivel, tamanhos incompativeis.\n");
      }

    }else if (strcmp(comando, "subtrai") == 0) {
      if(scanf(" %s = %s - %s", matA, matB, matC) != 3) return 1;
      if(subtrai(&(M[matA[0]-'A']), M[matB[0]-'A'], M[matC[0]-'A'])) {
	printf("Subtraido %c = %c - %c .\n", matA[0], matB[0], matC[0]);
      }else{
	printf("Subtracao impossivel, tamanhos incompativeis.\n");
      }
      
    }else if (strcmp(comando, "multiplica") == 0) {
      if(scanf(" %s = %s * %s", matA, matB, matC) != 3) return 1;
      if(multiplica(&M[matA[0]-'A'], M[matB[0]-'A'], M[matC[0]-'A'])) {
	printf("Multiplicado %c = %c * %c .\n", matA[0], matB[0], matC[0]);
      }else {
	printf("Multiplicacao impossivel, tamanhos incompativeis.\n");
      }

    }else if (strcmp(comando, "imprime") == 0) {
      if(scanf(" %s", matA) != 1) return 1;
      printf("%c=", matA[0]);
      imprime(M[matA[0]-'A']);

    }else {
      printf("Comando invalido.\n");
      return 2;
    }
  }
  for (c = 'A'; c <= 'Z'; c++) {
    desaloca_matriz(&(M[c-'A']));
  }
  return 0;
}
