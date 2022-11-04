#ifndef __TABELA_H__
#define __TABELA_H__

typedef enum{false, true} bool;

typedef int TipoDado;

typedef struct {
  bool ocupado;
  bool jah_usado;
  TipoDado valor;
} ElementoTabela;

typedef struct {
  int n_pos; // numero de posicoes da tabela.
  ElementoTabela *T;
} Tabela;

#define FATOR_FOLGA 5

/* Aloca uma tabela com (FATOR_FOLGA) vezes n_elem_max
   posições. Inicializa coerentemente os campos da Tabela, sendo
   n_pos=FATOR_FOLGA*n_elem_max, ocupado=false e jah_usado=false para
   todo índice.*/
bool aloca_tabela(Tabela *ap_Tabela, int n_elem_max);

/* Desaloca a tabela. */
void desaloca_tabela(Tabela *ap_Tabela);

/* Insere elem na tabela T. Utiliza a posição definida pela função
   hash do arquivo hash.h e hash.c, onde hash(elem, vez, T.n_pos) para
   vez=0,1,2,3...  são as consecutivas posições onde se deve tentar
   colocar o elemento elem.  Retorna a posição onde o elemento será
   inserido, ou -1 caso não seja possível inserir o elemento. */
int insere(Tabela T, int elem);

/* Busca o elemento elem na tabela T. Retorna a posição dele na tabela, 
   ou -1 caso não seja encontrado. */
int busca(Tabela T, int elem);

/* Busca o elemento elem na tabela T. Retorna a antiga posição dele na
   tabela, ou -1 caso não seja encontrado. */
int remover(Tabela T, int elem);

#endif
