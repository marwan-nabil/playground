/*****************************************************************/
/*          Grafo direcionado | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#include "grafo.h"
#include "heap.h"

//#define LINE__ __LINE__
//#define FILE__ __FILE__
//#define print_error printf("ERROR: at file: %s   line %d\n", FILE__, LINE__);

// creates an empty graph
grafo *grafo_novo()
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    if (!g)
    {
        return NULL;
    }
    g->tamanho = 0;
    g->nos = NULL;
    return g;
}

// searches a graph for a node with the given city name, returns this node
no_grafo *encontra_no(grafo *g, char *cidade)
{
    if(!g || !cidade)
    {
        return NULL;
    }

    // search for cidade (city) in array of nos (nodes)
    for(int i = 0; i < g->tamanho; i++)
    {
        if(strcmp(g->nos[i]->cidade, cidade) == 0)
        {
            return g->nos[i];
        }
    }

    // didn't find the city
    return NULL;
}

// adds a new node with new city name to the graph, returns this node
no_grafo *no_insere(grafo *g, char *cidade)
{
    if(!g || !cidade)
    {
        return NULL;
    }

    // check if the node already exists, by searching the graph for the city
    no_grafo *no = encontra_no(g, cidade);
    if(no)
    {
        return NULL;
    }

    // create the new node for the user
    no = (no_grafo *)malloc(sizeof(no_grafo));
    if(!no)
    {
        return NULL;
    }

    // allocate space for the field cidade
    no->cidade = (char *)calloc((strlen(cidade) + 1), sizeof(char));
    if(!no->cidade)
    {
        free(no);
        return NULL;
    }

    // initializes all fields
    strcpy(no->cidade, cidade);
    no->tamanho = 0;
    no->arestas = NULL;
    no->p_acumulado = INFINITY; // infinite weight
    no->anterior = NULL;
    no->dataatualizada = (data *)calloc(1, sizeof(data));

    if(!no->dataatualizada)
    {
        free(no->cidade);
        free(no);
        return NULL;
    }

    // inserts the created node at the end of the array nos

    no_grafo **temp = (no_grafo **)realloc(g->nos, (g->tamanho + 1) * sizeof(no_grafo *));
    if(!temp)
    {
        free(no->cidade);
        free(no);
        return NULL;
    }
    g->nos = temp;

    // increases the size of the number of nodes and inserts in the array of pointers nós
    g->nos[g->tamanho] = no; // add the new node to the end
    g->tamanho++;

    return no;
}

// auxiliary function that returns 1 if there is an edge for destination
// or 0, if the edge does not exist, -1 if there is an error
// takes source and destination nodes, and the flight number
int existe_aresta(no_grafo *origem, no_grafo *destino, char *codigo)
{
    if(!origem || !destino)
    {
        return -1;
    }

    // search all edges
    for(int i = 0; i < origem->tamanho; i++)
    {
        if((origem->arestas[i]->destino == destino) && ((strcmp(origem->arestas[i]->codigo, codigo) == 0)))
            return 1;
    }

    return 0;
}

// creates an edge (connection) between two cities
int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *companhia, data partida, data chegada, float preco, int lugares)
{
    // error checking
    if(!origem || !destino || !codigo || !companhia)
    {
        return -1;
    }

    if(preco < 0 || lugares < 0)
    {
        return -1;
    }

    // check if the connection already exists
    if(existe_aresta(origem, destino, codigo) > 0)
    {
        return -1;
    }

    // create the new edge
    aresta_grafo *ag = (aresta_grafo *)malloc(sizeof(aresta_grafo));
    if(!ag)
    {
        return -1;
    }

    ag->destino = destino;
    ag->preco = (double)preco;
    ag->lugares = lugares;

   // allocate space for the flight code
    ag->codigo = (char *)calloc((strlen(codigo) + 1), sizeof(char));
    if(!ag->codigo)
    {
            free(ag);
        return -1;
    }
    strcpy(ag->codigo, codigo);

    // allocates space for the company name
    ag->companhia = (char *)malloc((strlen(companhia) + 1) * sizeof(char));
    if(!ag->companhia)
    {
            free(ag->codigo);
        free(ag);
        return -1;
    }
    strcpy(ag->companhia, companhia);

    // initializes all fields in the depatrure time
    ag->partida.tm_year = partida.tm_year;
    ag->partida.tm_mon = partida.tm_mon;
    ag->partida.tm_mday = partida.tm_mday;
    ag->partida.tm_hour = partida.tm_hour;
    ag->partida.tm_min = partida.tm_min;
    ag->partida.tm_sec = 0;
    ag->partida.tm_isdst = 0;

    // initializes all fields in the arrival time
    ag->chegada.tm_year = chegada.tm_year;
    ag->chegada.tm_mon = chegada.tm_mon;
    ag->chegada.tm_mday = chegada.tm_mday;
    ag->chegada.tm_hour = chegada.tm_hour;
    ag->chegada.tm_min = chegada.tm_min;
    ag->chegada.tm_sec = 0;
    ag->chegada.tm_isdst = 0;

    // inserts the new link into the connected edges array for the source nodes
    origem->arestas = (aresta_grafo **)realloc(origem->arestas, (origem->tamanho + 1) * sizeof(aresta_grafo *));
    if(!origem->arestas)
    {
            free(ag->codigo);
        free(ag->companhia);
        free(ag);
        return -1;
    }
    origem->arestas[origem->tamanho] = ag;  // insert new edge for the source node
    origem->tamanho++;

    return 0;
}

// removes a node from a graph
no_grafo *no_remove(grafo *g, char *cidade)
{
    // error checking
    if(!g || !cidade)
    {
        return NULL;
    }

    // get the node of the city we want to delete
    no_grafo *node_to_remove = encontra_no(g, cidade);
    if(!node_to_remove)
    {
        return NULL;
    }

    // loop over all graph nodes and remove all edges pointing to this city
    // and also make all node pointers to the city node NULL
    for(int i = 0; i < g->tamanho; i++)
    {
        no_grafo *current_node = g->nos[i];

        // loop over all edges in this node and remove any edge pointing to the city
        int removed_edges_count = 0;
        for(int j = 0; j < current_node->tamanho; j++)
        {
            aresta_grafo *current_edge = current_node->arestas[j];
            if(current_edge->destino == node_to_remove)
            {
                // remove the edge
                aresta_apaga(current_edge);
                current_node->arestas[j] = NULL;
                removed_edges_count++;
            }
        }

        // adjust the current node edges array to remove NULL edges
        int new_arestas_array_idx = 0;
        aresta_grafo **new_arestas_array =
            (aresta_grafo **)calloc((current_node->tamanho - removed_edges_count), sizeof(aresta_grafo *));
        if(!new_arestas_array)
        {
            return NULL;
        }

        for(int k = 0; k < current_node->tamanho; k++)
        {
            if(current_node->arestas[k] != NULL)
            {
                new_arestas_array[new_arestas_array_idx++] = current_node->arestas[k];
            }
        }

        free(current_node->arestas);
        current_node->arestas = new_arestas_array;
        current_node->tamanho -= removed_edges_count;

        // if the current node has a pointer to the city to delete, make it NULL
        if((current_node->anterior) && (current_node->anterior == node_to_remove))
        {
            current_node->anterior = NULL;
        }
    }

    // adjust the graph
    int new_nos_idx = 0;
    no_grafo **new_nos = (no_grafo **)malloc((g->tamanho - 1) * sizeof(no_grafo *));

    for(int i = 0; i < g->tamanho; i++)
    {
        if(g->nos[i] != node_to_remove)
        {
            new_nos[new_nos_idx++] = g->nos[i];
        }
    }
    g->tamanho -= 1;
    free(g->nos);
    g->nos = new_nos;

    return node_to_remove;
}

// deletes an edge
int aresta_apaga(aresta_grafo *aresta)
{
    if(!aresta)
    {
        return -1;
    }

    // free edge and it's elements
    free(aresta->codigo);
    free(aresta->companhia);
    free(aresta);

    return 0;
}

// delete a node
int no_apaga(no_grafo *no)
{
    if(!no)
    {
        return -1;
    }
    // delete all edges of the node
    for(int i = 0; i < no->tamanho; i++)
    {
        aresta_apaga(no->arestas[i]);
    }

    // delete the city name, latest update date and edges array
    free(no->arestas);
    free(no->cidade);
    free(no->dataatualizada);

    // delete the city node
    free(no);
    return 0;
}

// deletes the graph
void grafo_apaga(grafo *g)
{
    for(int i = 0; i < g->tamanho; i++)
    {
        no_apaga(g->nos[i]);
    }
    free(g);
}

// finds an edge and a node corresponding to a flight number
no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos)
{
    if(!g || !codigo)
    {
        return NULL;
    }

    no_grafo *found_node = NULL;

    for(int i = 0; i < g->tamanho; i++)
    {
        no_grafo *current_node = g->nos[i];
        for(int j = 0; j < current_node->tamanho; j++)
        {
            aresta_grafo *current_edge = current_node->arestas[j];
            if(strcmp(current_edge->codigo, codigo) == 0)
            {
                *aresta_pos = j;
                found_node = current_node;
                break;
            }
        }

        if(found_node)
            break;
    }

    return found_node;
}

// finds and returns all nodes that have direct flights to destination with the provided date and max price
no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n)
{
    heap *found_nodes_heap = heap_nova(g->tamanho);
    if(!found_nodes_heap)
    {
        return NULL;
    }
    no_grafo *destination_city = encontra_no(g, destino);
    if(!destination_city)
    {
        return NULL;
    }

    for(int i = 0; i < g->tamanho; i++)
    {
        no_grafo *current_node = g->nos[i];
        for(int j = 0; j < current_node->tamanho; j++)
        {
            aresta_grafo *current_edge = current_node->arestas[j];
            if
                (
                    (current_edge->destino == destination_city) &&
                    (current_edge->preco < preco_max) &&
                    (current_edge->chegada.tm_year == chegada.tm_year && current_edge->chegada.tm_mon == chegada.tm_mon && current_edge->chegada.tm_mday == chegada.tm_mday)
                    )
            {
                heap_insere(found_nodes_heap, current_node, 1.0f);
                break;
            }
        }
    }

    *n = found_nodes_heap->tamanho;
    no_grafo **found_nodes_array = (no_grafo **)calloc((found_nodes_heap->tamanho), sizeof(no_grafo *));
    if(!found_nodes_array)
    {
        return NULL;
    }
    for(int i = 0; i < found_nodes_heap->tamanho; i++)
    {
        if(found_nodes_heap->elementos[i])
        {
            found_nodes_array[i] = found_nodes_heap->elementos[i]->no;
        }
        else
        {
            return NULL;
        }
    }
    heap_apaga(found_nodes_heap);
    return found_nodes_array;
}

int get_node_index(grafo *g, no_grafo *node)
{
    // get the index of the node in the graph nodes array
    for(int i = 0; i < g->tamanho; i++)
    {
        if(g->nos[i] == node)
        {
            return i;
        }
    }
    return -1;
}

double calculate_time_delta(data *start, data *end)
{
    start->tm_year -= 1900;
    start->tm_mon -= 1;
    start->tm_hour -= 1;
    end->tm_year -= 1900;
    end->tm_mon -= 1;
    end->tm_hour -= 1;
    time_t time1 = mktime(start);
    time_t time2 = mktime(end);
    double result = (double)difftime(time2, time1);
    return result;
}

no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n)
{
    // convert graph into adjacency matrix for the cost of the traversal from node to node
    // on the given departure date
    double **time_cost_matrix = (double **)calloc(g->tamanho, sizeof(double *));
    for(int i = 0; i < g->tamanho; i++)
    {
        time_cost_matrix[i] = (double *)calloc(g->tamanho, sizeof(double));
        // set them all with INFINITY
        for(int j = 0; j < g->tamanho; j++)
        {
            time_cost_matrix[i][j] = INFINITY;
        }
    }

    // cross loop for all nodes
    for(int i = 0; i < g->tamanho; i++)
    {
        no_grafo *source_node = g->nos[i];
        for(int j = 0; j < g->tamanho; j++)
        {
            no_grafo *dest_node = g->nos[j];
            if(source_node == dest_node)
            {
                time_cost_matrix[i][j] = 0.0f; // zero cost
                continue;
            }

            // loop over source node edges
            for(int k = 0; k < source_node->tamanho; k++)
            {
                aresta_grafo *current_source_node_edge = source_node->arestas[k];
                if(current_source_node_edge->destino == dest_node)
                {
                    double time_delta = calculate_time_delta(&current_source_node_edge->partida, &current_source_node_edge->chegada);
                    if(time_delta < time_cost_matrix[i][j])
                    {
                        time_cost_matrix[i][j] = time_delta;
                    }
                }
            }
        }
    }

    // source and target node indices
    int source = get_node_index(g, encontra_no(g, origem));
    int target = get_node_index(g, encontra_no(g, destino));

    // distance[i] will hold the shortest distance from source to i
    double *distance = (double *)malloc(g->tamanho * sizeof(double));
    // array that holds previous node index
    int *previous = (int *)malloc(g->tamanho * sizeof(int));
    // the set of flags of already traversed node
    bool *traversed = (bool *)malloc(g->tamanho * sizeof(bool));
    // array that holds the shortest path from source to destination
    no_grafo **path = (no_grafo **)malloc(g->tamanho * sizeof(no_grafo *));

    // initialise all arrays
    for(int i = 0; i < g->tamanho; i++)
    {
        distance[i] = INFINITY;
        previous[i] = -1;
        traversed[i] = false;
        path[i] = NULL;
    }

    // initialise the current node
    int current = source;
    traversed[current] = true;
    distance[current] = 0.0f;  // distance of source node to itself is 0
    previous[current] = -1;  // no previous node to the source node

    while(traversed[target] == false) // while we still haven't reached the target node
    {
        double min_distance = INFINITY;
        int min_element_index = 0;
        for(int i = 0; i < g->tamanho; i++)
        {
            double distance_from_source_to_this_node_through_current = distance[current] + time_cost_matrix[current][i];
            if(distance_from_source_to_this_node_through_current < distance[i] && traversed[i] == false)
            {
                distance[i] = distance_from_source_to_this_node_through_current;
                previous[i] = current;
            }

            if(distance[i] < min_distance && traversed[i] == false)
            {
                min_distance = distance[i];
                min_element_index = i;
            }
        }

        current = min_element_index; // next element to check is the least distant element from source
        traversed[current] = true;
    }

    current = target;
    int i = 0;
    while(current != -1)
    {
        path[i++] = g->nos[current];
        current = previous[current];
    }
    // we now have the path in reverse order

    // count the path nodes in the path
    int path_count = 0;
    while(path[path_count])
    {
        path_count++;
    }

    if(path_count == 0)
    {
        *n = 0;
        return NULL;
    }
    else
    {
        *n = path_count;
    }

    // reverse the path
    no_grafo **result_path = (no_grafo **)malloc(path_count * sizeof(no_grafo *));
    for(int i = 0; i < path_count; i++)
    {
        result_path[i] = path[path_count - i - 1];
    }
    free(path);

    // free the time_cost_matrix
    for(int i = 0; i < g->tamanho; i++)
    {
        free(time_cost_matrix[i]);
    }
    free(time_cost_matrix);

    // free helper arrays
    free(distance);
    free(previous);
    free(traversed);

    return result_path;
}

no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n)
{
    // source and target node indices
    int source = get_node_index(g, encontra_no(g, origem));
    int target = get_node_index(g, encontra_no(g, destino));

    // convert graph into adjacency matrix for the cost of the traversal from node to node
    // on the given departure date
    int **transfers_cost_matrix = (int **)calloc(g->tamanho, sizeof(int *));
    for(int i = 0; i < g->tamanho; i++)
    {
        transfers_cost_matrix[i] = (int *)calloc(g->tamanho, sizeof(int));
        // set them all with INT_MAX
        for(int j = 0; j < g->tamanho; j++)
        {
            transfers_cost_matrix[i][j] = INT_MAX;
        }
    }

    // cross loop for all nodes
    for(int i = 0; i < g->tamanho; i++)
    {
        no_grafo *source_node = g->nos[i];
        for(int j = 0; j < g->tamanho; j++)
        {
            no_grafo *dest_node = g->nos[j];
            if(source_node == dest_node)
            {
                transfers_cost_matrix[i][j] = 0; // zero cost
                continue;
            }

            // loop over source node edges
            for(int k = 0; k < source_node->tamanho; k++)
            {
                aresta_grafo *current_source_node_edge = source_node->arestas[k];
                if(current_source_node_edge->destino == dest_node)
                {
                    if(dest_node == g->nos[target])
                    {
                        transfers_cost_matrix[i][j] = 1; // a transfer between any city and the desired destination city
                    }
                    else
                    {
                        transfers_cost_matrix[i][j] = 2; // any transfer between two cities
                    }
                }
            }
        }
    }

    int watched_cost_matrix[23][23] = {0};

    for(int i = 0; i < 23; i++)
    {
        for(int j = 0; j < 23; j++)
        {
            watched_cost_matrix[i][j] = transfers_cost_matrix[i][j];
        }
    }

    // distance[i] will hold the shortest distance from source to i
    int *distance = (int *)malloc(g->tamanho * sizeof(int));
    // array that holds previous node index
    int *previous = (int *)malloc(g->tamanho * sizeof(int));
    // the set of flags of already traversed node
    bool *traversed = (bool *)malloc(g->tamanho * sizeof(bool));
    // array that holds the shortest path from source to destination
    no_grafo **path = (no_grafo **)malloc(g->tamanho * sizeof(no_grafo *));

    // initialise all arrays
    for(int i = 0; i < g->tamanho; i++)
    {
        distance[i] = INT_MAX;
        previous[i] = -1;
        traversed[i] = false;
        path[i] = NULL;
    }

    // initialise the current node
    int current = source;
    traversed[current] = true;
    distance[current] = 0;  // distance of source node to itself is 0
    previous[current] = -1;  // no previous node to the source node

    while(traversed[target] == false) // while we still haven't reached the target node
    {
        int min_distance = INT_MAX;
        int min_element_index = 0;

        for(int i = 0; i < g->tamanho; i++)
        {
            int distance_from_source_to_this_node_through_current = distance[current] + transfers_cost_matrix[current][i];
            if(distance_from_source_to_this_node_through_current < distance[i] && traversed[i] == false)
            {
                distance[i] = distance_from_source_to_this_node_through_current;
                previous[i] = current;
            }

            if(distance[i] < min_distance && traversed[i] == false)
            {
                min_distance = distance[i];
                min_element_index = i;
            }
        }

        current = min_element_index; // next element to check is the least distant element from source
        traversed[current] = true;
    }

    current = target;
    int i = 0;
    while(current != -1)
    {
        path[i++] = g->nos[current];
        current = previous[current];
    }
    // we now have the path in reverse order

    // count the path nodes in the path
    int path_count = 0;
    while(path[path_count])
    {
        path_count++;
    }

    if(path_count == 0)
    {
        *n = 0;
        return NULL;
    }
    else
    {
        *n = path_count;
    }

    // reverse the path
    no_grafo **result_path = (no_grafo **)malloc(path_count * sizeof(no_grafo *));
    for(int i = 0; i < path_count; i++)
    {
        result_path[i] = path[path_count - i - 1];
    }
    free(path);

    // free the time_cost_matrix
    for(int i = 0; i < g->tamanho; i++)
    {
        free(transfers_cost_matrix[i]);
    }
    free(transfers_cost_matrix);

    // free helper arrays
    free(distance);
    free(previous);
    free(traversed);

    return result_path;
}


/* acquires updated information and corrects the graph
* each line of the file contains the flight code and the number of seats updated
* parameter ficheiro - name of the file containing the updated information
* parameter g - pointer to the graph to be changed
* parameter *n - size of the edge array returned
* removes from the graph and returns the edges / flights whose places have dropped to zero via an array of pointers to aresta_grafo
* the size of the array must be returned by reference using the ‘n’ argument
* returns NULL on error
*/
typedef struct
{
    char flight_code[15];
    int vacancies;
} update_info;

aresta_grafo **atualiza_lugares(char *ficheiro, grafo *g, int *n)
{
    if(ficheiro == NULL)
        return NULL;

    FILE *f = fopen(ficheiro, "r");
    if(f == NULL)
        return NULL;

    // count how many lines there are in the file
    int num_lines = 0;
    while(!feof(f))
    {
        char ch = fgetc(f);
        if(ch == '\n')
        {
            num_lines++;
        }
    }

    // parse the file with updated flight data
    update_info *updates = (update_info *)calloc(num_lines, sizeof(update_info));
    int updates_idx = 0;

    char *token;
    char str[500] = {0};

    // read line by line into the updates structures

    fseek(f, 0, SEEK_SET);
    while(fgets(str, 500 * sizeof(char), f) != NULL)
    {
        // make it a null terminated string
        str[strlen(str) - 1] = '\0';

        // parse the flight code
        token = strtok(str, ",");
        if(!token)
            break;
        strcpy(updates[updates_idx].flight_code, token);

        token = strtok(NULL, ",");
        updates[updates_idx].vacancies = atoi(token);
        updates_idx++;
    }

    int removed_edges_idx = 0;
    aresta_grafo **removed_edges = (aresta_grafo **)calloc(num_lines, sizeof(aresta_grafo *));

    // search the graph for the edges corresponding to flight numbers
    // and update the vacancies in them, remove the edges if they reach zero vacancies
    for(int i = 0; i < num_lines; i++)
    {
        int edge_index;
        no_grafo *origin_node = encontra_voo(g, updates[i].flight_code, &edge_index);
        if(!origin_node)
        {
            continue;
        }
        aresta_grafo *selected_edge = origin_node->arestas[edge_index];
        selected_edge->lugares = updates[i].vacancies;

        // pop that edge if it has no vacancies
        if(selected_edge->lugares == 0)
        {
            int new_arestas_idx = 0;
            aresta_grafo **new_arestas = (aresta_grafo **)calloc(origin_node->tamanho - 1, sizeof(aresta_grafo *));
            // copy the rest of the edges to the new edges array
            for(int j = 0; j < origin_node->tamanho; j++)
            {
                if(origin_node->arestas[j] != selected_edge)
                {
                    new_arestas[new_arestas_idx++] = origin_node->arestas[j];
                }
            }
            free(origin_node->arestas);
            origin_node->arestas = new_arestas;
            origin_node->tamanho--;
            removed_edges[removed_edges_idx++] = selected_edge;
        }
    }

    // re-adjust the removed_edges array and return the results
    removed_edges = (aresta_grafo **)realloc(removed_edges, removed_edges_idx * sizeof(aresta_grafo *));
    *n = removed_edges_idx;
    fclose(f);
    free(updates);
    return removed_edges;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if(nome_ficheiro == NULL)
    {
            return NULL;
    }

    FILE *f = fopen(nome_ficheiro, "r");
    if(f == NULL)
    {
            return NULL;
    }

    grafo *g = grafo_novo();
    if(g == NULL)
    {
            fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, companhia[4] = {0};
    int lugares = 0;
    double preco = 0;
    struct tm partida, chegada;

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while(fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ",");
        if(!token)
            break;
        strcpy(codigo, token);

        token = strtok(NULL, ",");
        strcpy(origem, token);

        token = strtok(NULL, ",");
        strcpy(destino, token);

        token = strtok(NULL, ",");
        partida.tm_year = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        partida.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_min = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_year = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        chegada.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_min = atoi(token);

        token = strtok(NULL, ",");
        preco = atof(token);

        token = strtok(NULL, ",");
        lugares = atoi(token);

        token = strtok(NULL, ",");
        strcpy(companhia, token);

        // searches the graph for a node with the name of the origin
        no_origem = encontra_no(g, origem);
        // if the node does not yet exist, create it and insert it into the graph
        if(!no_origem)
        {
            no_origem = no_insere(g, origem);
            if(!no_origem)
            {
                    fclose(f);
                return NULL;
            }
        }
        // search the graph for a node with the name of the destination
        no_destino = encontra_no(g, destino);

        // if the node does not yet exist, create it and insert it into the graph
        if(!no_destino)
        {
            no_destino = no_insere(g, destino);

            if(!no_destino)
            {
                    fclose(f);
                return NULL;
            }
        }

        if(existe_aresta(no_origem, no_destino, codigo) == 0)
        {

            ret = cria_aresta(no_origem, no_destino, codigo, companhia, partida, chegada, (float)preco, lugares);

            if(ret == -1)
            {
                    fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}
