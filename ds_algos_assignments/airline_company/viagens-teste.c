/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "tabdispersao.h"
#include "stnova.h"

/* VERIFICACOES IMPLEMENTADAS */

int verifica_no_remove(grafo *g)
{
    int er = 0;

    no_grafo *no;
    no = no_remove(g, "inexistente");
    if (no)
    {
        printf("...verifica_no_remove (teste de cidade inexistente): removeu um nó inexistente (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_no_remove (teste de cidade inexistente): não removeu nenhum nó (OK)\n");
    no_apaga(no);

    no = no_remove(g, "Dallas/Fort Worth/TX");
    no_grafo *nod = encontra_no(g, "Phoenix/AZ");
    if (!no)
    {
        printf("...verifica_no_remove (teste de cidade válida): não removeu (ERRO)\n");
        er++;
    }
    else if (strcmp(no->cidade, "Dallas/Fort Worth/TX") != 0)
    {
        printf("...verifica_no_remove (teste de cidade válida): removeu um nó errado (ERRO)\n");
        er++;
    }
    else if (nod->tamanho != 8)
    {
        printf("...verifica_no_remove (teste de cidade válida): não removeu as arestas corretamente (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_no_remove (teste de cidade válida): removeu com sucesso (OK)\n");
    }

    if (no)
        no_apaga(no);
    return er;
}

int verifica_no_apaga()
{
    int erro;
    char cid[] = "teste";
    no_grafo *norem = (no_grafo *)malloc(sizeof(no_grafo));
    if (norem)
    {

        // aloca espaço para o campo cidade

        norem->cidade = (char *)malloc((strlen(cid) + 1) * sizeof(char));
        if (!norem->cidade)
        {
            free(norem);
        }
        else
        {
            strcpy(norem->cidade, cid);
            norem->tamanho = 0;
            norem->arestas = NULL;
            norem->p_acumulado = 0;
            norem->anterior = NULL;
            norem->dataatualizada = NULL;
            erro = no_apaga(norem);
            if (erro == -1)
            {
                printf("...verifica_no_apaga: deu erro ao apagar nó (ERRO)\n");
                return 1;
            }
            else
                printf("...verifica_no_apaga: apagou com sucesso (OK)\n");
        }
    }
    return 0;
}
int verifica_encontra_voo(grafo *g)
{
    int er = 0;

    no_grafo *no;
    int pos = 0;
    no = encontra_voo(g, "N583AAPHXDFW", &pos);
    if (!no)
    {
        printf("...verifica_encontra_voo: deu erro ao encontrar o voo (ERRO)\n");
        er++;
    }
    else if (strcmp(no->cidade, "Phoenix/AZ") != 0)
    {
        printf("...verifica_encontra_voo: encontrou o nó errado (ERRO)\n");
        er++;
    }
    else if (pos != 3)
    {
        printf("...verifica_encontra_voo: encontrou a aresta errada (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_encontra_voo: encontrou com sucesso (OK)\n");
    }

    return er;
}

int verifica_pesquisa_avancada(grafo *g)
{
    int er = 0;

    no_grafo **vno;
    data chegada;
    chegada.tm_year = 2021;
    chegada.tm_mon = 5;
    chegada.tm_mday = 8;
    chegada.tm_hour = 0;
    chegada.tm_min = 0;
    chegada.tm_sec = 0;
    chegada.tm_isdst = 0;
    int n = 0;
    vno = pesquisa_avancada(g, "Dallas/Fort Worth/TX", chegada, 1400, &n);

    if (!vno)
    {
        printf("...verifica_pesquisa_avancada: deu erro ao encontrar o voo (ERRO)\n");
        er++;
    }
    else if ((n != 1) || (strcmp(vno[0]->cidade, "Las Vegas/NV")) != 0)
    {
        printf("...verifica_pesquisa_avancada: encontrou número de nós errado (ERRO)\n");
        free(vno);
        er++;
    }
    else
    {
        free(vno);
        printf("...verifica_pesquisa_avancada: encontrou com sucesso (OK)\n");
    }

    return er;
}

int verifica_trajeto_mais_rapido(grafo *g)
{
    int er = 0;
    char or [] = "Charlotte/NC";
    char de[] = "Kansas City/MO";
    int n = 0;
    struct tm partida;
    partida.tm_year = 2021;
    partida.tm_mon = 5;
    partida.tm_mday = 1;
    partida.tm_hour = 0;
    partida.tm_min = 0;
    partida.tm_sec = 0;
    partida.tm_isdst = 0;
    no_grafo **teste = trajeto_mais_rapido(g, or, de, partida, &n);

    if (!teste)
    {
        printf("...verifica_trajeto_mais_rapido: deu erro ao encontrar o trajeto mais rápido (ERRO)\n");
        er++;
    }
    else if (n != 3)
    {

        printf("...verifica_trajeto_mais_rapido: encontrou o número de nós errado (ERRO)\n");
        er++;
    }
    else if ((strcmp(teste[0]->cidade, "Charlotte/NC") != 0) || (strcmp(teste[1]->cidade, "Phoenix/AZ") != 0) || (strcmp(teste[2]->cidade, "Kansas City/MO") != 0))
    {

        printf("...verifica_trajeto_mais_rapido: encontrou os nós errados (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_trajeto_mais_rapido: encontrou com sucesso (OK)\n");
    }
    free(teste);
    return er;
}

int verifica_menos_transbordos(grafo *g)
{
    int er = 0;
    char or [] = "Charlotte/NC";
    char de[] = "Kansas City/MO";
    int n = 0;
    struct tm partida;
    partida.tm_year = 2021;
    partida.tm_mon = 5;
    partida.tm_mday = 1;
    partida.tm_hour = 0;
    partida.tm_min = 0;
    partida.tm_sec = 0;
    partida.tm_isdst = 0;
    no_grafo **teste = menos_transbordos(g, or, de, partida, &n);

    if (!teste)
    {
        printf("...verifica_menos_transbordos: deu erro ao encontrar o trajeto com menos transbordos (ERRO)\n");
        er++;
    }
    else if (n != 2)
    {

        printf("...verifica_menos_transbordos: encontrou o número de nós errado (ERRO)\n");
        er++;
    }
    else if ((strcmp(teste[0]->cidade, "Charlotte/NC") != 0) || (strcmp(teste[1]->cidade, "Kansas City/MO") != 0))
    {

        printf("...verifica_menos_transbordos: encontrou os nós errados(ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_menos_transbordos: encontrou com sucesso (OK)\n");
    }
    free(teste);
    return er;
}

int verifica_atualiza_lugares(grafo *g)
{
    int er = 0;

    int n = 0;

    char ficheiro_atualiza[] = "flightPlan_atualiza.txt";
    aresta_grafo **testearesta = atualiza_lugares(ficheiro_atualiza, g, &n);

    if (!testearesta)
    {
        printf("...verifica_atualiza_lugares: deu erro ao fazer o update de lugares (ERRO)\n");
        er++;
    }
    else if (n != 3)
    {

        printf("...verifica_atualiza_lugares: encontrou o número de arestas errado (ERRO)\n");
        er++;
    }
    else if ((strcmp(testearesta[0]->codigo, "N583AACLTPHX") != 0) || (strcmp(testearesta[1]->codigo, "N823AAPITDFW") != 0) || (strcmp(testearesta[2]->codigo, "N744AALAXOMA") != 0))
    {

        printf("...verifica_atualiza_lugares: encontrou as arestas erradas (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_atualiza_lugares: encontrou com sucesso (OK)\n");
    }
    if (testearesta)
    {
        for (int j = 0; j < n; j++)
        {
            free(testearesta[j]->codigo);
            free(testearesta[j]->companhia);
            free(testearesta[j]);
        }

        free(testearesta);
    }
    return er;
}

int verifica_tabela_nova(tabela_dispersao **td)
{
    int er = 0;
    int tamanho = 11;

    *td = tabela_nova(tamanho, hash_krm, sond_rh);

    if (*td)
    {

        if (((*td)->estado_celulas[0] == 0) && ((*td)->hfunc == hash_krm) && ((*td)->sfunc == sond_rh) && ((*td)->capacidade == tamanho))
        {
            printf("...verifica_tabela_nova: tabela_nova criou a tabela corretamente (OK)\n");
        }
        else
        {
            printf("...verifica_tabela_nova: tabela_nova deu erro num dos campos da estrutura da tabela (ERRO)\n");
            er++;
        }
    }
    else

    {
        printf("...verifica_tabela_nova: tabela_nova deu NULL (ERRO)\n");
        er++;
    }

    return er;
}
int verifica_tabela_adiciona(tabela_dispersao *td, grafo *g)
{
    int er = 0;

    char or [] = "Miami/FL";
    char or1[] = "Las Vegas/NV";
    char or2[] = "Atlanta/GA";
    char or3[] = "Salt Lake City/UT";
    char or4[] = "Orlando/FL";
    no_grafo *no1 = encontra_no(g, or);
    no_grafo *no2 = encontra_no(g, or1);
    no_grafo *no3 = encontra_no(g, or2);
    no_grafo *no4 = encontra_no(g, or3);
    int t1 = tabela_adiciona(td, no1);
    int t2 = tabela_adiciona(td, no2);
    int t3 = tabela_adiciona(td, no3);
    int t4 = tabela_adiciona(td, no4);

    if ((t1 == 0) && (t2 == 6) && (t3 == 8) && (t4 == 7) && (td->tamanho == 4))
    {

        printf("...verifica_tabela_adiciona (sem colisão): adicionou corretamente todos os nós (OK)\n");
    }
    else
    {
        printf("...verifica_tabela_adiciona (sem colisão): pelos menos um dos nós não foi adicionado corretamente (ERRO)\n");
        er++;
    }
    no1 = encontra_no(g, or4);
    t1 = tabela_adiciona(td, no1);

    if ((t1 == 10) && (td->tamanho == 5))
    {

        printf("...verifica_tabela_adiciona (com colisão): adicionou corretamente o nó (OK)\n");
    }
    else
    {
        printf("...verifica_tabela_adiciona (com colisão): o nó não foi adicionado corretamente (ERRO)\n");
        er++;
    }
    return er;
}

int verifica_tabela_remove(tabela_dispersao *td, grafo *g)
{
    int er = 0, t;

    no_grafo *no = encontra_no(g, "Las Vegas/NV");
    no_grafo *no1 = encontra_no(g, "Orlando/FL");
    if (no)
    {
        t = tabela_remove(td, no);

        if (!t)
        {

            if ((td->estado_celulas[6] == -1) && (td->nos[6] == NULL) && (td->tamanho == 4))
            {

                printf("...verifica_tabela_remove (remoção sem colisões): tabela_remove removeu corretamente (OK)\n");
            }
            else
            {

                printf("...verifica_tabela_remove (remoção sem colisões): tabela_remove não removeu corretamente (ERRO)\n");
                er++;
            }
        }
        else

        {
            printf("...verifica_tabela_remove (remoção sem colisões): tabela_remove não removeu (ERRO)\n");
            er++;
        }
    }
    if (no1)
    {
        t = tabela_remove(td, no1);

        if (!t)
        {

            if ((td->estado_celulas[10] == -1) && (td->nos[10] == NULL) && (td->tamanho == 3))
            {
                printf("...verifica_tabela_remove (remoção com colisões): tabela_remove removeu corretamente (OK)\n");
            }
            else
            {
                printf("...verifica_tabela_remove (remoção com colisões): tabela_remove não removeu corretamente(ERRO)\n");
                er++;
            }
        }
        else

        {
            printf("...verifica_tabela_remove (remoção com colisões): tabela_remove não removeu (ERRO)\n");
            er++;
        }
    }

    return er;
}

int verifica_tabela_existe(tabela_dispersao *td, grafo *g)
{
    int er = 0, t;

    char or [] = "Phoenix/AZ";

    t = tabela_existe(td, or);

    if (t == -1)
    {
        printf("...verifica_tabela_existe (não existe): tabela_existe não encontrou (OK)\n");
    }
    else

    {
        printf("...verifica_tabela_existe (não existe): tabela_existe encontrou um elemento (ERRO)\n");
        er++;
    }

    char or1[] = "Salt Lake City/UT";

    t = tabela_existe(td, or1);

    if (t != -1)
    {

        if (t != 7)
        {
            printf("...verifica_tabela_existe (existe): tabela_existe não encontrou (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_tabela_existe (existe): tabela_existe encontrou corretamente (OK)\n");
    }
    else

    {
        printf("...verifica_tabela_existe (existe): tabela_existe não removeu (ERRO)\n");
        er++;
    }

    return er;
}

int verifica_tabela_carrega(tabela_dispersao **td, grafo *g)
{
    int er = 0;
    int tamanho = 31;

    *td = tabela_carrega(g, tamanho);

    if (*td)
    {

        if ((*td)->tamanho != 22)
        {
            printf("...verifica_tabela_carrega (número de espaços ocupados): tabela_carrega deu diferente de 22 espaços ocupados (ERRO)\n");
            er++;
        }
        else
            printf("...verifica_tabela_carrega (número de espaços ocupados): tabela_carrega deu 22 espaços ocupados (OK)\n");
    }
    else

    {
        printf("...verifica_tabela_carrega (número de espaços ocupado): tabela_carrega deu NULL (ERRO)\n");
        er++;
    }

    return er;
}

int verifica_st(grafo *g)
{
    int er = 0;
    clock_t start_t, end_t;
    start_t = clock();

    estrutura *st = st_nova();
    st_importa_grafo(st, g);
    end_t = clock();

    printf("\tTempo a criar a nova estrutura: %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    start_t = clock();
    char or [] = "Charlotte/NC";
    char de[] = "Kansas City/MO";
    char or1[] = "Phoenix/AZ";
    char de1[] = "Houston/TX";
    char or2[] = "Atlanta/GA";
    char de2[] = "Salt Lake City/UT";
    char or3[] = "Salt Lake City/UT";
    char de3[] = "Washington/DC";
    char or4[] = "Orlando/FL";
    char de4[] = "Washington/DC";
    char *teste1, *teste2, *teste3, *teste4, *teste5;
    for (int i = 0; i < 20000; i++)
    {
        teste1 = st_pesquisa(st, or, de);
        teste2 = st_pesquisa(st, or1, de1);
        teste3 = st_pesquisa(st, or2, de2);
        teste4 = st_pesquisa(st, or3, de3);
        teste5 = st_pesquisa(st, or4, de4);
    }
    end_t = clock();

    if ((teste1 == NULL) || (teste2 == NULL) || (teste3 == NULL) || (teste4 == NULL) || (teste5 == NULL))
    {
        printf("...verifica_st: st_pesquisa deu NULL numa das pesquisas (ERRO)\n");
        er++;
    }
    else
    {
        if ((strcmp(teste1, "N712AACLTMCI") == 0) && (strcmp(teste2, "N36444PHXIAH") == 0) && (strcmp(teste3, "N819NWATLSLC") == 0) && (strcmp(teste4, "N384DASLCDCA") == 0) && (strcmp(teste5, "N280WNMCOIAD") == 0))
        {
            printf("...verifica_st (100000 pesquisas): st_pesquisa pesquisou os voos corretos (OK)\n");
            printf("\tTempo a pesquisar (100000 pesquisas): %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
        }
        else
        {
            printf("...verifica_st: st_pesquisa não pesquisou corretamente(ERRO)\n");

            er++;
        }
    }

    start_t = clock();
    st_apaga(st);
    end_t = clock();

    printf("\tTempo a apagar a nova estrutura: %.8f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    return er;
}

int main()
{
    int errorCount = 0, error;

    char ficheiro[] = "flightPlan_small.txt";
    grafo *g = grafo_importa(ficheiro);

    printf("INICIO DOS TESTES\n");

    printf("\nTESTES DO GRAFO\n\n");

    error = verifica_encontra_voo(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_encontra_voo\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_encontra_voo passou\n\n");
    }

    error = verifica_pesquisa_avancada(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_pesquisa_avancada\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_pesquisa_avancada passou\n\n");
    }

    error = verifica_trajeto_mais_rapido(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_trajeto_mais_rapido\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_trajeto_mais_rapido passou\n\n");
    }

    error = verifica_menos_transbordos(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_menos_transbordos\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_menos_transbordos passou\n\n");
    }

    error = verifica_atualiza_lugares(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_atualiza_lugares\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_atualiza_lugares passou\n\n");
    }

    error = verifica_no_remove(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_remove passou\n\n");
    }

    error = verifica_no_apaga();
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_apaga\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_apaga passou\n\n");
    }

    printf("\nTESTES DA TABELA DE DISPERSAO\n\n");
    tabela_dispersao *td0, *td;

    error = verifica_tabela_nova(&td0);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_nova\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_tabela_nova passou\n\n");
    }

    error = verifica_tabela_adiciona(td0, g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_adiciona\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_tabela_adiciona passou\n\n");
    }

    error = verifica_tabela_remove(td0, g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_tabela_remove passou\n\n");
    }

    error = verifica_tabela_existe(td0, g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_existe\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_tabela_existe passou\n\n");
    }

    error = verifica_tabela_carrega(&td, g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_tabela_carrega\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_tabela_carrega passou\n\n");
    }

    if (td)
        tabela_apaga(td);
    if (td0)
        tabela_apaga(td0);

    grafo_apaga(g);

    printf("\nTESTES DA ST NOVA\n\n");

    char ficheiro1[] = "flightPlan.txt";
    grafo *g1 = grafo_importa(ficheiro1);

    error = verifica_st(g1);

    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_st\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_st passou\n\n");
    }

    grafo_apaga(g1);

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}
