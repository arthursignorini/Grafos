// Trabalho_1/Direcionado_NaoPonderado.cpp

#include <bits/stdc++.h>
using namespace std;

struct Grafo {
    int n; // número de vértices
    /* 
       Foi escolhida a lista de adjacência para representar este grafo direcionado e não ponderado 
       pelos seguintes motivos:

       1. Eficiência de memória:
          - Diferente da matriz de adjacência (que ocupa O(n²) posições), a lista de adjacência 
            ocupa O(n + m), onde n é o número de vértices e m o número de arestas.
          - Isso é especialmente vantajoso em grafos esparsos (poucas arestas em relação a n²).

       2. Simplicidade para grafos não ponderados:
          - Como não há pesos, basta armazenar o destino de cada aresta.
          - Não é necessário guardar informações extras como valores ou matrizes de custos.

       3. Facilidade de percorrer vizinhos:
          - Ao percorrer a lista de adjacência de um vértice, acessamos apenas seus vizinhos diretos, 
            evitando iterações desnecessárias sobre vértices não conectados (como ocorreria em uma matriz).

       4. Adequação para algoritmos de grafos:
          - Algoritmos de busca (BFS e DFS) e de verificação de conectividade funcionam de forma 
            mais natural e eficiente sobre listas de adjacência.
          - Também facilita operações como adicionar uma aresta, que é O(1) em média.

       Por esses motivos, a lista de adjacência é a escolha mais adequada para representar este 
       grafo direcionado e não ponderado.
    */
    vector<vector<int>> adj; // lista de adjacência

    Grafo(int n) {
        this->n = n;
        adj.resize(n);
    }

    void addAresta(int u, int v) {
        adj[u].push_back(v);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Grafo g(5);
    g.addAresta(0, 1);
    g.addAresta(0, 2);
    g.addAresta(1, 3);
    g.addAresta(3, 4);

    g.print();
}
