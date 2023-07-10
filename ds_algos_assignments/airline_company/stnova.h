/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#ifndef _STNOVA_H_
#define _STNOVA_H_

#include <time.h>
#include "grafo.h"

/****************************************************/
/****************************************************/
/*               type definitions                   */
/****************************************************/

typedef struct tm date;
typedef unsigned long hash_function_type(char *key, int hash_table_capacity);
typedef unsigned long probe_function_type(int probe_index, int number_of_trials, int hash_table_capacity);

typedef struct {
    char *city_name;
    char **departing_flights;
    int departing_flights_capacity;
} city;

typedef struct {
    char *flight_code;
    char *company_name;

    char *origin_city;
    date departure_time;

    char *destination_city;
    date arrival_time;

    double price;
    int number_of_empty_seats;
} flight;

typedef struct {
    hash_function_type  *hash_function;
    probe_function_type *probe_function;
    int hash_table_capacity;
    int number_of_elements;

    city **cells;
    int *cell_states; // 0: empty, 1: full
} cities_index;

typedef struct {
    hash_function_type  *hash_function;
    probe_function_type *probe_function;
    int hash_table_capacity;
    int number_of_elements;

    flight **cells;
    int *cell_states; // 0: empty, 1: full
} flights_index;

typedef struct
{
    city *cities_table;
    cities_index *cities_index;
    int number_of_cities;

    flight *flights_table;
    flights_index *flights_index;
    int number_of_flights;
} estrutura;

/****************************************************/
/****************************************************/

/****************************************************/
/****************************************************/
/*               hash table utilities               */
/****************************************************/

cities_index *new_cities_index(int hash_table_capacity, hash_function_type *hash_function, probe_function_type *probe_function);
flights_index *new_flights_index(int hash_table_capacity, hash_function_type *hash_function, probe_function_type *probe_function);

int add_to_cities_index(cities_index *index, city *new_city);
int add_to_flights_index(flights_index *index, flight *new_flight);

int remove_from_cities_index(cities_index *index, char *city_to_remove);
int remove_from_flights_index(flights_index *index, char *flight_to_remove);

void free_cities_index(cities_index *index);
void free_flights_index(flights_index *index);

int exists_in_cities_index(cities_index *index, char *city_name);
int exists_in_flights_index(flights_index *index, char *flight_code);

city   *get_from_cities_index(cities_index *index, char *city_name);
flight *get_from_flights_index(flights_index *index, char *flight_code);

/****************************************************/
/****************************************************/


/*
*  creates and initializes the structure created
* returns the structure if successful or NULL otherwise
*/
estrutura *st_nova();

/*
* imports all the contents of graph g into the new access format
* parameter st - pointer to the structure created
* parameter g - pointer to the graph
* returns 0 if successful or -1 otherwise
*/
int st_importa_grafo(estrutura *st, grafo *g);

/* obtains the flight code of the origin-destination pair with the lowest price
* the returned instance must be kept, i.e., a copy of it must be left in the respective ‘st’ element
* NOTE: this function will be evaluated by the runtime!
* parameter st - pointer to the structure
* parameter origem - name of the city of origin of the flights to be searched
* parameter destino - name of the destination city of the flights to be searched
* returns the flight code or in case of failure, returns NULL
*/
char *st_pesquisa(estrutura *database, char *origin_city_name, char *destination_city_name);

/*
*  eliminates all instances present in the st structure and deallocates all the memory in the same structure
* NOTE: this function will be evaluated by the runtime!
* parameter st - pointer to the structure
* returns 0 if successful and -1 if an error occurs
*/
int st_apaga(estrutura *database);


#endif
