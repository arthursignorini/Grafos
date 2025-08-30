#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

typedef struct Fila {
    struct Celula *primeiro;
    struct Celula *ultimo;
} Fila;

Fila*iniciarFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila -> primeiro = (Celula*)malloc(sizeof(Celula));
    fila -> primeiro -> prox = NULL;
    fila -> ultimo = fila -> primeiro;
    return fila;
}

void inserirFila (Fila *fila, int x) {
    fila -> ultimo -> prox = (Celula*)malloc(sizeof(Celula));
    fila -> ultimo -> prox -> elemento = x;
    fila -> ultimo = fila -> ultimo -> prox;
    fila -> ultimo -> prox = NULL;
}

int removerFila(Fila *fila) {
    if(fila -> primeiro == fila -> ultimo) {
        printf("FILA VAIZA");
        exit(1);
    }
    Celula *temp = fila -> primeiro -> prox;
    int elemento = temp -> elemento;
    fila -> primeiro -> prox = temp -> prox;
    if(fila -> ultimo == temp) {
        fila -> ultimo = fila -> primeiro;
    }
    free(temp);
    temp = NULL;
    return elemento;

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

void BFS (int v, int tam, int**matriz, int distancia[]) {
    bool visitados[tam];
    int dist = 0;
    for(int i=0; i<tam;i++) {
        distancia[i] = -1;
        visitados[i] = false;
    }

    Fila *fila = iniciarFila();
    inserirFila(fila, v);
    visitados[v] = true;
    distancia[v] = dist;

    while (fila->primeiro != fila->ultimo) {
        int v_atual = removerFila(fila);
        dist++;
        for(int i=0; i<tam; i++) {
            if (visitados[i] == false && matriz[v_atual][i] == 1) {
               distancia[i] = distancia[v_atual] + 1;
               visitados[i] = true;
               inserirFila(fila, i);
            }
        }
    }
}



int main() {
    int tam;

    Fila *fila = iniciarFila();
    printf("Quantos vertices tem o grafo? ");
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
    printf("Vamos fazer o BFS agora, digite a partir de qual vertice voce quer sair: ");
    scanf(" %c", &vertice);

    int distancia[tam];

    BFS(vertice-65, tam, matriz, distancia);

    for(int i=0; i<tam; i++) {
        printf("\nDistancia para o vertice %c: %d", i+65, distancia[i]);
    }


    return 0;
}