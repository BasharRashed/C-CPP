#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define TWO_ARGUMENTS 3

#define NUM_ARGS_ERROR "Usage: invalid number of arguments"


/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {
    {13, 4},
    {85, 17},
    {95, 67},
    {97, 58},
    {66, 89},
    {87, 31},
    {57, 83},
    {91, 25},
    {28, 50},
    {35, 11},
    {8, 30},
    {41, 62},
    {81, 43},
    {69, 32},
    {20, 39},
    {33, 70},
    {79, 99},
    {23, 76},
    {15, 47},
    {61, 14}
};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to; // cell which ladder leads to, if there is one
    int snake_to; // cell which snake leads to, if there is one
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/**
 * allocates memory for cells on the board and initalizes them
 * @param cells Array of pointer to Cell, represents game board
 * @return EXIT_SUCCESS if successful, else EXIT_FAILURE
 */
int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(cells[j]);
            }
            printf(ALLOCATION_ERROR_MESSAGE);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell){i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        } else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

int add_cells_to_database(MarkovChain *markov_chain, Cell *cells[BOARD_SIZE])
{
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        Node *tmp = add_to_database(markov_chain, cells[i]);
        if (tmp == NULL)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int set_nodes_frequencies(MarkovChain *markov_chain, Cell *cells[BOARD_SIZE])
{
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain, cells[i])->data;
        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain,
                                             cells[index_to])->data;
            int res = add_node_to_frequency_list(from_node, to_node);
            if (res == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell *) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain,
                                                 cells[index_to])->data;
                int res = add_node_to_frequency_list(from_node, to_node);
                if (res == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int fill_database_snakes(MarkovChain *markov_chain)
{
    Cell *cells[BOARD_SIZE];
    if (create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    if (add_cells_to_database(markov_chain, cells) == EXIT_FAILURE)
    {
        for (size_t i = 0; i < BOARD_SIZE; i++)
        {
            free(cells[i]);
        }
        return EXIT_FAILURE;
    }

    if(set_nodes_frequencies(markov_chain, cells) == EXIT_FAILURE)
    {
        for (size_t i = 0; i < BOARD_SIZE; i++)
        {
            free(cells[i]);
        }
        return EXIT_FAILURE;
    }

    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */

void print_cell (const void* data);
void* copy_cell (const void* data);
int compare_cells(const void* data1, const void* data2);
void free_cell(void* data);
bool is_cell_end (const void* data);

int main(int argc, char *argv[])
{
    if (argc != TWO_ARGUMENTS) {
        fprintf(stderr, "%s\n", NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }

    long seed = strtol(argv[1], NULL, 10);
    long num_paths = strtol(argv[2], NULL, 10);

    if (num_paths <= 0) {
        return EXIT_FAILURE;
    }

    srand(seed);

    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
    if(markov_chain!=NULL) {
        LinkedList *linked_list = malloc(sizeof(LinkedList));
        if (linked_list != NULL) {
            markov_chain->database = linked_list;
            linked_list->first = NULL;
            linked_list->last = NULL;
            linked_list->size = 0;
            markov_chain->copy_func = copy_cell;
            markov_chain->free_data = free_cell;
            markov_chain->print_func = print_cell;
            markov_chain->comp_func = compare_cells;
            markov_chain->is_last = is_cell_end;
        }
    }
    if (fill_database_snakes(markov_chain) == EXIT_FAILURE) {
        free_database(&markov_chain);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_paths; ++i) {
        printf("Random Walk %d: ", i + 1);
        MarkovNode *start_node = get_node_from_database
                (markov_chain, &(Cell){.number = 1})->data;
        generate_random_sequence(markov_chain,
                                 start_node, MAX_GENERATION_LENGTH);
        printf("\n");
    }

    free_database(&markov_chain);
    return EXIT_SUCCESS;
}

bool is_in_transition(int number){
    for(int i=0; i<NUM_OF_TRANSITIONS;i++){
        if(transitions[i][0] == number){
            return true;
        }
    }
    return false;
}

void print_cell(const void* data) {
    const Cell *cell = (const Cell *)data;

    if(cell->ladder_to == EMPTY && cell->snake_to == EMPTY) {
        if (cell->number != BOARD_SIZE) {
            printf("[%d] ->", cell->number);
        } else {
            printf("[%d]", cell->number);
        }
    }
    else{
        printf("[%d] ", cell->number);
    }
    if (cell->ladder_to != EMPTY) {
        printf("-ladder to->");
    } else if (cell->snake_to != EMPTY) {
        printf("-snake to->");
    }
}

int compare_cells(const void *data1, const void *data2) {
    const Cell *cell1 = (const Cell*)data1;
    const Cell *cell2 = (const Cell*)data2;
    return cell1->number - cell2->number;
}

void free_cell(void *data) {
    free(data);
}

void *copy_cell(const void *data) {
    const Cell *cell = (const Cell *)data;
    Cell *copy = malloc(sizeof(Cell));
    if (!copy) {
        return NULL;
    }
    *copy = *cell;
    return copy;
}

bool is_cell_end(const void *data) {
    const Cell *cell = (const Cell *)data;
    return cell->number == BOARD_SIZE;
}