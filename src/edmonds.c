#include <memory.h>
#include <stdbool.h>
#include "../include/edmonds.h"
#include "../include/graph.h"
#include "../include/print_graph.h"

/// @brief 
/// @param graph 
/// @param v 
/// @param w 
/// @return 
static int check_vertex_cycle(const Graph *graph, const Stack *stack, const void *vertex) {
    for (Cell *element = list_head(stack); element != NULL; element = list_next(element)) {
        if (graph->match(list_data(element), vertex) == 0)
            return 1;
    }

    return  0;
}

/// @brief 
/// @param graph 
/// @param stack 
/// @param spanning_aborescence 
/// @return 
static int contract_cycle(Graph *graph, Stack *stack, Graph *spanning_aborescence) {
    AdjList new_vertex;
    
    // inicializa o novo grafo
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);

    // novo vertice fica identificado com o primeiro da stack (ciclo)
    new_vertex.vertex = list_data(list_head(stack));
    if (graph_insert_vertex(spanning_aborescence, new_vertex.vertex) == -1)
        return -1;

    // inserir os vertices no grafo ignorando os do ciclo  
    int v_cycle = 0, w_cycle = 0;
    void *u = NULL, *p = NULL; 
    for (Cell *element = list_head(graph->adjlists); element != NULL; element = list_next(element)) {
        u = ((AdjList *) list_data(element))->vertex;
        p = list_data(list_head(((AdjList *) list_data(element))->adjacent));

        v_cycle = check_vertex_cycle(graph, stack, u);
        w_cycle = check_vertex_cycle(graph, stack, p);

        if (!v_cycle || !w_cycle) {
            if (!v_cycle && w_cycle)  
                p = new_vertex.vertex;
            else if (v_cycle && !w_cycle)
                u = new_vertex.vertex;

            if (graph_insert_vertex(spanning_aborescence, u) == -1)
                return -1;

            if (graph_insert_vertex(spanning_aborescence, p) == -1)
                return -1;

            if (graph_insert_edge(spanning_aborescence, u, p) == -1)
                return -1;
        }
    }

    graph_destroy(graph);
    free(graph);

    return 0;
}

/// @brief 
/// @param x 
/// @param y 
/// @return 
int compare_integer(const void *x, const void* y) {
    if (!memcmp(x, y, sizeof(int)))
        return 1;
    return 0;
}

/// @brief 
/// @param parents 
/// @param index 
/// @param stack 
/// @return 
static int cycle(const int* parents, const int index, Stack *stack) {
    Stack aux;
    int father;

    stack_init(&aux, sizeof(int), compare_integer, NULL);
    stack_push(&aux, (void *) &index);

    father = parents[index];
    while (father != 0) {
        if (stack_search(&aux, (void *) &father)) {
            while (!compare_integer(&father, stack_peek(&aux))) {
                stack_push(stack, stack_peek(&aux));
                stack_pop(&aux);
            }

            stack_push(stack, &father);

            return 1;
        } else {
            stack_push(&aux, &father);
            father = parents[father];
        }
    }
    
    return 0;
}

/// @brief 
/// @param n 
/// @param parents 
/// @param stack 
/// @return 
static int discover_cycle(const int n, const int* parents, Stack *stack) {
    int retval = 0;

    stack_init(stack, sizeof(int), compare_integer, NULL);

    for (int i = 1; i < n; i++) {
        if ((retval = cycle(parents, i, stack)))
            break;
    }

    return retval; 
}

/// @brief 
/// @param graph 
/// @param weights 
/// @param v_min 
/// @return 
static int find_min_parents(const Graph *graph, int *weights, int *v_min) {
    for (Cell *v = list_head(graph->adjlists); v != NULL; v = list_next(v)) {
        const AdjList *adjlist = (AdjList *) list_data(v);

        for (Cell *i = list_head(adjlist->adjacent); i != NULL; i = list_next(i)) {
            const void *vertex = list_data(i);

            if (weights[vertex_data(vertex)]) {
                if (vertex_weight(vertex) < weights[vertex_data(vertex)]) {
                    weights[vertex_data(vertex)] = vertex_weight(vertex);
                    v_min[vertex_data(vertex)] = vertex_data(adjlist->vertex); 
                }
            } else {
                weights[vertex_data(vertex)] = vertex_weight(vertex);
                v_min[vertex_data(vertex)] = vertex_data(adjlist->vertex);
            }
        }
    }
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @param comparison_weights 
/// @return 
static int edmonds_main(Graph *graph, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {
    Stack stack;
    int n = graph->vcount + 1;
    int weights[n], v_min[n];

    memset((void *) weights, 0, sizeof(int) * n);
    memset((void *) v_min, 0, sizeof(int) * n);
    stack_init(&stack, sizeof(int), compare_integer, NULL);

    find_min_parents(graph, weights, v_min);
    discover_cycle(n, v_min, &stack);
    
    // for (Cell *element = list_head(&stack); element != NULL; element = list_next(element)) 
    //     printf("%d - ", *((int *) list_data(element)));
    // printf("\n");

    // int retval = graph_has_cycle(spanning_aborescence, &stack);
    // if (retval || retval != -1) {
    //     Graph *new_graph = (Graph *) malloc(sizeof(Graph));
        
    //     contract_cycle(spanning_aborescence, &stack, new_graph);

    //     spanning_aborescence = new_graph;
    // }
}

/// @brief 
/// @param graph 
/// @param spanning_aborescence 
/// @param comparison_weights 
void edmonds(Graph *graph, Graph *spanning_aborescence, int (*comparison_weights) (const void* v, const void *w)) {    
    graph_init(spanning_aborescence, graph_structure_size(graph), graph->match, graph->destroy);
    
    edmonds_main(graph, spanning_aborescence, comparison_weights);
}