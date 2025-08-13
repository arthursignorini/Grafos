#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista de adjacências
struct Node {
  int vertex;          // Armazena o número do vértice
  struct Node* next;   // Ponteiro para o próximo nó na lista
};

// Estrutura para o grafo
struct Graph {
  int num_vertices;      // O número total de vértices no grafo
  struct Node** adjLists; // Array de ponteiros para as listas de adjacências
};

// Função para criar um novo nó
struct Node* createNode(int v) {
  // 1. Aloca dinamicamente memória para um novo nó
  struct Node* newNode = malloc(sizeof(struct Node));
  
  // 2. Acessa os campos da struct através do ponteiro
  newNode->vertex = v;
  newNode->next = NULL; 
  
  // 3. Retorna o ponteiro para o nó criado
  return newNode;
}

// Função para criar um grafo
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->num_vertices = vertices;
  
  // Aloca memória para o array de ponteiros das listas de adjacências
  graph->adjLists = malloc(vertices * sizeof(struct Node*));

  // Inicializa cada ponteiro do array como NULL
  for (int i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
  }
  return graph;
}

// Função para adicionar uma aresta (não-direcionada)
void addEdge(struct Graph* graph, int src, int dest) {
  // Adiciona aresta de src para dest (sentido 1)
  struct Node* newNode = createNode(dest);
  // O novo nó aponta para o que era o primeiro da lista do vértice 'src'
  newNode->next = graph->adjLists[src];
  // O cabeçalho da lista agora aponta para o novo nó
  graph->adjLists[src] = newNode;

  // Como o grafo não é direcionado, fazemos o mesmo para o sentido oposto
  // Adiciona aresta de dest para src (sentido 2)
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Função para imprimir o grafo
void printGraph(struct Graph* graph) {
  for (int v = 0; v < graph->num_vertices; v++) {
    // 'temp' é um ponteiro temporário para percorrer a lista
    struct Node* temp = graph->adjLists[v];
    printf("\nLista de adjacencias do vertice %d\n", v);
    while (temp) {
      printf(" -> %d", temp->vertex);
      // 'temp' avança para o próximo nó
      temp = temp->next;
    }
    printf("\n");
  }
}

// Exemplo de uso
int main() {
  struct Graph* graph = createGraph(5);
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 4);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 3);
  addEdge(graph, 1, 4);
  addEdge(graph, 2, 3);
  addEdge(graph, 3, 4);

  printGraph(graph);

  return 0;
}