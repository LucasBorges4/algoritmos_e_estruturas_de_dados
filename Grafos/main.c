#include "grafo.h"
#include <stdio.h>

int main(void){
    Grafo *gr;
    int N, L;

    scanf("%d %d", &N, &L);
    gr = cria_Grafo(N, L, 0);
    for (int i = 0; i < L; i++) {
        int vertice1, vertice2;
        scanf("%d %d", &vertice1, &vertice2);
        insere_Aresta(gr, vertice1, vertice2, 0, 0);
    }
   
    //mostra 
    for (int i = 0; i < N; i++) {
        printf("Linha %d:", i);
        for (int j = 0; j < N; j++) {
            printf(" %d", gr->arestas[i][j]);
        }
        printf("\n");
    }
    libera_Grafo(gr);


    return 0;
}