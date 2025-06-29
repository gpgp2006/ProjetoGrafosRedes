#include <iostream>
#include <stack>
#include <queue>
#include "grafo.h"

#define INF 1000000      //número estupidamente alto para representar infinito

using namespace std;

// Inicializa o grafo com n vértices e sem arestas
void inicializarGrafo(Grafo &g, int n) {
    g.num_vertices = n;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            g.matriz[i][j] = 0;
}

// Adiciona uma aresta entre os vértices u e v (grafo não direcionado) com peso
void adicionarAresta(Grafo &g, int u, int v, int peso) {
    if (u >= 0 && u < g.num_vertices && v >= 0 && v < g.num_vertices) {
        g.matriz[u][v] = peso;
        g.matriz[v][u] = peso; 
    }
}

// Imprime a matriz de adjacência com índices de linha e coluna
void imprimirGrafo(const Grafo &g) {
    cout << "Matriz de Adjacência:\n\n";

    // Imprime os índices das colunas
    cout << "    "; // espaço para alinhar com os índices das linhas
    for (int j = 0; j < g.num_vertices; j++) {
        cout << j << "   ";
    }
    cout << "\n";

    // Linha separadora
    cout << "  ";
    for (int j = 0; j < g.num_vertices; j++) {
        cout << "----";
    }
    cout << "-\n";

    // Imprime as linhas da matriz com os índices
    for (int i = 0; i < g.num_vertices; i++) {
        cout << i << " | ";
        for (int j = 0; j < g.num_vertices; j++) {
            cout << g.matriz[i][j] << "   ";
        }
        cout << "\n";
    }
}

// Imprime a busca em largura de um grafo
void buscaEmLargura(const Grafo &g, int inicio) {
    bool visitado[MAX_VERTICES] = {false}; // vetor de visitados
    queue<int> fila;

    visitado[inicio] = true;
    fila.push(inicio);

    cout << "Busca em Largura a partir do vértice " << inicio << ": ";

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        cout << atual << " ";

        for (int i = 0; i < g.num_vertices; i++) {
            if (g.matriz[atual][i] != 0 && !visitado[i]) {
                visitado[i] = true;
                fila.push(i);
            }
        }
    }

    cout << "\n";
}

// Imprime a busca em profundidade do grafo
void buscaEmProfundidade(const Grafo &g, int inicio) {
    bool visitado[MAX_VERTICES] = {false};
    stack<int> pilha;

    pilha.push(inicio);

    cout << "Busca em profundidade a partir do vertice " << inicio << ": ";

    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();

        if (!visitado[v]) {
            visitado[v] = true;
            cout << v << " ";

            for (int i = g.num_vertices - 1; i >= 0; i--) {
                if (g.matriz[v][i] != 0 && !visitado[i]) {
                    pilha.push(i);
                }
            }
        }
    }

    cout << "\n";
}

// algoritmo de dijkstra
void dijkstra(const Grafo &g, int inicio) {
    vector<int> d(g.num_vertices, INF);             // veto de distâncias (d[u])
    vector<int> pi(g.num_vertices, -1);             // vetor de predecessores (pi[u])
    vector<bool> visitado(g.num_vertices, false);   // vetor de visitados (S)

    // min heap - priority queue invertida / menor para maior, em pares (distância, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    d[inicio] = 0;                                  //d[s] <-- 0
    pq.push({0, inicio});                           //coloca o vertice inicial, com distancia 0, na fila

    while (!pq.empty()) {                           //enquanto |q| != 0
        int u = pq.top().second;                    //pega o segundo valor da fila para atribuir ao verticeAtual
        pq.pop();                                   //remove o valor da fila, da distancia minima e vertice, que ja foram utilizados na linha acima

        if (visitado[u])                            //se o vertice atual já foi visitado, pule tudo e volte ao início do while
            continue;

        visitado[u] = true;                         //atribui true ao vértice atual, para próximas iterações

        for (int v = 0; v < g.num_vertices; v++) {  //for para percorrer todos os vertices
            int peso = g.matriz[u][v];              //atribui o peso da conexao entre vertices, de acordo com a funcao adicionarArestas
            if (peso > 0 && !visitado[v]) {         //se o peso for maior que 0 e o vertice nao tiver sido visitado
                if (d[v] > d[u] + peso) {           //se a distancia armazenada for maior que a distancia do verticeAtual + peso
                    d[v] = d[u] + peso;             //aloca o valor da distancia do verticeAtual + peso no local correto
                    pi[v] = u;                      //troca o predecessor pelo verticeAtual
                    pq.push({d[v], v});             //coloca a nova distancia e o vertice na fila
                }
            }
        }
    }

    // cout de distancias minimas (d)
    cout << "Distâncias mínimas a partir do vértice " << inicio << ":\n";
    for (int i = 0; i < g.num_vertices; i++) {
        cout << "Vértice " << i << ": ";
        if (d[i] == INF)
            cout << "inacessível";
        else
            cout << d[i];
        cout << "\n";
    }

    //cout de predecessores (pi)
    cout << "\nPredecessores:\n";
    for (int i = 0; i < g.num_vertices; i++) {
        cout << "Vértice " << i << ": ";
        if (pi[i] == -1)
            cout << "nenhum";
        else
            cout << pi[i];
        cout << "\n";
    }
}