#include <iostream>
#include <queue>
#include <stack>
#include "grafo.cpp"
#include "grafo.h"
using namespace std;

int main() {
    Grafo g;
    g.num_vertices = 5;

    adicionarAresta(g, 0, 1, 15);
    adicionarAresta(g, 0, 2, 20);
    adicionarAresta(g, 0, 3, 15);
    adicionarAresta(g, 1, 2, 5);
    adicionarAresta(g, 1, 4, 5);
    adicionarAresta(g, 2, 3, 10);
    adicionarAresta(g, 2, 4, 10);
    adicionarAresta(g, 3, 4, 5);

    int inicio;

    cout << "Insira o vertice de inicio" << endl;
    cin >> inicio;

    imprimirGrafo(g);
    buscaEmLargura(g, inicio);
    buscaEmProfundidade(g, inicio);
    dijkstra(g, inicio);

    return 0;
}