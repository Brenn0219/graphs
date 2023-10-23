#pragma once
#include <stdio.h>
#include "list.h"

/// @brief 
typedef struct Graph {
    int vcount; 
    int ecount;
    size_t structure_size;

    int (*match) (const void *first_key, const void *second_key, size_t structure_size);
    void (*destroy) (void *data);

    List *adjlists;
} Graph;

/// @brief 
typedef struct AdjList {
    void *vertex;
    List *adjacent;
} AdjList;

/// @brief Inicializa o grafico especificado por graph. Esta operacao deve ser chamada para um grafico antes que o grafico possa ser usado com qualquer outra operacao. O argumento match e uma funcao usada por varias operacaoes graficas para determinar se dois vertices correspondem. Deve retornar 1 se first_key for igual second_key e caso contrario. O argumento destroy fornece uma maneira de liberar dados alocados dinamicamente quando graph_destroy e chamado graph_destroy. Para por exemplo, se o gráfico contiver dados alocados dinamicamente usando malloc, destroy devera ser definido como free para libere os dados enquanto o gráfico é destruído. Para dados estruturados contendo vários alocados dinamicamente membros, destroy deve ser definido como uma funçao definida pelo usuario que chama free para cada membro alocado dinamicamente. membro, bem como para a propria estrutura. Para um grafico contendo dados que não devem ser liberados, destrua deve ser definido como NULL. Complexidade - O(1)
/// @param graph ponteiro para um grafo
/// @param structure_size tamanho da estrutura utilizada na lista
/// @param match ponteiro para funcao de comparacao entre as estruturas alocadas na lista
/// @param destroy ponteiro para funcao de liberacao das estruturas alocadas dinamicamente nas listas
void graph_init(Graph *graph, size_t structure_size, int (*match) (const void *first_key, const void *second_key, size_t structure_size), void (*destroy) (void *data));

/// @brief 
/// @param graph 
/// @param path 
int graph_build(Graph *graph, char *path);

/// @brief 
/// @param graph 
void graph_destroy(Graph *graph);

/// @brief Insere um vértice no gráfico especificado por graph. O novo vértice contém um ponteiro para data, então o a memória referenciada pelos dados deve permanecer válida enquanto o vértice permanecer no gráfico. É o responsabilidade do chamador gerenciar o armazenamento associado aos dados. Complexidade - O(V), onde V é o número de vértices no gráfico.
/// @param graph ponteiro para um grafo
/// @param data novo elemento a ser inserido na lista
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário
int graph_insert_vertex(Graph *graph, const void *data);

/// @brief Insere uma aresta do vértice especificado por data1 até o vértice especificado por data2 no gráfico especificado pelo gráfico. Ambos os vértices devem ter sido inseridos anteriormente usando graph_insert_vertex . O novo edge é representado com um ponteiro para data2 na lista de adjacências do vértice especificado por data1 , então a memória referenciada por data2 deve permanecer válida enquanto a aresta permanecer no gráfico. É o responsabilidade do chamador gerenciar o armazenamento associado aos dados2. Para inserir uma aresta (u , v ) em um gráfico não direcionado, chame esta operação duas vezes: uma vez para inserir uma aresta de u a v e novamente para inserir o borda implícita de v para você . Este tipo de representação é comum para gráficos não direcionados. Complexidade - O(V), onde V é o número de vértices no gráfico.
/// @param graph ponteiro para um grafo
/// @param data1 vertice incidente
/// @param data2 vertice sucessor
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário.
int graph_insert_edge(Graph *graph, const void *data1, const void *data2);

/// @brief Remove os dados de correspondência de vértices do gráfico especificado por graph . Todas as arestas incidentes de e para o vértice deve ter sido removido anteriormente usando graph_remove_edge . Ao retornar, os dados apontam para o dados armazenados no vértice que foi removido. É responsabilidade do chamador gerenciar o armazenamento associado aos dados. Complexidade - O (V + E ), onde V é o número de vértices no gráfico e E é o número de arestas.
/// @param graph ponteiro para um grafo
/// @param data vertice a ser removido
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário.
int graph_remove_vertex(Graph *graph, void *data);

/// @brief Remove a borda de data1 para data2 no gráfico especificado por graph . No retorno, data2 aponta para os dados armazenados na lista de adjacências do vértice especificado por data1 . É responsabilidade de o chamador para gerenciar o armazenamento associado aos dados.
/// @param graph ponteiro para um grafo
/// @param data1 vertice incidente
/// @param data2 vertice sucessor
/// @return 0 se a inserção da aresta for bem-sucedida, 1 se a aresta já existir ou -1 caso contrário.
int graph_remove_edge(Graph *graph, void *data1, void *data2);

/// @brief 
/// @param graph 
/// @param data 
/// @param adjlist 
/// @return 
// int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);

/// @brief 
/// @param graph 
/// @param data1 
/// @param data2 
/// @return 
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);

#define graph_adjlists(graph) ((graph)->adjlists)
// Macro que retorna o valor da estrutura que ira ser utilizada na lista do grafo
#define graph_structure_size(graph) ((graph)->structure_size)
// Macro que avalia o número de vértices no gráfico especificado por graph.
#define graph_vcount(graph) ((graph)->vcount)
// Macro que avalia o número de arestas no gráfico especificado por gráfico.
#define graph_ecount(graph) ((graph)->ecount)