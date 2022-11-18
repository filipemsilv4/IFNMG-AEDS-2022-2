#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COUNT 5     // Espaçamento usado na função print2DUtil
#define MAX_ELEM 50 // Maximo de elementos lidos

typedef struct node {
    int  val  ;
    bool eh_op;
    struct node *filhoEsquerda;
    struct node *filhoDireita ;
    struct node *acima        ;
} No;

// Protótipos
bool isop(char c);
No  *alocaNo(int c, bool op);
bool insereNaArvore(No *raiz, No *novono);
int  imprimePosFixada(No *raiz);
void print2D(No* root);
void print2DUtil(No* root, int space);

int main(void){
    char expressao[MAX_ELEM]  ;
    scanf("%[^\n]", expressao);

    char *elemDaExpressao  = malloc(sizeof(char));
    int   digitosDoNum     = 0;
    int   posFinalDoNum    = 0;

    // Alocar o No raiz
    No *raiz;
    int posDoPrimeiroElem  = 0;
    for (int percorreExpressao = 0; percorreExpressao < strlen(expressao) + 1; ++percorreExpressao){
        if (expressao[percorreExpressao] != ' '){
            raiz = alocaNo(expressao[percorreExpressao], true);
            break;
        }
        ++posDoPrimeiroElem;
    }

    // Percorre cada elemento da string
    for (int percorreExpressao = posDoPrimeiroElem + 1; percorreExpressao < strlen(expressao) + 1; ++percorreExpressao){
        // Se for operador:
        if (isop(expressao[percorreExpressao]) == true){
            insereNaArvore(raiz, alocaNo(expressao[percorreExpressao], true));
        }
        // Se for um número, é importante saber o tamanho da "sub-string" que o contém e onde ela termina
        else if (isdigit(expressao[percorreExpressao]) != 0){
            posFinalDoNum = percorreExpressao;
            ++digitosDoNum;
        }
        // Entra nessa condição ao encontrar um espaço após dígito(s)
        else if (((expressao[percorreExpressao] == ' ') || (expressao[percorreExpressao] == '\0')) && digitosDoNum != 0){
            elemDaExpressao = realloc(elemDaExpressao, digitosDoNum + 1);
            // Coloca o numero em uma string
            int countNormal = 0;
            for (int countInverso = digitosDoNum - 1; countInverso >= 0 ; --countInverso){
                elemDaExpressao[countInverso] = expressao[posFinalDoNum - countNormal];
                ++countNormal;
            }
            elemDaExpressao[digitosDoNum] = '\0';  // Finaliza a string com o numero
            insereNaArvore(raiz, alocaNo(atoi(elemDaExpressao), false));
            digitosDoNum = 0;
        }
    }

    //print2D(raiz);

    printf("\n%i\n", imprimePosFixada(raiz));
}

bool isop(char c){
    if (c == '%' || c == '/' || c == '*' || c == '+' || c == '-' || c == '^'){ return true; }
    return false;
}

No *alocaNo(int c, bool op){
    No *novono = malloc(sizeof(No));

    novono->val    = c   ;
    novono->eh_op  = op  ;
    novono->acima  = novono->filhoEsquerda = novono->filhoDireita  = NULL;

    return novono;
}

bool insereNaArvore(No *raiz, No *novono){
    // Se não houver nada na esquerda, tenta inserir
    if (raiz->filhoEsquerda == NULL){
        novono->acima       =  raiz  ;
        raiz->filhoEsquerda =  novono;
        return true;
    } else if (raiz->filhoEsquerda->eh_op == true){  // Se houver operador na posição, chama recursivamente passando o op como raiz
        if (insereNaArvore(raiz->filhoEsquerda, novono) == true){ return true; }
    }
    
    // Se não houver nada na direita, tenta inserir
    if ((raiz->filhoDireita == NULL)){
        novono->acima       =  raiz  ;
        raiz->filhoDireita  =  novono;
        return true;
    } else if (raiz->filhoDireita->eh_op == true){ // Se houver operador na posição, chama recursivamente passando o op como raiz
        if (insereNaArvore(raiz->filhoDireita, novono) == true){ return true; }
    }

    return false;
}

int opera(int a, int b, char op){
    int res = 0;
    switch(op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '%': res = a % b; break;
        case '/': res = a / b; break;
        case '^': res = a ^ b; break;
        default: break;
    }
    return res;
}

int imprimePosFixada(No *raiz){
    int result = 0;

    if (raiz->eh_op == true){
        int esquerda = imprimePosFixada(raiz->filhoEsquerda);
        int direita  = imprimePosFixada(raiz->filhoDireita) ;
        result       = opera(esquerda, direita, (char)raiz->val);
        printf("%c ", (char)raiz->val);
    } else {
        printf("%i ", raiz->val);
        return raiz->val;
    }

    return result;
}

void print2DUtil(No* root, int space){
    // Function to print binary tree in 2D. It does reverse inorder traversal
    // fonte: <https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/> (há alterações)
    // Base case
    if (root == NULL){ return; }
 
    // Increase distance between levels
    space += COUNT;
 
    // Process filhoDireita child first
    print2DUtil(root->filhoDireita, space);
 
    // Print current node after space
    // count
    for (int i = COUNT; i < space; i++){ printf(" "); }
    if (root->eh_op == true){ printf("%c\n", (char)root->val); }
    else { printf("%i\n", root->val); }
 
    // Process left child
    print2DUtil(root->filhoEsquerda, space);
}
void print2D(No* root){
    // Wrapper over print2DUtil()
    // fonte: <https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/>
    // Pass initial space count as 0
    print2DUtil(root, 0);
}