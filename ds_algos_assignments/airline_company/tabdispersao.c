/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include "grafo.h"

tabela_dispersao *tabela_nova(int capacidade, hash_func *hfunc, sond_func *sfunc)
{
    if (hfunc == NULL)
        return NULL;

    tabela_dispersao *hash_table = (tabela_dispersao *) malloc(sizeof (tabela_dispersao));
    if (hash_table == NULL)
        return NULL;

    hash_table->estado_celulas = (int *)malloc(capacidade * sizeof(int));
    if (hash_table->estado_celulas == NULL)
        return NULL;
    memset(hash_table->estado_celulas, 0, capacidade * sizeof(int));

    hash_table->nos = (no_grafo **)malloc(capacidade * sizeof(no_grafo *));
    if (hash_table->nos == NULL)
        return NULL;
    memset(hash_table->nos, 0, capacidade * sizeof(no_grafo *));

    hash_table->tamanho = 0;
    hash_table->capacidade = capacidade;
    hash_table->hfunc = hfunc;
    hash_table->sfunc = sfunc;

    return hash_table;
}

int tabela_adiciona(tabela_dispersao *td, no_grafo *entrada)
{
    if (!td || !entrada)
        return -1;

    // calculate the hash to get the first index
    int index = td->hfunc(entrada->cidade, td->capacidade);

     //use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for(int trials = 0; trials < max_probing_trials; trials++)
    {
        // probe at the current index
        index = td->sfunc(index, trials, td->capacidade);
        
        if (td->estado_celulas[index] == -1 || td->estado_celulas[index] == 0)
        {
            td->nos[index] = entrada;
            td->estado_celulas[index] = 1; // valid node
            td->tamanho++;
            return index;
        }
        else
        {
            // there is a city in this cell
            if(strcmp(td->nos[index]->cidade, entrada->cidade) == 0)
            {
                // the same city we're trying to add
                return index;
            }
            else
            {
                continue;
            }
        }
    }
    return -1; // node not found
}

int tabela_remove(tabela_dispersao *td, no_grafo *saida)
{
    if(!td || !saida)
    {
        return -1;
    }

    // calculate hash value
    int index = td->hfunc(saida->cidade, td->capacidade);

    // use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        // probe the current index
        index = td->sfunc(index, trials, td->capacidade);

        if((td->nos[index]) && strcmp(td->nos[index]->cidade, saida->cidade) == 0 && td->estado_celulas[index] == 1)
        {
            // we fond the city, delete the node
            td->estado_celulas[index] = -1;
            td->nos[index] = NULL;
            td->tamanho--;
            return 0;
        }
        else if((td->nos[index]) && strcmp(td->nos[index]->cidade, saida->cidade) == 0 && td->estado_celulas[index] == -1)
        {
            // we found the city but it's already deleted before
            return 0;
        }

        // while there are collisions at this index, probe for a different index
    }
    return -1; // node not found
}

void tabela_apaga(tabela_dispersao *td)
{
    if (td == NULL) 
        return;

    free(td->nos);
    free(td->estado_celulas);
    free(td);
}


int tabela_existe(tabela_dispersao *td, const char *cidade)
{
    if (!cidade || !td) 
        return -1;

    int index = td->hfunc(cidade, td->tamanho);

    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        // probe the current index
        index = td->sfunc(index, trials, td->capacidade);

        if((td->nos[index]) && strcmp(td->nos[index]->cidade, cidade) == 0 && td->estado_celulas[index] == 1)
        {
            // we fond the city
            return index;
        }
        else if((td->nos[index]) && strcmp(td->nos[index]->cidade, cidade) == 0)
        {
            // we found the city but it's already deleted before
            return -1;
        }

        // while there are collisions at this index, probe for a different index
    }
    return -1;
}

tabela_dispersao *tabela_carrega(grafo *g, int tamanho)
{
    tabela_dispersao *hash_table = tabela_nova(tamanho, hash_krm, sond_rh);
    int result = 0;

    // loop over all graph nodes
    for (int i = 0; i < g->tamanho; i++)
    {
        no_grafo *current_node = g->nos[i];
        result = tabela_adiciona(hash_table, current_node);
        if(result == -1)
        {
            return NULL;
        }
    }

    return hash_table;
}

/*================================================================================*/
unsigned long sond_rh(int pos, int tentativas, int tamanho)
{

    return (pos + tentativas * tentativas) % tamanho;
}

unsigned long hash_krm(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;
}
