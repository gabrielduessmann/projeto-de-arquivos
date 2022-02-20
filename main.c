#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <time.h>
#include <string.h>


typedef struct no1 {
    struct no1* pai;
    struct no1* esquerda;
    struct no1* direita;
    int valor;
} No1;

typedef struct arvore1 {
    struct no1* raiz;
} Arvore1;


enum coloracao2 { Vermelho, Preto };
typedef enum coloracao2 Cor2;

typedef struct no2 {
    struct no2* pai;
    struct no2* esquerda;
    struct no2* direita;
    Cor2 cor;
    int valor;
} No2;

typedef struct arvore2 {
    struct no2* raiz;
    struct no2* nulo; 
} Arvore2;


typedef struct no3 {
    int total;
    int* chaves;
    struct no3** filhos;
    struct no3* pai; 
} No3;

typedef struct arvoreB3 {
  No3* raiz;
  int ordem;
} ArvoreB3;


void balanceamento1(Arvore1*, No1*);
int altura1(No1*);
int fb1(No1*);
No1* rsd1(Arvore1*, No1*);
No1* rse1(Arvore1*, No1*);
No1* rdd1(Arvore1*, No1*);
No1* rde1(Arvore1*, No1*);


No2* criarNo2(Arvore2*, No2*, int);
void balancear2(Arvore2*, No2*);
void rotacionarEsquerda2(Arvore2*, No2*);
void rotacionarDireita2(Arvore2*, No2*);

Arvore2* criar2();
int vazia2(Arvore2*);   
No2* adicionar2(Arvore2*, int);
No2* localizar2(Arvore2* arvore, int valor);



Arvore1* criar1() {
    Arvore1 *arvore = malloc(sizeof(Arvore1));
    arvore->raiz = NULL;
  
    return arvore;
}



ArvoreB3* criaArvore3(int);
No3* criaNo3(ArvoreB3*);
void percorreArvore3(No3*);
int pesquisaBinaria3(No3*, int);
int localizaChave3(ArvoreB3*, int);
No3* localizaNo(ArvoreB3*, int);
void adicionaChaveNo3(No3*, No3*, int);
int transbordo3(ArvoreB3*,No3*);
No3* divideNo3(ArvoreB3*, No3*);
void adicionaChaveRecursivo3(ArvoreB3*, No3*, No3*, int);
void adicionaChave3(ArvoreB3*, int);
































/** 
 * AVL tree
 */


long unsigned contador1 = 0;

No1* adicionarNo1(No1* no, int valor) {
    contador1++;
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No1* novo = malloc(sizeof(No1));
            novo->valor = valor;
            novo->pai = no;

            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo1(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No1* novo = malloc(sizeof(No1));
			novo->valor = valor;
            novo->pai = no;
			
            no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo1(no->esquerda, valor);
        }
    }
}

No1* adicionar1(Arvore1* arvore, int valor) {
    contador1++;
    if (arvore->raiz == NULL) {
        No1* novo = malloc(sizeof(No1));
        novo->valor = valor;
        
        arvore->raiz = novo;
			
        return novo;
    } else {
        No1* no = adicionarNo1(arvore->raiz, valor);
        balanceamento1(arvore, no);
        
        return no;
    }
}


int altura1(No1* no){
    contador1++;
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura1(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura1(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}


void balanceamento1(Arvore1* arvore, No1* no) {
    while (no != NULL) {
        contador1++;
        int fator = fb1(no);

        if (fator > 1) { //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb1(no->esquerda) > 0) {
                rsd1(arvore, no); //rotação simples a direita, pois o FB do filho tem sinal igual
            } else {
                rdd1(arvore, no); //rotação dupla a direita, pois o FB do filho tem sinal diferente
            }
        } else if (fator < -1) { //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb1(no->direita) < 0) {
                rse1(arvore, no); //rotação simples a esquerda, pois o FB do filho tem sinal igual
            } else {
                rde1(arvore, no); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
            }
        }

        no = no->pai; 
    }
}

int fb1(No1* no) {
    contador1++;
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura1(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura1(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No1* rse1(Arvore1* arvore, No1* no) {
    contador1++;
    No1* pai = no->pai;
    No1* direita = no->direita;
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No1* rsd1(Arvore1* arvore, No1* no) {
    contador1++;
    No1* pai = no->pai;
    No1* esquerda = no->esquerda;
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No1* rde1(Arvore1* arvore, No1* no) {
    contador1++;
    no->direita = rsd1(arvore, no->direita);
    return rse1(arvore, no);
}

No1* rdd1(Arvore1* arvore, No1* no) {
    contador1++;
    no->esquerda = rse1(arvore, no->esquerda);
    return rsd1(arvore, no);
}




















































/** 
 * Red-black tree
 */

long unsigned contador2 = 0;


Arvore2* criar2() {
    Arvore2 *arvore = malloc(sizeof(Arvore2));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo2(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}


No2* criarNo2(Arvore2* arvore, No2* pai, int valor) {
    contador2++;
    No2* no = malloc(sizeof(No2));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

No2* adicionarNo2(Arvore2* arvore, No2* no, int valor) {
    contador2++;
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo2(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNo2(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo2(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNo2(arvore, no->esquerda, valor);
        }
    }
}

No2* adicionar2(Arvore2* arvore, int valor) {
    contador2++;
    if (vazia2(arvore)) {
        arvore->raiz = criarNo2(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        No2* no = adicionarNo2(arvore, arvore->raiz, valor);
        balancear2(arvore, no);
        
        return no;
    }
}

int vazia2(Arvore2* arvore) {
    // contador2++;
    return arvore->raiz == NULL;
}


void rotacionarEsquerda2(Arvore2* arvore, No2* no) {
    contador2++;
    No2* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita2(Arvore2* arvore, No2* no) {
    contador2++;
    No2* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

void balancear2(Arvore2* arvore, No2* no) {
    while (no->pai->cor == Vermelho) {
        contador2++;
        if (no->pai == no->pai->pai->esquerda) {
            No2 *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda2(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita2(arvore, no->pai->pai); //Caso 3
                }
            }
        } else {
            No2 *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita2(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda2(arvore, no->pai->pai); //Caso 3
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}









































/**
 * B-tree
 */ 

long unsigned contador3 = 0;

ArvoreB3* criaArvore3(int ordem) {
    ArvoreB3* a = malloc(sizeof(ArvoreB3));
    a->ordem = ordem;
    a->raiz = criaNo3(a);

    return a;
}

No3* criaNo3(ArvoreB3* arvore) {
    contador3++;
    int max = arvore->ordem * 2;
    No3* no = malloc(sizeof(No3));

    no->pai = NULL;
        
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No3) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++) {
        contador3++;
        no->filhos[i] = NULL;
    }      

    return no;
}


int pesquisaBinaria3(No3* no, int chave) {
    int inicio = 0, fim = no->total - 1, meio;		
    
    while (inicio <= fim) {	
        contador3++;
        
        meio = (inicio + fim) / 2;
        
        if (no->chaves[meio] == chave) {	
		    return meio; //encontrou	
        } else if (no->chaves[meio] > chave) {
                fim	= meio - 1;	
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou	
}



No3* localizaNo3(ArvoreB3* arvore, int chave) {	
    
    No3 *no = arvore->raiz;
    
    while (no != NULL) {
        contador3++;
        int i = pesquisaBinaria3(no, chave);

        if (no->filhos[i] == NULL)
            return no; //encontrou nó
        else
            no = no->filhos[i];
    }

    return NULL; //não encontrou nenhum nó
}



void adicionaChaveNo3(No3* no, No3* novo, int chave) {
    contador3++;
    int i = pesquisaBinaria3(no, chave);

    for (int j = no->total - 1; j >= i; j--) {
        contador3++;
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    
    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;

    no->total++;
}

int transbordo3(ArvoreB3* arvore, No3* no) {
    contador3++;
    
    return no->total > arvore->ordem * 2;
}

No3* divideNo3(ArvoreB3* arvore, No3* no) {
    contador3++;
    int meio = no->total / 2;
    No3* novo = criaNo3(arvore);
    novo->pai = no->pai;
    
    for (int i = meio + 1; i < no->total; i++) {
        contador3++;
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    no->total = meio;
    return novo;
}

void adicionaChaveRecursivo3(ArvoreB3* arvore, No3* no, No3* novo, int chave) {
    contador3++;
    
    adicionaChaveNo3(no, novo, chave);
    
    if (transbordo3(arvore, no)) {
        int promovido = no->chaves[arvore->ordem]; 
        No3* novo = divideNo3(arvore, no);

        if (no->pai == NULL) {
            
            No3* pai = criaNo3(arvore);            
            pai->filhos[0] = no;
            adicionaChaveNo3(pai, novo, promovido);
            
            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else
            adicionaChaveRecursivo3(arvore, no->pai, novo, promovido);
    }
}

void adicionaChave3(ArvoreB3* arvore, int chave) {
    contador3++;
    No3* no = localizaNo3(arvore, chave);

    adicionaChaveRecursivo3(arvore, no, NULL, chave);
}














































int main(int argc, char *argv[]) {
  

    long unsigned quantityOperationsAVLTree[10][1000] = {};
    long unsigned quantityOperationsRedBlackTree[10][1000] = {};
    long unsigned quantityOperationsBTree[1][2] = {};

    for (int executionTime = 0; executionTime < 10; executionTime++) {
   
        time_t t;
        srand((unsigned) time(&t));

        long unsigned keys[1000];
        for (int i = 0; i < 1000; i++) {
            keys[i] = rand();
            int indexKeyFound = -1;
            int index = 0;
            while (indexKeyFound == -1) {
                
                if (keys[index] == keys[i]) {
                    indexKeyFound = index;
                } 
                index++;
            }
            if (indexKeyFound != i) {
                i--;
            }
        }
        
        for (int quantityInsertionKeys = 0; quantityInsertionKeys < 1000; quantityInsertionKeys++) {
            contador1 = 0;
            contador2 = 0;
            contador3 = 0;

            // AVL tree
            Arvore1* avlTree = criar1();
            contador1 =0;

            // Red-black tree
            Arvore2* redBlackTree = criar2();
            contador2 = 0;

            // B-tree
            ArvoreB3* bTree = criaArvore3(1);
            contador3 = 0;

            for (int i = 0; i <= quantityInsertionKeys; i++) {
                adicionar1(avlTree,keys[i]);
                adicionar2(redBlackTree,keys[i]); 
                adicionaChave3(bTree, keys[i]); 
            }

            free(avlTree);
            free(redBlackTree);
            free(bTree);

            quantityOperationsAVLTree[executionTime][quantityInsertionKeys] = contador1;
            quantityOperationsRedBlackTree[executionTime][quantityInsertionKeys] = contador2;
            quantityOperationsBTree[executionTime][quantityInsertionKeys] = contador3;

            printf("\nNúmero de operações 1: %ld", contador1);
            printf("\nNúmero de operações 2: %ld", contador2);
            printf("\nNúmero de operações 3 (%i, %i): %ld\n", executionTime, quantityInsertionKeys, quantityOperationsBTree[executionTime][quantityInsertionKeys]);
        }

    }  

    char strAvarageQuantityOperations[100000] = "";
    
    FILE *file;
    file = fopen("operationsQuantity2.csv", "w+");    
    
   
    fprintf(file, "Quantidade média de operações para inserção de registros aleatórios\n");
    fprintf(file, ", Arvore AVL, Arvore Rubro-negran, Arvore B\n"); 
   
    for (int j=0; j<1000; j++) {

        long unsigned quantityOperationsAVLTreeSum = 0;
        long unsigned quantityOperationsRedBlackTreeSum = 0;
        long unsigned quantityOperationsBTreeSum = 0;
        
        for (int k = 0; k < 10; k++) {
            
            quantityOperationsAVLTreeSum = quantityOperationsAVLTreeSum + quantityOperationsAVLTree[k][j];
            quantityOperationsRedBlackTreeSum = quantityOperationsRedBlackTreeSum + quantityOperationsRedBlackTree[k][j];
            quantityOperationsBTreeSum = quantityOperationsBTreeSum + quantityOperationsBTree[k][j];

        }

        sprintf(strAvarageQuantityOperations, ", %.3f, %.3f, %.3f \n",
        (float) quantityOperationsAVLTreeSum / 10, (float) quantityOperationsRedBlackTreeSum / 10, (float) quantityOperationsBTreeSum / 10);
        
        printf("\nLinha %d) %s", j, strAvarageQuantityOperations);         
        fprintf(file, strAvarageQuantityOperations);   
    }
       

    fprintf(file, "Quantidade de operações para inserção de registros ordenados em order crescente\n");
    fprintf(file, ", Arvore AVL, Arvore Rubro-negran, Arvore B\n");


    for (int s = 0; s < 1000; s++) {

        // AVL tree
        Arvore1* avlTree = criar1();
        contador1 = 0;

        // Red-black tree
        Arvore2* redBlackTree = criar2();
        contador2 = 0;

        // B-tree
        ArvoreB3* bTree = criaArvore3(1);
        contador3 = 0;



        for (int b = 0; b <= s; b++) {
                adicionar1(avlTree, b); 
                adicionar2(redBlackTree,b); 
                adicionaChave3(bTree, b); 
        }

        free(avlTree);
        free(redBlackTree);
        free(bTree);

        sprintf(strAvarageQuantityOperations, ", %d, %d, %d \n", contador1, contador2, contador3);

        printf("Linha %d) %d, %d, %d \n", s, contador1, contador2, contador3);

        fprintf(file, strAvarageQuantityOperations);
        
    }

    printf("Arquivo com os valores criado! \n\n");
    

    fclose(file);

}