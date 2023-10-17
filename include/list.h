#pragma once

/// @brief Estrutura de dado Celula. O atributo data corresponde o dado que vamos armazenar e next e um ponteiro para proxima celula
typedef struct Cell {
    int data;
    struct Cell *next; 
} Cell;

/// @brief Estrutura de dado Lista Encadeada. A estrutra de Lista Encadead consistem em numero de elementos agrupados ou encadeados em uma ordem especifica.  
typedef struct List {
    int size;
    Cell *head;
    Cell *tail;
} List;

/// @brief inicializa uma lista adicionando 0 para size e nul para head e tail
/// @param list ponteiro para uma lista encadeada
void list_init(List *list);

/// @brief Remove um elemento da lista encadeada
/// @param list ponteiro para uma lista encadeada
/// @param element elemnto que corresponde uma posicao anterior do elemento que ira ser removido
/// @return -1 caso lista for vazia; 0 caso o elemento for removido
int list_remove(List *list, Cell *element);

/// @brief Desalocando uma lista encadeada da memoria
/// @param list ponteiro para uma lista encadeada
/// @return 0 caso lista seja destruida; -1 caso nao de para remover alguma aresta
int list_destroy(List *list);

/// @brief Insere um novo elemento na lista encadeada
/// @param list ponteiro para uma lista encadeada
/// @param element elemnto que corresponde uma posicao anterior do elemento que ira ser inserido
/// @param data dado a ser inserido na nova celula da lista 
/// @return -1 caso a posicao da nova celula ser nula; 0 caso a nova celula for inserida
int list_insert(List *list, Cell *element, int data);

/// @brief Pesquisa um elemento na lista encadeada
/// @param list pointer para uma lista encadeada
/// @param data corresponde o dado que vamos armazenar
/// @return -1 caso o elemento nao for encontrado; 0 caso o elemento for encontrado
int list_search(List *list, int data);
 
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_next(element) ((element)->next)