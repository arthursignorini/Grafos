#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Vertice
{
    int existeAresta;
    int peso;
    bool visitado;
} Vertice;

// Celula da pilha agora armazena o numero do vertice
typedef struct Celula
{
    int vertice_num;
    struct Celula *prox;
} Celula;

typedef struct Pilha
{
    Celula *topo;
} Pilha;

Pilha *iniciarPilha()
{
    Pilha *pilha = malloc(sizeof(Pilha));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
    }
    return pilha;
}

void inserirPilha(Pilha *pilha, int x)
{
    Celula *temp = malloc(sizeof(Celula));
    if (temp == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    temp->vertice_num = x;
    temp->prox = pilha->topo;
    pilha->topo = temp;
}

int removerPilha(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("PILHA VAZIA\n");
        exit(1);
    }
    Celula *temp = pilha->topo;
    int elemento = temp->vertice_num;
    pilha->topo = temp->prox;
    free(temp);
    return elemento;
}

bool pilhaVazia(Pilha *pilha)
{
    return pilha->topo == NULL;
}

void inserirArestas(int src, int dest, Vertice **matriz, int tam, int peso)
{
    if (src >= 0 && src < tam && dest >= 0 && dest < tam)
    {
        matriz[src][dest].existeAresta = 1;
        matriz[src][dest].peso = peso;
        matriz[dest][src].existeAresta = 1;
        matriz[dest][src].peso = peso;
    }
    else
    {
        printf("Aviso: Aresta (%d, %d) fora dos limites do grafo.\n", src, dest);
    }
}

void printarGrafo(Vertice **matriz, int tam)
{
    printf("Matriz de Adjacencia:\n");

    printf("  ");
    for (int i = 0; i < tam; i++)
    {
        printf("%c ", i + 65);
    }
    printf("\n");
    for (int i = 0; i < tam; i++)
    {
        printf("%c ", i + 65);
        for (int j = 0; j < tam; j++)
        {
            printf("%d ", matriz[i][j].existeAresta);
        }
        printf("\n");
    }
}

void liberarPilha(Pilha *pilha)
{
    while (!pilhaVazia(pilha))
    {
        removerPilha(pilha);
    }
    free(pilha);
}

void dijkstra(Vertice **matriz, int tam, int origem, int destino) // SERVE PARA PEGAR O MENOR CAMINHO USANDO OS PESOS
{
    int dist[tam];
    bool visitado[tam];
    int anterior[tam];

    // Inicializa distâncias
    for (int i = 0; i < tam; i++)
    {
        dist[i] = INT_MAX;
        visitado[i] = false;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < tam - 1; count++)
    {
        // Encontra o vértice com menor distância ainda não visitado
        int u = -1;
        int menorDist = INT_MAX;
        for (int i = 0; i < tam; i++)
        {
            if (!visitado[i] && dist[i] < menorDist)
            {
                menorDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break; // Não há mais vértices alcançáveis

        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos de u
        for (int v = 0; v < tam; v++)
        {
            if (!visitado[v] && matriz[u][v].existeAresta &&
                dist[u] != INT_MAX &&
                dist[u] + matriz[u][v].peso < dist[v])
            {
                dist[v] = dist[u] + matriz[u][v].peso;
                anterior[v] = u;
            }
        }
    }

    // Resultado
    if (dist[destino] == INT_MAX)
    {
        printf("Nao existe caminho entre %c e %c\n", origem + 65, destino + 65);
    }
    else
    {
        printf("Menor distancia entre %c e %c = %d\n", origem + 65, destino + 65, dist[destino]);

        // Reconstruir caminho
        printf("Caminho: ");
        int caminho[tam];
        int atual = destino;
        int tamanho = 0;

        while (atual != -1)
        {
            caminho[tamanho++] = atual;
            atual = anterior[atual];
        }

        for (int i = tamanho - 1; i >= 0; i--)
        {
            printf("%c", caminho[i] + 65);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");
    }
}

void printarPesos(Vertice **matriz, int tam) {
    for(int i=0; i<tam; i++) {
        for(int j=0; j<tam; j++) {
            if(matriz[i][j].existeAresta == 1) {
                printf("Aresta %C X %C | Peso = %d\n", i+65,j+65,matriz[i][j].peso);
            }
        }
    }
}

int main()
{
    int tam;
    printf("Digite a quantidade de vertices do seu grafo: ");
    scanf("%d", &tam);

    // Alocacao dinamica da matriz de adjacencia
    Vertice **matriz = malloc(tam * sizeof(Vertice *));
    for (int i = 0; i < tam; i++)
    {
        matriz[i] = malloc(tam * sizeof(Vertice));
    }

    // Inicializacao
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            matriz[i][j].existeAresta = 0;
            matriz[i][j].visitado = false;
        }
    }

    int qntdArestas;
    printf("Digite a quantidade de arestas: ");
    scanf("%d", &qntdArestas);

    for (int i = 0; i < qntdArestas; i++)
    {
        char n1, n2;
        int peso;
        printf("Digite os vertices conectados e os pesos (A B 3): ");
        scanf(" %c %c %d", &n1, &n2, &peso);
        inserirArestas(n1 - 65, n2 - 65, matriz, tam, peso);
    }

    printarGrafo(matriz, tam);
    printarPesos(matriz, tam);

    char origemChar, destinoChar;
    printf("Digite os vertices para encontrar o menor caminho (ex: A C): ");
    scanf(" %c %c", &origemChar, &destinoChar);

    int origem = origemChar - 65;
    int destino = destinoChar - 65;

    dijkstra(matriz, tam, origem, destino);

    return 0;
}