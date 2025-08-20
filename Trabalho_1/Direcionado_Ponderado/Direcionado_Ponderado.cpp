// Trabalho_1/Direcionado_Ponderado.cpp

#include <bits/stdc++.h>
using namespace std;

struct Grafo
{
    int n; // número de vértices
    /*
       Neste grafo direcionado e ponderado, optamos por usar uma lista de adjacência
       com pares (destino, peso) em vez de matriz de adjacência. Os motivos são:

       1. Eficiência de memória:
          - A matriz de adjacência exigiria O(n²) posições, mesmo que muitas arestas não existam.
          - A lista de adjacência ocupa apenas O(n + m), onde m é o número de arestas,
            armazenando apenas conexões realmente existentes.

       2. Representação natural dos pesos:
          - Cada posição da lista guarda o vértice de destino e o peso da aresta (par de valores).
          - Isso facilita algoritmos que dependem de pesos, como Dijkstra, Bellman-Ford e Prim.

       3. Facilidade para grafos direcionados:
          - Ao adicionar uma aresta (u, v, peso), ela é armazenada apenas na lista de adjacência de u,
            respeitando a direção da aresta.

       4. Operações eficientes:
          - Inserir uma aresta leva O(1) em média.
          - Percorrer os vizinhos de um vértice é eficiente, pois acessamos apenas as arestas de fato conectadas.
          - Ideal para grafos esparsos, comuns em aplicações reais.

       Assim, a lista de adjacência com pares (destino, peso) é a melhor escolha para este grafo direcionado e ponderado.
    */
    vector<vector<pair<int, int>>> adj; // lista de adjacência com (vértice, peso)

    Grafo(int n)
    {
        this->n = n;
        adj.resize(n);
    }

    void addAresta(int u, int v, int peso)
    {
        adj[u].push_back({v, peso});
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << ": ";
            for (auto edge : adj[i])
            {
                int v = edge.first;     // vértice de destino
                int peso = edge.second; // peso da aresta
                cout << "(" << v << ", " << peso << ") ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    Grafo g(5);
    g.addAresta(0, 1, 10);
    g.addAresta(0, 2, 5);
    g.addAresta(1, 3, 2);
    g.addAresta(2, 3, 8);
    g.addAresta(3, 4, 7);

    g.print();
}