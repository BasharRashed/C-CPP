#ifndef _MARKOV_CHAIN_H
#define _MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

//Don't change the macros!
#define ALLOCATION_ERROR_MESSAGE "Allocation failure: Failed to allocate"\
         "new memory\n"


/***************************/
/*   insert typedefs here  */
/***************************/
typedef void (*print_func)(const void *data);
typedef int (*comp_func)(const void *data1, const void *data2);
typedef void (*free_func)(void *data);
typedef void *(*copy_func)(const void *data);
typedef bool (*is_last_func)(const void *data);

/***************************/
/*        STRUCTS          */
/***************************/

typedef struct MarkovNode {
    void *data;
    struct MarkovNodeFrequency *frequency_list;
    int freq_list_size;
    /**
     * @param is_end_of_sentence is 1 when it has a dot.
     * and 0 if it doesn't.
 */
    int is_end_of_sentence;
    // any other fields you need
} MarkovNode;

typedef struct MarkovNodeFrequency {
    struct MarkovNode *markov_node;
    int frequency;
    // any other fields you need
} MarkovNodeFrequency;

/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain {
    LinkedList *database;

    // It is recommended to declare the function pointers using typedefs
    print_func print_func;

    comp_func comp_func;

    free_func free_data;

    copy_func copy_func;

    is_last_func is_last;
} MarkovChain;

/**
 * Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database(MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return its node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return node wrapping given data_ptr in given chain's database
 */
Node *add_to_database(MarkovChain *markov_chain, void *data_ptr);

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update its frequency value.
 * @param first_node
 * @param second_node
 * @return success/failure: 0 if the process was successful, 1 if in
 * case of allocation error.
 */
int add_node_to_frequency_list(MarkovNode *first_node,
                               MarkovNode *second_node);

/**
 * Free markov_chain and all of it's content from memory
 * @param chain_ptr markov_chain to free
 */
void free_database(MarkovChain **chain_ptr);

/**
 * Get one random markov node from the given markov_chain's database.
 * @param markov_chain
 * @return MarkovNode of the chosen state that is not a "last state"
 * in sequence.
 */
MarkovNode *get_first_random_node(MarkovChain *markov_chain);

/**
 * Choose the next node, by its occurrence frequency in current node.
 * @param cur_markov_node MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node(MarkovNode *cur_markov_node);

/**
 * Receive markov_chain, generate and print random sequences out of it. The
 * sequence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with, if NULL- choose a
 * random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence(MarkovChain *markov_chain,
                              MarkovNode *first_node, int max_length);

#endif /* MARKOV_CHAIN_H */
