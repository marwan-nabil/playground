/*****************************************************************/
/*          Grafo direcionado | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_
#include <time.h>

/* Estrutura ligação ponderada. */
struct no_grafos;

typedef struct tm data;

typedef struct
{
    char *codigo;              /* código do voo */
    char *companhia;           /* nome da companhia que opera o voo */
    data partida;              /* dia e hora da partida da cidade de origem */
    data chegada;              /* dia e hora da chegada na cidade de destino */
    double preco;              /* preço do voo */
    int lugares;               /* número de lugares disponíveis para a ligação */
    struct no_grafos *destino; /* apontador para o nó de destino do voo */

} aresta_grafo;

/* no_grafo é uma estrutura que tem o nome da cidade e 
   um vetor de apontadores para os destinatários */
typedef struct no_grafos
{
    char *cidade;               /* string com nome da cidade */
    int tamanho;                /* número de posições válidas de ‘arestas’ */
    aresta_grafo **arestas;     /* vetor de apontadores para ‘no_grafo’ */
    double p_acumulado;         /* peso acumulado, útil para o cálculo do algoritmo de Dijkstra */
    struct no_grafos *anterior; /* apontador para nó anterior, útil para o cálculo do algoritmo de Dijkstra */
    data *dataatualizada;       /* data mais recente, útil para o o cálculo do algoritmo de Dijkstra */
} no_grafo;

/* grafo é implementado atraves de vetor apontadores de nos e as respetivas ligacoes */
typedef struct
{
    int tamanho;    /* número de posições válidas de ‘nos’ */
    no_grafo **nos; /* vetor de apontadores para ‘no_grafo’ */
} grafo;

/* cria grafo de tamanho 0
*  retorna um apontador para o grafo criado
*/
grafo *grafo_novo();

/* encontra nó no grafo que tem uma determinada cidade
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro cidade - apontador para uma string que se pretende procurar no grafo
*  retorna um apontador para um nó do grafo se o nó existir, se não existir ou ocorrer um erro retorna NULL
*/
no_grafo *encontra_no(grafo *g, char *cidade);

/* insere um nó no grafo
*  parametro g - apontador para o grafo em que se pretende inserir o nó
*  parametro cidade - nome da cidade do novo nó
*  retorna apontador para o novo nó ou NULL em caso de erro ou em caso de nó repetido
*  obs: não esquecer de atualizar a estrutura grafo com o novo nó
*/
no_grafo *no_insere(grafo *g, char *cidade);

/* cria uma ligação entre a origem e o destino
* parametro origem - apontador para o nó de origem da ligação
* parametro destino - apontador para o nó de destino da ligação
* retorno 0 se for bem sucedido e -1 em caso de erro
*/
int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *companhia, data partida, data chegada, float preco, int lugares);

/* remove e retorna apontador para o nó do grafo ‘g’, referente a ‘cidade’
*  parametro g - apontador para o grafo em que se pretende remover o nó
*  parametro cidade - apontador para a cidade cujo o nó se pretende remover
*  retorna apontador para o nó do grafo referente a cidade sem apagá-lo
*  retorna NULL em caso de insucesso
*/
no_grafo *no_remove(grafo *g, char *cidade);

/* apaga a aresta e liberta toda a memória associada
*  parametro aresta - apontador para a aresta a apagar
*  retorna 0 se for apagado com sucesso e retorna -1 em caso de insucesso
*/
int aresta_apaga(aresta_grafo *aresta);

/* apaga o nó e liberta toda a memória associada
*  parametro no - apontador para o nó a apagar
*  retorna 0 se for apagado com sucesso e retorna -1 em caso de insucesso
*/
int no_apaga(no_grafo *no);

/* apaga grafo e liberta toda a memória associada
*  parametro g - apontador para o grafo que se pretende apagar
*/
void grafo_apaga(grafo *g);

/* encontra um determinado voo através do código 
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro codigo - apontador para o código de voo que se pretende procurar no grafo
*  retorna um apontador para um nó de origem desse voo, em caso de erro retorna NULL 
*  retorna por referência através do argumento ‘aresta_pos‘ a posição da respetiva aresta no vetor de arestas do nó retornado (nó origem do voo)
*/
no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos);

/* pesquisa todo os nós que tenham voos diretos a chegar ao nó com o nome ‘destino’,
*  no dia indicado em ‘chegada’ e com o preço máximo de ‘preco_max’ (inclusive)
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro destino - nome dos nós a procurar
*  parametro chegada - data de chegada dos voos a procurar
*  parametro preco_max - preço máximo dos voos a procurar
*  parametro *n - tamanho do vetor de nós retornados
*  retorna um vetor de apontadores para todos os nós do grafo ‘g’ que cumpram os critérios mencionados
*  retorna NULL se não forem encontrados voos ou em caso de erro
*  o tamanho do vetor deve ser retornado por referência através do argumento ‘n’ e o vetor não deve conter elementos repetidos
*/
no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n);

/* calcula o trajeto mais rápido entre as cidades de ‘origem’ e ‘destino’, 
*  considerando os voos a partir do dia ‘partida’, usando o algoritmo de Dijkstra
*  parametro g - apontador para o grafo
*  parametro origem - nome da cidade de origem do trajeto
*  parametro destino - nome da cidade de destino do trajeto
*  parametro partida - data a partir da qual o trajeto é considerado
*  parametro *n - tamanho do vetor de nós retornado
*  retorna um vetor de apontadores para todos os nós do grafo ‘g’ desse trajeto
*  retorna NULL se não for encontrada nenhuma combinação de voos válida ou em caso de erro
*  o tamanho do vetor deve ser retornado por referência através do argumento ‘n’
*/
no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n);

/* calcula o trajeto com menor número de transbordos entre as cidades de ‘origem’ e ‘destino’, 
*  considerando os voos a partir do dia ‘partida’
*  parametro g - apontador para o grafo
*  parametro origem - nome da cidade de origem do trajeto
*  parametro destino - nome da cidade de destino do trajeto
*  parametro partida - data a partir da qual o trajeto é considerado
*  parametro *n - tamanho do vetor de nós retornado
*  retorna um vetor de apontadores para todos os nós do grafo ‘g’ desse trajeto
*  retorna NULL se não for encontrada nenhuma combinação de voos válida ou em caso de erro
*  o tamanho do vetor deve ser retornado por referência através do argumento ‘n’
*/
no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n);

/* adquire as informações atualizadas e corrige o grafo
*  cada linha do ficheiro contém o código do voo e o número de lugares atualizado
*  parametro ficheiro - nome do ficheiro que contém as informações atualizadas
*  parametro g - apontador para o grafo a alterar
*  parametro *n - tamanho do vetor de arestas retornado
*  remove do grafo e retorna as arestas/voos cujos lugares desceram para zero por via de um vetor de apontadores para aresta_grafo 
*  o tamanho do vetor deve ser retornado por referência através do argumento ‘n’
*  retorna NULL em caso de erro
*/
aresta_grafo **atualiza_lugares(char *ficheiro, grafo *g, int *n);

/* cria e retorna um grafo direccionado, do tipo vetor de adjacências, a partir de um ficheiro
*  parametro nome_ficheiro - nome do ficheiro a ler
*  retorna um apontador para o novo grafo, em caso de erro retorna NULL
*/
grafo *grafo_importa(const char *nome_ficheiro);
#endif
