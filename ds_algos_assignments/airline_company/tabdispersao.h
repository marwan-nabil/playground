/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#ifndef TABDISPERSAO_H
#define TABDISPERSAO_H

#include "grafo.h"

/* tabela de dispersão baseada em encadeamento */

typedef unsigned long hash_func(const char *, int);

typedef unsigned long sond_func(int, int, int);

/*
*  estrutura tabela_dispersao para armazenar dados relativos a uma tabela de dispersão
*/
typedef struct
{
  hash_func *hfunc;    /* apontador para função de dispersão */
  sond_func *sfunc;    /* apontador para função de sondagem */
  int capacidade;      /* número de posições alocadas de ‘nos’ */
  int tamanho;         /* número de posições preenchidas de ‘nos’ */
  no_grafo **nos;      /* vetor de apontadores para nó */
  int *estado_celulas; /* vetor de indicadores de estado 0:vazio, 1:válido, -1:removido */
} tabela_dispersao;

/*
*  cria uma tabela de dispersão
*  parametro capacidade - capacidade da tabela de dispersão
*  parametro hash_func - apontador para função de dispersão a ser usada nesta tabela
*  parametro sond_func - apontador para função de sondagem a ser usada nesta tabela
*  retorna uma tabela de dispersão vazia que usa a função de dispersão e a função de sondagem indicadas
*/
tabela_dispersao *tabela_nova(int capacidade, hash_func *hfunc, sond_func *sfunc);

/*
*  adiciona um novo nó à tabela de dispersão
*  parametro td - tabela onde adicionar o nó
*  parametro entrada - nó a ser adicionado
*  retorna o índice do nó adicionado se for bem sucedido e -1 em caso contrário
*/
int tabela_adiciona(tabela_dispersao *td, no_grafo *entrada);

/*
*  remove um nó da tabela não desalocando a memória do mesmo
*  parametro td - tabela onde remover o nó
*  parametro saida - nó a ser removido
*  retorna 0 se a remoção for bem sucedido e -1 em caso contrário
*/
int tabela_remove(tabela_dispersao *td, no_grafo *saida);

/*
*  elimina uma tabela, removendo todos os nós e apaga a memória da estrutura da tabela de dispersão 
*  parametro td - tabela de dispersão a ser apagada
*/
void tabela_apaga(tabela_dispersao *td);

/*
*  verifica se determinada cidade existe na tabela
*  parametro td - tabela onde procurar o valor
*  parametro cidade - cidade a procurar na tabela
*  retorna o índice do nó encontrado na tabela se for bem sucedido e -1 em caso contrário
*/
int tabela_existe(tabela_dispersao *td, const char *cidade);

/*
*  cria e preenche uma nova tabela de dispersão a partir do grafo
*  parametro g - apontador para o grafo 
*  parametro capacidade - capacidade da nova tabela de dispersão 
*  retorna a tabela de dispersão criada ou NULL se ocorrer algum erro
*/
tabela_dispersao *tabela_carrega(grafo *g, int capacidade);

/*
*  função de dispersão
*  calcula hash com base na seguinte fórmula:
*            hash(i) = hash(i-1) + chave[i]
*    em que hash(0) = 7
*
*  parametro chave - string para a qual se pretende calcular o chave de hash
*  parametro tamanho - capacidade da tabela de dispersão
*  nota - chave[i] é o caracter no índice de i da chave
*  retorna o índice correspondente à ‘chave’
*/
unsigned long hash_krm(const char *chave, int tamanho);

/*
*  função de resolução de colisões, implementada por sondagem quadrática
*  parametro pos - índice base onde ocorreu a colisão
*  parametro tentativas - passo/número de tentativas atual
*  parametro tamanho - capacidade da tabela de dispersão
*  retorna um índice alternativo, correspondente à 'tentativa'
*  deve usar esta função sempre que se verificar uma colisão
*/
unsigned long sond_rh(int pos, int tentativas, int tamanho);

#endif
