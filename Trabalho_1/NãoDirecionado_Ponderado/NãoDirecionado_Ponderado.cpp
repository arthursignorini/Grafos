// Trabalho_1/NãoDirecionado_Ponderado.cpp

#include <bits/stdc++.h>
using namespace std;

struct Grafo {
    int n; // número de vértices
    /*
       Grafo não direcionado e ponderado usando lista de adjacência com pares (destino, peso):

       1. Cada aresta (u, v, peso) é armazenada em adj[u] e adj[v], 
          pois a conexão é bidirecional.
       2. Eficiência de memória: lista de adjacência ocupa O(n + m), melhor para grafos esparsos.
       3. Fácil acesso aos vizinhos e seus pesos.
       4. Ideal para algoritmos de caminhos mínimos, MST, etc.
    */
    vector<vector<pair<int, int>>> adj; // lista de adjacência com (vértice, peso)

    Grafo(int n) {
        this->n = n;
        adj.resize(n);
    }

    void addAresta(int u, int v, int peso) {
        adj[u].push_back({v, peso});
        adj[v].push_back({u, peso}); // adiciona a aresta no sentido contrário
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (auto edge : adj[i]) {
                int v = edge.first;
                int peso = edge.second;
                cout << "(" << v << ", " << peso << ") ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Grafo g(5);
    g.addAresta(0, 1, 10);
    g.addAresta(0, 2, 5);
    g.addAresta(1, 3, 2);
    g.addAresta(2, 3, 8);
    g.addAresta(3, 4, 7);

    g.print();
}
