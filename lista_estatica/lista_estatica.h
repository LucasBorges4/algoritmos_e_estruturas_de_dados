#define const_MAX 100
struct TAD_item_Lista {
    // caracteristicas do item composto;
    int num_Lista;
    char nome_Lista[30];
    float peso_lista;

};

typedef struct lista Lista;

//Definimos um novo tipo baseado na estrutura criada;

//typedef {estrutura} {nome da estrtura} {nome do tipo criado}

struct lista {
    int qtd;
    struct TAD_item_Lista listagem[const_MAX];
};

Lista cria_lista();