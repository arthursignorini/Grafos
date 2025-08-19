#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Celula da pilha agora armazena o numero do vertice
typedef struct Celula {
    int vertice_num;
    struct Celula *prox;
} Celula;

typedef struct Pilha {
    Celula *topo;
} Pilha;

Pilha* iniciarPilha() {
    Pilha *pilha = malloc(sizeof(Pilha));
    if (pilha != NULL) {
        pilha->topo = NULL;
    }
    return pilha;
}

void inserirPilha(Pilha *pilha, int x) {
    Celula *temp = malloc(sizeof(Celula));
    if (temp == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    temp->vertice_num = x;
    temp->prox = pilha->topo;
    pilha->topo = temp;
}

int removerPilha(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("PILHA VAZIA\n");
        exit(1);
    }
    Celula *temp = pilha->topo;
    int elemento = temp->vertice_num;
    pilha->topo = temp->prox;
    free(temp);
    return elemento;
}

bool pilhaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void inserirArestas(int src, int dest, int **matriz, int tam) {
    if (src >= 0 && src < tam && dest >= 0 && dest < tam) {
        matriz[src][dest] = 1;
        matriz[dest][src] = 1;
    } else {
        printf("Aviso: Aresta (%d, %d) fora dos limites do grafo.\n", src, dest);
    }
}

void printarGrafo(int **matriz, int tam) {
    printf("Matriz de Adjacencia:\n");

    printf("  ");
    for(int i=0; i<tam; i++) {
      printf("%c ", i+65);
    }
    printf("\n");
    for(int i = 0; i < tam; i++) {
      printf("%c ", i+65);
        for(int j = 0; j < tam; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarPilha(Pilha *pilha) {
    while (!pilhaVazia(pilha)) {
        removerPilha(pilha); 
    }
    free(pilha);
}

bool visitado (int visitados[], int tam, int num) {

  for(int i=0; i<tam; i++) {
    if(num == visitados[i]) {
      return true;
    }
  }
  return false;
}

void DFS(int v, int tam, int **matriz) {

  Pilha* pilha = iniciarPilha();
  inserirPilha(pilha, v);
  int visitados[tam];
  int cont = 0;
  visitados[cont] = v;

  while(!pilhaVazia(pilha)) {

    int elemento = removerPilha(pilha);
    printf("%c ", elemento + 65);

    for(int i=0; i<tam; i++) {
      if(matriz[elemento][i] == 1 && !visitado(visitados, cont, i)){
        inserirPilha(pilha, i);
        cont++;
        visitados[cont] = i;
      }
    }
  }
    
}

int main() {
    int tam;
    printf("Digite a quantidade de vertices do seu grafo: ");
    scanf("%d", &tam);

    // Alocacao dinamica da matriz de adjacencia
    int **matriz = malloc(tam * sizeof(int *));
    for (int i = 0; i < tam; i++) {
        matriz[i] = malloc(tam * sizeof(int));
    }

    // Inicializacao
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matriz[i][j] = 0;
        }
    }

    
    int qntdArestas;
    printf("Digite a quantidade de arestas: ");
    scanf("%d",&qntdArestas);

    for(int i=0; i<qntdArestas; i++) {
        char n1, n2;
        printf("Digite os vertices conectados: ");
        scanf(" %c %c", &n1,&n2);
        inserirArestas(n1 - 65, n2 - 65, matriz, tam);
    }
    
    printarGrafo(matriz, tam);
    
    char vertice;
    printf("Vamos fazer o DFS agora, digite a partir de qual vertice voce quer sair: ");
    scanf(" %c", &vertice);

    DFS(vertice-65, tam, matriz);

  
    return 0;
}