#include "grafo.h"


Grafo* cria_Grafo(int num_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->num_vertices = num_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(num_vertices,sizeof(int));

        gr->arestas = (int**) malloc(num_vertices * sizeof(int*));
        for(i=0; i < num_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (double**) malloc(num_vertices * sizeof(double*));
            for(i=0; i<num_vertices; i++)
                gr->pesos[i] = (double*) malloc(grau_max * sizeof(double));
        }

    }
    return gr;
}
void libera_Grafo(Grafo *gr){
    if (gr!= NULL) {
        int i;
        for (i = 0; i < gr->num_vertices; i++) {
            free(gr->arestas[i]);
        }
        free(gr->arestas);
        if(gr->eh_ponderado){
            for (i = 0; i < gr -> num_vertices; i++) {
                free(gr->pesos[i]);
            }
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insere_Aresta(Grafo *gr, int orig, int destino, int eh_digrafo, double peso){
    /*
        Verifica se vertices existe;
    */
    
    if (gr == NULL) {
        return 0;
    }
    if (orig < 0 || orig >= gr->num_vertices) {
        return 0;
    }
    if (destino < 0 || destino >= gr ->num_vertices) {
        return 0;
    }
    /*
    Insere no final da linha    
    */
    gr -> arestas[orig][gr->grau[orig]] = destino;
    if (gr -> eh_ponderado) {
        gr->pesos[orig][gr->grau[orig]] = peso;
    }
    gr->grau[orig]++;
    
    /*
    Insere outra aresta se NÃO digrafo    
    */
    if (eh_digrafo == 0) {
        insere_Aresta(gr, destino, orig, 1, peso);
    }
    return 1;
}

int remove_Aresta(Grafo *gr, int orig, int destino, int eh_digrafo){
    /*
        Verfica se existe
    */
    if (gr == NULL) return 0;
    if (orig < 0 || orig >= gr -> num_vertices) return 0;
    if (destino < 0 || destino >= gr->num_vertices) return 0;

    /*
        Procura aresta
    */
    int i = 0;
    while (i < gr -> grau[orig] && gr -> arestas[orig][i] != destino) i++;
    /*
         
    */

    if (i == gr->grau[orig]) return 0;
    gr -> grau[orig]--;
    gr -> arestas[orig][i] = gr -> arestas[orig][gr->grau[orig]];
    if (gr -> eh_ponderado) gr -> pesos[orig][i] = gr -> pesos[orig][gr-> grau[orig]];
    // Remove outra aresta se NÃO for digrafo
    if (eh_digrafo == 0) remove_Aresta(gr, orig, destino, eh_digrafo);

    return 1;
}

/**

Busca em grafos
= Consiste em explorar um grafo
= processo sistemático de como caminhar por seus vertices e arestas
= depende do vertice inicial

*/
//busca em profundidade 
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont){
    int i;
    /*
    Marca o vértice como visitado. Visita os vizinhos ainda não visitados.
    */
    visitado[ini] = cont;
    for (i = 0; i < gr -> grau[ini]; i++) {
        if (!visitado[gr->arestas[ini][i]]) {
            buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont+1);
        }
    }
}

void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado){
    int i, cont = 1;
    for (i = 0; i < gr -> num_vertices; i++) visitado[i] = 0;
    buscaProfundidade(gr, ini, visitado, cont);
}

//busca em largura;
void busca_Largura_Grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1, *fila, inicio_Fila, fim_Fila;
    for (i = 0; i < gr->num_vertices; i++) {
        visitado[i] = 0;
    }
    NV = gr -> num_vertices;
    fila = (int*) malloc(NV * sizeof(int));
    inicio_Fila++;
    fila[inicio_Fila] = ini;
    visitado[ini] = cont;
    while (inicio_Fila != fim_Fila) {
        inicio_Fila = (inicio_Fila + 1) % NV;
        vert = fila[inicio_Fila];
        cont++;
        for (i = 0; i < gr -> grau[vert]; i++) {
            if (!visitado[gr->arestas[vert][i]]){
                fim_Fila = (fim_Fila + 1) % NV;
                fila[fim_Fila] = gr -> arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    } 
    free(fila);
}


//busca pelo menor caminho
int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for (i = 0; i < NV; i++) {
        if (dist[i] >= 0 && visitado[i] == 0) {
            if(primeiro){
                menor = i;
                primeiro = 0;
            }
            else {
                if (dist[menor] > dist[i]) {
                    menor = i;
                }
            }
        }
    }
    return menor;
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){
    int i, cont, NV, ind, *visitado, u;
    cont = NV = gr -> num_vertices;
    /*
    Cria vetor auxiliar
    Inicializa distâncias e anteriores    
    */
    
    visitado = (int*) malloc (NV * sizeof(int));
    for (i = 0; i < NV; i++) {
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while (cont > 0) {
        /*
        Procura vértice com 
        menor distância e marca como visitado
        */
        u = procuraMenorDistancia(dist, visitado, NV);
        if (u == -1) {
            break;
        }

        visitado[u] = 1;
        cont--;
    }
    free(visitado);
     
    for (int i = 0; i < gr->grau[u]; i++) {
        //Para cada vértice vizinho
        ind = gr -> arestas[u][i];
        /*
            Atualizar
            distâncias dos vizinhos        
        */    
        if (dist[ind] < 0) {
            dist[ind] = dist[u] + 1;
            // ou peso da aresta
            // dist[ind] = dist[u] + gr -> pesos[u][i]
            ant[ind] = u;
        }
        else {
            if(dist[ind] > dist[u] + 1){
            //if (dist[ind] > dist[u] + 1)
                dist[ind] = dist[u] + 1;
                // ou peso da aresta
                //dist[ind] = dist[u] + gr->pesos[u][i]
                ant[ind] = u;
            }
        }
    }
}
