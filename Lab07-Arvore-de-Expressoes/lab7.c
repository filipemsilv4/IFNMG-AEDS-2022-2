#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 5
#define MAX_ELEM 50

typedef struct node {
    char val  ;
    bool eh_op;
    struct node *filhoEsquerda;
    struct node *filhoDireita ;
    struct node *acima         ;
} No;

No *alocaNo(char c, No* acima);
bool insereNaArvore(No *raiz, No *novono);

//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(No* root, int space){
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process filhoDireita child first
    print2DUtil(root->filhoDireita, space);
 
    // Print current node after space
    // count
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%c\n", root->val);
 
    // Process left child
    print2DUtil(root->filhoEsquerda, space);
}
// Wrapper over print2DUtil()
void print2D(No* root){
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


int main(void){
    char *expressao = calloc(MAX_ELEM , sizeof(char));
    int pos = 0;

    char c;
    while ((c = getchar()) != EOF){
        if (c != ' '){
            expressao[pos] = c;
            ++pos;
        }
        if (c == '\n'){
            expressao[pos - 1] = '\0';
            break;
        }
    }

    if (realloc(expressao, (strlen(expressao) + 1)) == NULL){ return -1; }

    // No raiz
    No *raiz = alocaNo(expressao[0], NULL);
    for (int i = 1; i < strlen(expressao); ++i){
        insereNaArvore(raiz, alocaNo(expressao[i], NULL));
    }

    print2D(raiz);

}

No *alocaNo(char c, No* acima){
    No *novono = malloc(sizeof(No));

    novono->val    = c    ;
    novono->acima  = acima;
    novono->filhoEsquerda = NULL;
    novono->filhoDireita  = NULL;

    if (isdigit(c) != 0){ novono->eh_op = false; }  // isdigit retorna !0 se for digito
    else                { novono->eh_op = true;  }

    return novono;
}

bool insereNaArvore(No *raiz, No *novono){
    // &
    // Tentar inserir à esquerda
    //  Se houver op, goto &
    //  Se nao houver nada, insere, return true;
    // Tentar inserir à direita
    //  Se houver op, goto &
    //  Se não houver nada, insere, return true;
    // Return false;
    bool sucesso = true;

    if (raiz->filhoEsquerda == NULL){
        novono->acima       =  raiz  ;
        raiz->filhoEsquerda =  novono;
        return true;
    } else if (raiz->filhoEsquerda->eh_op == true){
        sucesso = insereNaArvore(raiz->filhoEsquerda, novono);
        if (sucesso == true){ return true; }
    }
    
    if ((raiz->filhoDireita == NULL)){
        novono->acima      = raiz  ;
        raiz->filhoDireita = novono;
        return true;
    } else if (raiz->filhoDireita->eh_op == true){
        if (insereNaArvore(raiz->filhoDireita, novono) == true){ return true; }
    }
    return false;
}