#include "matriz.h"
#include <stdlib.h>

#include<unistd.h>


/*
typedef struct No_aux {
  int linha, coluna, valor;
  struct No_aux * direita;  
  struct No_aux * esquerda;
  struct No_aux * abaixo;
  struct No_aux * acima;  
} No;
typedef No * ListaBidim;

typedef struct {
  ListaBidim cabeca;
  int n_linhas;
  int n_colunas;
} Matriz;   */

/* Inicializa uma matriz de zeros com nlin linhas e ncol colunas. 
 * Supõe que não há nada a ser desalocado. */
void inicializa_matriz(Matriz * ap_mat, int nlin, int ncol){
    ap_mat->n_linhas  = nlin;
    ap_mat->n_colunas = ncol;
    ap_mat->cabeca    = calloc(1, sizeof(No));

    ap_mat->cabeca->abaixo   = ap_mat->cabeca; ap_mat->cabeca->acima   = ap_mat->cabeca;
    ap_mat->cabeca->esquerda = ap_mat->cabeca; ap_mat->cabeca->direita = ap_mat->cabeca;
    ap_mat->cabeca->linha    = 0;              ap_mat->cabeca->coluna  = 0;
}

/* Desaloca toda a memória alocada da matriz. */
void desaloca_matriz(Matriz *ap_mat){
  return;
  for (No *percorreCabLinha = ap_mat->cabeca->abaixo; percorreCabLinha != ap_mat->cabeca; percorreCabLinha = percorreCabLinha->abaixo){
    // Segue à direita do nó cabeça da linha, até o fim, o que garante que acessaremos os nós por ordem de coluna
    No *percorreElem = percorreCabLinha->direita;
    while (percorreElem != percorreCabLinha){
        No *tmpElem = percorreElem->direita;
        free(percorreElem);
        percorreElem = tmpElem;
    }
  }

  // limpar os cabecas de linha
  for (No *percorreCabLinha = ap_mat->cabeca->abaixo; percorreCabLinha != ap_mat->cabeca; percorreCabLinha = percorreCabLinha->abaixo){
    No *tmpElem = percorreCabLinha->abaixo;
    free(percorreCabLinha);
    percorreCabLinha = tmpElem;
  }

  // limpar os cabecas de coluna
  for (No *percorreCabColuna = ap_mat->cabeca->direita; percorreCabColuna != ap_mat->cabeca; percorreCabColuna = percorreCabColuna->direita){
    No *tmpElem = percorreCabColuna->direita;
    free(percorreCabColuna);
    percorreCabColuna = tmpElem;
  }

  // limpar cabeca de cabeca
  free(ap_mat->cabeca);

  return;
}

/* Desaloca a memória atualmente utilizada por *mat. Em seguida, 
   inicializa *mat para ser uma matriz de zeros com nlin linhas e
   ncol colunas.  */
void zera(Matriz *ap_mat, int nlin, int ncol){
  //desaloca_matriz(ap_mat);
  inicializa_matriz(ap_mat, nlin, ncol);
  return;
}

// Se não houver cabeça, cabeçá-lo-ei
void insere_linha(Matriz mat, int lin, int col, No *novono){
  No *novoCabLinha = calloc(1, sizeof(No)); 
  novoCabLinha->linha = lin; novoCabLinha->coluna = col;
  novoCabLinha->abaixo = novoCabLinha->acima = novoCabLinha->esquerda = novoCabLinha->direita = novoCabLinha;
  
  bool ha_cabeca = false;

  for (No *percorreCabLinha = mat.cabeca->abaixo; percorreCabLinha != mat.cabeca; percorreCabLinha = percorreCabLinha->abaixo){
    // Caso já haja o no cabeca
    if (percorreCabLinha->linha == lin){
      novoCabLinha = percorreCabLinha;
      ha_cabeca = true;
      break;
    }
    // Caso haja algum maior, inserir antes
    else if (percorreCabLinha->linha > lin){
      novoCabLinha->abaixo = percorreCabLinha;
      novoCabLinha->acima = percorreCabLinha->acima;

      percorreCabLinha->acima->abaixo = novoCabLinha;
      percorreCabLinha->acima = novoCabLinha;
      ha_cabeca = true;
      break;
    }
  }

  // Caso ainda nao tiver criado o cabeca, significa que não há cabecas maiores, ou que nao ha nenhuma; cria o cabeca no fim da lista
  if (ha_cabeca == false){
    novoCabLinha->abaixo = mat.cabeca;
    novoCabLinha->acima = mat.cabeca->acima;
    mat.cabeca->acima->abaixo = novoCabLinha;
    mat.cabeca->acima = novoCabLinha;
  }

  // Na lista de linhas, os nós ficam ordenados por coluna (obvio, pq a linha é a mesma se tao na msm linha né)
  for (No *percorreLinha = novoCabLinha->direita; percorreLinha != novoCabLinha; percorreLinha = percorreLinha->direita){
    // Se o nó atual for maior, inserir antes
    if (percorreLinha->coluna == novono->coluna){
      percorreLinha->valor = novono->valor;
      return;
    }
    if (percorreLinha->coluna > novono->coluna){
      novono->direita = percorreLinha;
      novono->esquerda = percorreLinha->esquerda;

      percorreLinha->esquerda->direita = novono;
      percorreLinha->esquerda = novono;
      return;
    }
  }

  novono->direita = novoCabLinha;
  novono->esquerda = novoCabLinha->esquerda;
  novoCabLinha->esquerda->direita = novono;
  novoCabLinha->esquerda = novono;
  return;
}

void insere_coluna(Matriz mat, int lin, int col, No *novono){
  No *novoCabColuna = calloc(1, sizeof(No)); 
  novoCabColuna->coluna = col; novoCabColuna->linha = lin;
  novoCabColuna->direita = novoCabColuna->esquerda = novoCabColuna->abaixo = novoCabColuna->acima = novoCabColuna;

  bool ha_cabeca = false;

  for (No *percorreCabColuna = mat.cabeca->direita; percorreCabColuna != mat.cabeca; percorreCabColuna = percorreCabColuna->direita){
    // Caso já haja algum
    if (percorreCabColuna->coluna == col){
      novoCabColuna = percorreCabColuna;
      ha_cabeca = true;
      break;
    }
    // Caso haja algum maior, inserir antes
    else if (percorreCabColuna->coluna > col){
      novoCabColuna->direita = percorreCabColuna;
      novoCabColuna->esquerda = percorreCabColuna->esquerda;

      percorreCabColuna->esquerda->direita = novoCabColuna;
      percorreCabColuna->esquerda = novoCabColuna;
      ha_cabeca = true;
      break;
    }
  }

  // Caso ainda nao tiver criado o cabeca, significa que não há cabecas maiores, ou que nao ha nenhuma; cria o cabeca no fim da lista
  if (ha_cabeca == false){
    novoCabColuna->direita = mat.cabeca;
    novoCabColuna->esquerda = mat.cabeca->esquerda;
    mat.cabeca->esquerda->direita =   novoCabColuna;
    mat.cabeca->esquerda = novoCabColuna;
  }

  // Na lista de colunas, os nós ficam ordenados por linha
  for (No *percorreColuna = novoCabColuna->abaixo; percorreColuna != novoCabColuna; percorreColuna = percorreColuna->abaixo){
    // Se o nó atual for maior, inserir antes
    if (percorreColuna->linha == novono->linha){
      percorreColuna->valor = novono->valor;
      return;
    }
    if (percorreColuna->linha > novono->linha){
      novono->abaixo = percorreColuna;
      novono->acima = percorreColuna->acima;

      percorreColuna->acima->abaixo = novono;
      percorreColuna->acima = novono;
      return;
    }
  }

  novono->abaixo = novoCabColuna;
  novono->acima = novoCabColuna->acima;
  novoCabColuna->acima->abaixo = novono;
  novoCabColuna->acima = novono;
  return;
}

/* Define que o elemento na linha lin e coluna col valerá val. 
   O parâmetro lin está em [0,n_linhas-1] e ncol em [0,n_colunas-1].*/
void define_elemento(Matriz mat, int lin, int col, int val){
  No *novono = malloc(sizeof(No));
  novono->linha = lin; novono->coluna = col; novono->valor = val;
  insere_linha(mat, lin, 0, novono); insere_coluna(mat, 0, col, novono);
}

// Fazer coisas fantásticas
void faz_coisas_fantasticas(Matriz *ap_res, No *a, No *b, char op){
  No *perc_a = a->abaixo; No *perc_b = b->abaixo; // perc recebe o cabeca de coluna

  while (perc_a != a && perc_b != b){
    if (perc_a->linha == perc_b->linha){
      // SOMA ou SUBTRAI
      if (op == '+' && perc_a->valor + perc_b->valor != 0){
        define_elemento(*ap_res, perc_a->linha, perc_a->coluna, perc_a->valor + perc_b->valor);
      } else if (op == '-' && perc_a->valor - perc_b->valor){
        define_elemento(*ap_res, perc_a->linha, perc_a->coluna, perc_a->valor - perc_b->valor);
      }

      perc_a = perc_a->abaixo; perc_b = perc_b->abaixo;      // Anda
    } else if (perc_a->linha < perc_b->linha){
      // COPIA A
      define_elemento(*ap_res, perc_a->linha, perc_a->coluna, perc_a->valor);

      perc_a = perc_a->abaixo;      // Anda
    } else if (perc_b->linha < perc_a->linha){
      // COPIA B
      define_elemento(*ap_res, perc_b->linha, perc_b->coluna, perc_b->valor);

      perc_b = perc_b->abaixo;      // Anda
    }
  }

  while (perc_a != a){
    // COPIA RESTO DE A
    define_elemento(*ap_res, perc_a->linha, perc_a->coluna, perc_a->valor);
    perc_a = perc_a->abaixo;
  }
  while (perc_b != b){
    // COPIA RESTO DE B
    define_elemento(*ap_res, perc_b->linha, perc_b->coluna, perc_b->valor);
    perc_b = perc_b->abaixo;
  }
}

/* Computa a soma das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
bool soma(Matriz *ap_res, Matriz a, Matriz b){
  // Se nao tiverem mesmo tamanho, return false
  if (a.n_linhas != b.n_linhas || a.n_colunas != b.n_colunas){ return false; }

  inicializa_matriz(ap_res, a.n_linhas, a.n_colunas);

  No *perc_a = a.cabeca->direita; No *perc_b = b.cabeca->direita; // perc recebe o cabeca de coluna

  // Percorrer a lista de cabecas de coluna (indo para a direita)
  while (perc_a != a.cabeca && perc_b != b.cabeca){
    if (perc_a->coluna == perc_b->coluna){
      // SOMA
      faz_coisas_fantasticas(ap_res, perc_a, perc_b, '+');
      perc_a = perc_a->direita; perc_b = perc_b->direita;   // Anda

    } else if (perc_a->coluna < perc_b->coluna){
      // COPIA A (percorrendo para baixo e copiando cada elemento)
      for (No *perc_col = perc_a->abaixo; perc_col != perc_a; perc_col = perc_col->abaixo){
        define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
      }
      perc_a = perc_a->direita;

    } else if (perc_b->coluna < perc_a->coluna){
      // COPIA B (percorrendo para baixo e copiando cada elemento)
      for (No *perc_col = perc_b->abaixo; perc_col != perc_b; perc_col = perc_col->abaixo){
        define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
      }
      perc_b = perc_b->direita;
    }
  }

  // COPIA RESTO DE A
  while (perc_a != a.cabeca){
    // itera sobre cada elemento
    for (No *perc_col = perc_a->abaixo; perc_col != perc_a; perc_col = perc_col->abaixo){
      define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
    }
    perc_a = perc_a->direita;
  }

  // COPIA RESTO DE B
  while (perc_b != b.cabeca){
    // itera sobre cada elemento
    for (No *perc_col = perc_b->abaixo; perc_col != perc_b; perc_col = perc_col->abaixo){
      define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
    }
    perc_b = perc_b->direita;
  }
  
  return true;
}

/* Computa a subtracao das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
bool subtrai(Matriz *ap_res, Matriz a, Matriz b){
  // Se nao tiverem mesmo tamanho, return false
  if (a.n_linhas != b.n_linhas || a.n_colunas != b.n_colunas){ return false; }

  inicializa_matriz(ap_res, a.n_linhas, a.n_colunas);

  No *perc_a = a.cabeca->direita; No *perc_b = b.cabeca->direita; // perc recebe o cabeca de coluna

  // Percorrer a lista de cabecas de coluna (indo para a direita)
  while (perc_a != a.cabeca && perc_b != b.cabeca){
    if (perc_a->coluna == perc_b->coluna){
      // SUBTRAI
      faz_coisas_fantasticas(ap_res, perc_a, perc_b, '-');
      perc_a = perc_a->direita; perc_b = perc_b->direita;   // Anda

    } else if (perc_a->coluna < perc_b->coluna){
      // COPIA A (percorrendo para baixo e copiando cada elemento)
      for (No *perc_col = perc_a->abaixo; perc_col != perc_a; perc_col = perc_col->abaixo){
        define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
      }
      perc_a = perc_a->direita;

    } else if (perc_b->coluna < perc_a->coluna){
      // COPIA B (percorrendo para baixo e copiando cada elemento)
      for (No *perc_col = perc_b->abaixo; perc_col != perc_b; perc_col = perc_col->abaixo){
        define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
      }
      perc_b = perc_b->direita;
    }
  }

  // COPIA RESTO DE A
  while (perc_a != a.cabeca){
    // itera sobre cada elemento
    for (No *perc_col = perc_a->abaixo; perc_col != perc_a; perc_col = perc_col->abaixo){
      define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
    }
    perc_a = perc_a->direita;
  }

  // COPIA RESTO DE B
  while (perc_b != b.cabeca){
    // itera sobre cada elemento
    for (No *perc_col = perc_b->abaixo; perc_col != perc_b; perc_col = perc_col->abaixo){
      define_elemento(*ap_res, perc_col->linha, perc_col->coluna, perc_col->valor);
    }
    perc_b = perc_b->direita;
  }
  
  return true;
}

/* Computa a multiplicacao das matrizes a e b colocando o resultado em *ap_res.
 * Libera a memória anteriormente utilizada pelos nos de
 * *ap_res, e sobreescreve *ap_res. */
bool multiplica(Matriz *ap_res, Matriz a, Matriz b){  
  inicializa_matriz(ap_res, a.n_linhas, b.n_colunas);

  int mult = 0, soma = 0;

  // percorre cabecas de linha da matriz a
  for (No *a_cabecas_linha = a.cabeca->abaixo; a_cabecas_linha != a.cabeca; a_cabecas_linha = a_cabecas_linha->abaixo){
    // percorre cabecas de coluna da matriz b
    for (No *b_cabecas_coluna = b.cabeca->direita; b_cabecas_coluna != b.cabeca; b_cabecas_coluna = b_cabecas_coluna->direita){
      No *elem_linha_a  = a_cabecas_linha->direita;
      No *elem_coluna_b = b_cabecas_coluna->abaixo;
      // percorrer elementos de linha e coluna ao msm tempo
      while (elem_linha_a != a_cabecas_linha && elem_coluna_b != b_cabecas_coluna){
        if (elem_linha_a->coluna < elem_coluna_b->linha){ elem_linha_a = elem_linha_a->direita; }
        else if (elem_coluna_b->linha < elem_linha_a->coluna){ elem_coluna_b = elem_coluna_b->abaixo; }
        else{   // elem_coluna_b->linha == elem_linha_a->coluna
          mult = elem_linha_a->valor * elem_coluna_b->valor;
          soma = soma + mult;
          elem_linha_a  = elem_linha_a->direita;
          elem_coluna_b = elem_coluna_b->abaixo;
        }
      }
      if (soma != 0){
        define_elemento(*ap_res, a_cabecas_linha->linha, b_cabecas_coluna->coluna, soma);
        soma = 0;
      }
    }
  }

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
  printf("(nlin=%i,ncol=%i", mat.n_linhas, mat.n_colunas);

  // Percorre os nos cabeca de linha
  for (No *percorreCabLinha = mat.cabeca->abaixo; percorreCabLinha != mat.cabeca; percorreCabLinha = percorreCabLinha->abaixo){
    // Segue à direita do nó cabeça da linha, até o fim, o que garante que acessaremos os nós por ordem de coluna
    for (No *percorreLinha = percorreCabLinha->direita; percorreLinha != percorreCabLinha; percorreLinha = percorreLinha->direita){
      printf(",[%i,%i]=%i", percorreLinha->linha, percorreLinha->coluna, percorreLinha->valor);
    }
  }
  printf(")\n");
}