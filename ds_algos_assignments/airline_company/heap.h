/*****************************************************************/
/*    Fila de prioridade / min-heap | PROG2 | MIEEC | 2020/21    */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H
#include "grafo.h"

typedef struct
{
    double prioridade;
    no_grafo *no;
} elemento;

typedef struct
{
    /* numero de elementos no vetor */
    int tamanho;
    /* tamanho maximo do vetor */
    int capacidade;

    /* vetor de apontadores para elementos */
    elemento **elementos;
} heap;

/* cria nova heap de tamanho_maximo */
heap *heap_nova(int tamanho_maximo);

/* apaga heap, libertando toda a memória associada */
void heap_apaga(heap *h);

/* insere elemento 'no' na heap com uma determinada prioridade */
int heap_insere(heap *h, no_grafo *no, double prioridade);

/* remove elemento na raiz da heap */
no_grafo *heap_remove(heap *h);

/* imprime o estado atual da heap, a partir do índice indicado */
void heap_imprime(heap *h, int indice);

#endif /* HEAP_H */
