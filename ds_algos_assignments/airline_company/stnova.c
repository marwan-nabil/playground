/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stnova.h"

/****************************************************/
/****************************************************/
/*               hash table utilities               */
/****************************************************/

unsigned long hash_function(char *key, int hash_table_capacity)
{
    int key_length = strlen(key);
    unsigned long hash = 7;

    for (int i = 0; i < key_length; i++)
    {
        hash += (int)key[i];
    }

    return hash % hash_table_capacity;
}

unsigned long probe_function(int probe_index, int number_of_trials, int hash_table_capacity)
{
    return (probe_index + number_of_trials * number_of_trials) % hash_table_capacity;
}

cities_index *new_cities_index(int hash_table_capacity, hash_function_type *hash_function, probe_function_type *probe_function)
{
    if (hash_function == NULL || probe_function == NULL)
    {
        return NULL;
    }

    cities_index *index = (cities_index *)malloc(sizeof(cities_index));
    if (index == NULL)
    {
        return NULL;
    }

    index->hash_table_capacity = hash_table_capacity;
    index->hash_function = hash_function;
    index->probe_function = probe_function;
    index->number_of_elements = 0;

    index->cell_states = (int *)malloc(index->hash_table_capacity * sizeof(int));
    if (index->cell_states == NULL)
    {
        return NULL;
    }
    memset(index->cell_states, 0, index->hash_table_capacity * sizeof(int));

    index->cells = (city **)malloc(index->hash_table_capacity * sizeof(city *));
    if (index->cells == NULL)
    {
        return NULL;
    }
    memset(index->cells, 0, index->hash_table_capacity * sizeof(city *));

    return index;
}

flights_index *new_flights_index(int hash_table_capacity, hash_function_type *hash_function, probe_function_type *probe_function)
{
    if (hash_function == NULL || probe_function == NULL)
    {
        return NULL;
    }

    flights_index *index = (flights_index *)malloc(sizeof(flights_index));
    if (index == NULL)
    {
        return NULL;
    }

    index->hash_table_capacity = hash_table_capacity;
    index->hash_function = hash_function;
    index->probe_function = probe_function;
    index->number_of_elements = 0;

    index->cell_states = (int *)malloc(index->hash_table_capacity * sizeof(int));
    if (index->cell_states == NULL)
    {
        return NULL;
    }
    memset(index->cell_states, 0, index->hash_table_capacity * sizeof(int));

    index->cells = (flight **)malloc(index->hash_table_capacity * sizeof(flight *));
    if (index->cells == NULL)
    {
        return NULL;
    }
    memset(index->cells, 0, index->hash_table_capacity * sizeof(flight *));

    return index;
}

int add_to_cities_index(cities_index *index, city *new_city)
{
    if (!index || !new_city)
    {
        return -1;
    }

    // calculate the hash to get the initial position
    int position = index->hash_function(new_city->city_name, index->hash_table_capacity);

    // use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->city_name, new_city->city_name) == 0)
            {
                // city already in the table, return it's position
                return position;
            }
            else
            {
                // another city in this cell, probe for a different hash
            }
        }
        else  // cell is empty
        {
            index->cells[position] = new_city;
            index->cell_states[position] = 1;
            index->number_of_elements++;
            return position;
        }
    }
    return -1; // couldn't add the city to the index after all trials
}

int add_to_flights_index(flights_index *index, flight *new_flight)
{
    if (!index || !new_flight)
    {
        return -1;
    }

    // calculate the hash to get the initial position
    int position = index->hash_function(new_flight->flight_code, index->hash_table_capacity);

    // use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->flight_code, new_flight->flight_code) == 0)
            {
                // flight already in the table, return it's position
                return position;
            }
            else
            {
                // another flight in this cell, probe for a different hash
            }
        }
        else  // cell is empty
        {
            index->cells[position] = new_flight;
            index->cell_states[position] = 1;
            index->number_of_elements++;
            return position;
        }
    }
    return -1; // couldn't add the flight to the index after all trials
}

int remove_from_cities_index(cities_index *index, char *city_to_remove)
{
    if (!index || !city_to_remove)
    {
        return -1;
    }

    // calculate hash value
    int position = index->hash_function(city_to_remove, index->hash_table_capacity);

    // use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->city_name, city_to_remove) == 0)
            {
                // we found the city, remove it
                index->cell_states[position] = 0;
                index->cells[position] = NULL;
                index->number_of_elements--;
                return 0;
            }
        }
    }
    return -1; // city not found
}

int remove_from_flights_index(flights_index *index, char *flight_to_remove)
{
    if (!index || !flight_to_remove)
    {
        return -1;
    }

    // calculate hash value
    int position = index->hash_function(flight_to_remove, index->hash_table_capacity);

    // use the probing function to get the real index and deal with collisions
    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->flight_code, flight_to_remove) == 0)
            {
                // we found the flight, remove it
                index->cell_states[position] = 0;
                index->cells[position] = NULL;
                index->number_of_elements--;
                return 0;
            }
        }
    }
    return -1; // flight not found
}

void free_cities_index(cities_index *index)
{
    if (index == NULL)
    {
        return;
    }

    free(index->cells);
    free(index->cell_states);
    free(index);
}

void free_flights_index(flights_index *index)
{
    if (index == NULL)
    {
        return;
    }

    free(index->cells);
    free(index->cell_states);
    free(index);
}

int exists_in_cities_index(cities_index *index, char *city_name)
{
    if (!city_name || !index)
    {
        return -1;
    }

    int position = index->hash_function(city_name, index->hash_table_capacity);

    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->city_name, city_name) == 0)
            {
                // we found the node, return it
                return position;
            }
        }
    }
    return -1;
}

int exists_in_flights_index(flights_index *index, char *flight_code)
{
    if (!flight_code || !index)
    {
        return -1;
    }

    int position = index->hash_function(flight_code, index->hash_table_capacity);

    int max_probing_trials = 3000;
    for (int trials = 0; trials < max_probing_trials; trials++)
    {
        position = index->probe_function(position, trials, index->hash_table_capacity);

        if(index->cell_states[position] == 1) // cell not empty
        {
            if(strcmp(index->cells[position]->flight_code, flight_code) == 0)
            {
                // we found the node, return it
                return position;
            }
        }
    }
    return -1;
}

city *get_from_cities_index(cities_index *index, char *city_name)
{
    city *result = NULL;
    int index_position = exists_in_cities_index(index, city_name);
    if (index_position == -1) // not found in index
    {
        return NULL;
    }
    result = index->cells[index_position];
    return result;
}

flight *get_from_flights_index(flights_index *index, char *flight_code)
{
    flight *result = NULL;
    int index_position = exists_in_flights_index(index, flight_code);
    if (index_position == -1) // not found in index
    {
        return NULL;
    }
    result = index->cells[index_position];
    return result;
}

/****************************************************/
/****************************************************/

estrutura *st_nova()
{
    estrutura *database = (estrutura *)calloc(1, sizeof(estrutura));
    return database;
}

int st_importa_grafo(estrutura *database, grafo *graph)
{
    if(!database || !graph)
    {
        return -1;
    }

    database->number_of_cities = graph->tamanho;
    database->cities_table = (city *)calloc(database->number_of_cities, sizeof(city));
    database->cities_index = new_cities_index(database->number_of_cities, hash_function, probe_function);

    database->number_of_flights = 0;

    // loop over all cities in the graph and populate the cities table in the database
    for (int i = 0; i < graph->tamanho; i++)
    {
        no_grafo *graph_node = graph->nos[i];
        city *database_city = &database->cities_table[i];

        database_city->city_name = graph_node->cidade;
        database_city->departing_flights_capacity = graph_node->tamanho; // number of flights departing from this node
        database->number_of_flights += database_city->departing_flights_capacity;

        // fill the departing flights array in the database_city
        database_city->departing_flights = (char **)calloc(database_city->departing_flights_capacity, sizeof(char *));
        for (int j = 0; j < database_city->departing_flights_capacity; j++)
        {
            database_city->departing_flights[j] = graph_node->arestas[j]->codigo;
        }

        // add the database city to the cities index
        add_to_cities_index(database->cities_index, database_city);
    }

    // create the flights table and index, now that we know how many flights there are
    database->flights_table = (flight *)calloc(database->number_of_flights, sizeof(flight));
    database->flights_index = new_flights_index(database->number_of_flights, hash_function, probe_function);

    // loop over all flights (edges) in the graph to populate the flights table and index
    int flights_table_idx = 0;
    for (int i = 0; i < graph->tamanho; i++)
    {
        no_grafo *graph_node = graph->nos[i];
        for (int j = 0; j < graph_node->tamanho; j++)
        {
            aresta_grafo *graph_edge = graph_node->arestas[j];
            flight *database_flight = &database->flights_table[flights_table_idx++];

            database_flight->flight_code = graph_edge->codigo;
            database_flight->company_name = graph_edge->companhia;
            database_flight->origin_city = graph_node->cidade;
            database_flight->departure_time = graph_edge->partida;
            database_flight->destination_city = graph_edge->destino->cidade;
            database_flight->arrival_time = graph_edge->chegada;
            database_flight->price = graph_edge->preco;
            database_flight->number_of_empty_seats = graph_edge->lugares;

            // add the flight to the flights index
            add_to_flights_index(database->flights_index, database_flight);
        }
    }
    return 0;
}

char *st_pesquisa(estrutura *database, char *origin_city_name, char *destination_city_name)
{
    city *database_origin_city = get_from_cities_index(database->cities_index, origin_city_name);
    city *database_destination_city = get_from_cities_index(database->cities_index, destination_city_name);

    if(!database_origin_city || !database_destination_city)
    {
        return NULL;
    }

    // get the flight from origin to destination with the least price
    double least_price = INFINITY;
    flight *least_price_flight = NULL;
    for(int i = 0; i < database_origin_city->departing_flights_capacity; i++)
    {
        flight *debug_flight = NULL;
        if((strcmp(database_origin_city->departing_flights[i], "N819NWATLSLC") == 0))
        {
            debug_flight = get_from_flights_index(database->flights_index, database_origin_city->departing_flights[i]);
        }
        flight *current_flight = get_from_flights_index(database->flights_index, database_origin_city->departing_flights[i]);
        if (current_flight && strcmp(current_flight->destination_city, database_destination_city->city_name) == 0)
        {
            // this is a matching flight, check it's price
            if (current_flight->price < least_price)
            {
                least_price = current_flight->price;
                least_price_flight = current_flight;
            }
        }
    }
    
    if(!least_price_flight)
    {
        NULL;
    }

    return least_price_flight->flight_code;
}

int st_apaga(estrutura *database)
{
    if(!database)
    {
        return -1;
    }

    // delete the cities table and any allocations made for it
    for (int i = 0; i < database->number_of_cities; i++)
    {
        city *database_city = &database->cities_table[i];
        free(database_city->departing_flights);
    }
    free(database->cities_table);
    free_cities_index(database->cities_index);
    
    // delete the flights table and any allocations made for it
    free(database->flights_table);
    free_flights_index(database->flights_index);

    // free the database memory
    free(database);
    return 0;
}

