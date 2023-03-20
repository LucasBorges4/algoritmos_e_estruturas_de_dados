#include <stdlib.h>

typedef struct grafo Grafo;
//def, struct nome_struct, nome tipo

//Grafo usando Lista de Adjacência;

struct grafo{
    int eh_ponderado;
    int num_vertices; //numero de vertices
    int grau_max;   // maximo de conexões feitas por um grafo
    int** arestas; //guardar conexões (matriz)
    double** pesos; //peso de cada conexão
    int* grau;  
};


//Operações basicas;

Grafo *cria_Grafo(int num_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insere_Aresta(Grafo* gr, int orig, int destino, int eh_digrafo, double peso);
int remove_Aresta(Grafo* gr, int orig, int destino, int eh_digrafo);

//Operações Extras

void mostra_Grafo(Grafo* gr);


//Operações de busca;

/*
    "Busca em profundidade"
    - Partindo de um vértice inicial, ela
    explora o máximo possível cada um dos seus
    ramos antes de retroceder ("backtracking")
    - Poder ser usado para:
    = Encontrar componentes conectados e 
    fortemente conectados;
    = Ordenação topológica de um grafo
    = Resolver quebra-cabeças (Ex: labirinto)
*/
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont);
void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);

/*
    "Busca em largura"
    - Partindo de um vétice inicial, ela
    explora todos os vértices vizinhos. Em seguida,
    para cada vértice vizinho, ela repete esse
    processo, visitando os vértices ainda inexplorados
    - Pode ser usado para
    = Achar componentes conectados
    = Achar todos os vértices conectados a apenas 1 componente
    = Achar o menor caminho entre dois vértices
    = Testar bipartição em grafos
*/

void busca_Largura_Grafo(Grafo* gr, int ini, int *visitado);

/*
    "Busca pelo menor caminho"
    - Partindo de um vértice inicial, calcule a 
    menor distância desse vértice a todos os demais
    (desde que existe um caminho entre eles)
    = Algoritmo de Dijkstra
    - Resolve esse problema para grafos
    "dirigido" ou "não dirigido" com
    arestas de peso "não negativo"
*/

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist);
int procuraMenorDistancia(float *dist, int *visitado, int NV);
