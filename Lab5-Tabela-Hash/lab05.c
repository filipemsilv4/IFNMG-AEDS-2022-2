#include <stdio.h>
#include <string.h>

#include "tabela.h"

int main() {
    char comando[300];
    int n_elem_max, elem;
    Tabela T;
    T.n_pos = -1;
    scanf("%d", &n_elem_max);
    aloca_tabela(&T, n_elem_max);
    printf("Inicializada tabela para ate %d elementos.\n", n_elem_max);

    while (scanf(" %s", comando) == 1) {
        if (strcmp(comando, "insere") == 0) {
            if (scanf(" %d", &elem) != 1) return 1;
            int pos = insere(T, elem);
            if (pos == -1) {
                printf("Impossivel inserir elemento %d.\n", elem);
            } else {
                printf("Inserido elemento %d na posicao %d.\n", elem, pos);
            }

        } else if (strcmp(comando, "busca") == 0) {
            if (scanf(" %d", &elem) != 1) return 1;
            int pos = busca(T, elem);
            if (pos == -1) {
                printf("Elemento %d nao encontrado.\n", elem);
            } else {
                printf("Elemento %d encontrado na posicao %d.\n", elem, pos);
            }

        } else if (strcmp(comando, "remove") == 0) {
            if (scanf(" %d", &elem) != 1) return 1;
            int pos = remover(T, elem);
            if (pos == -1) {
                printf("Elemento %d nao encontrado para remocao.\n", elem);
            } else {
                printf("Elemento %d removido da posicao %d.\n", elem, pos);
            }

        } else {
            printf("Comando invalido.\n");
            return 2;
        }
    }
    desaloca_tabela(&T);
    return 0;
}
