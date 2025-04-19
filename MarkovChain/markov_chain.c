#include "markov_chain.h"
#include "string.h"
/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */

#define DB_ALLOC_FAIL "failed allocate for add to database."
#define FL_ALLOC_FAIL "failed allocate for add to frequency list."
#define REALLOC_FAIL "failed reallocation for add to frequency list."
int get_random_number(int max_number)
{
    return rand() % max_number;
}

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr){
    Node *curr_node = markov_chain->database->first;
    if(curr_node!=NULL) {
        for (; curr_node != NULL; curr_node = curr_node->next) {
            if (strcmp(curr_node->data->data, data_ptr) == 0) {
                return curr_node;
            }
        }
    }
    return NULL;
}

Node* add_to_database(MarkovChain *markov_chain, char *data_ptr) {
    Node *existing_node = get_node_from_database(markov_chain, data_ptr);
    if (existing_node) {
        return existing_node;
    }
    MarkovNodeFrequency *list_ptr = NULL;
    MarkovNode *new_markov_ptr = malloc(sizeof(MarkovNode));
    if (new_markov_ptr == NULL) {
        fprintf(stdout,DB_ALLOC_FAIL);
        return NULL;
    }
    new_markov_ptr->data = data_ptr;
    if(new_markov_ptr->data==NULL){
        free(new_markov_ptr);
        return NULL;
    }
    new_markov_ptr->frequency_list = list_ptr;

    if (add(markov_chain->database, new_markov_ptr) != 0) {
        free(new_markov_ptr);
        return NULL;
    }
    return markov_chain->database->last;
}

bool is_in_freq_list(MarkovNode *first_node, MarkovNode *second_node){
    MarkovNodeFrequency *list = first_node->frequency_list;
    for (int i = 0; i < first_node->freq_list_size; ++i) {
        if(list[i].markov_node==second_node){
            return true;
        }
    }
    return false;
}

int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode *second_node)
{
    if (first_node->frequency_list == NULL) {
        first_node->frequency_list = malloc(sizeof(MarkovNodeFrequency) * 1);
        if (first_node->frequency_list == NULL) {
            fprintf(stdout,FL_ALLOC_FAIL);
            return 1;
        }
        first_node->freq_list_size = 0;
    }

    if (is_in_freq_list(first_node,second_node)){
        MarkovNodeFrequency *list = first_node->frequency_list;
        for (int i = 0; i < first_node->freq_list_size; ++i) {
            if(list[i].markov_node==second_node){
                list[i].frequency +=1;
                return 0;
            }
        }
    }
    else {
        MarkovNodeFrequency *temp =
                realloc(first_node->frequency_list,
                        (first_node->freq_list_size + 1)
                        * sizeof(MarkovNodeFrequency));
        if (temp != NULL) {
            first_node->frequency_list = temp;
            first_node->frequency_list[first_node->freq_list_size]
            .markov_node = second_node;
            first_node->frequency_list[first_node->freq_list_size]
            .frequency = 1;
            first_node->freq_list_size++;
            return 0;
        } else {
            fprintf(stdout, REALLOC_FAIL);
            return 1;
        }
    }
    return 1;
}

void free_database(MarkovChain **ptr_chain) {
    if (ptr_chain == NULL || *ptr_chain == NULL) {
        return;
    }
    MarkovChain *chain = *ptr_chain;
    Node *curr_node = chain->database->first;
    while (curr_node != NULL) {
        if (curr_node->data->frequency_list != NULL) {
            free(curr_node->data->frequency_list);
        }
        if (curr_node->data->data != NULL) {
            free(curr_node->data->data);
        }
        free(curr_node->data);
        Node *temp = curr_node;
        curr_node = curr_node->next;
        free(temp);
    }
    free(chain->database);
    free(chain);
    *ptr_chain = NULL;
}




MarkovNode* get_first_random_node(MarkovChain *markov_chain){
    if (!markov_chain || !markov_chain->database
    || markov_chain->database->size == 0) {
        return NULL;
    }
    int random_num = get_random_number(markov_chain->database->size);
    Node *curr_node = markov_chain->database->first;

    while(true) {
        while (random_num > 0) {
            curr_node = curr_node->next;
            random_num--;
        }
        if(curr_node->data->is_end_of_sentence==1){
            random_num = get_random_number(markov_chain->database->size);
            curr_node = markov_chain->database->first;
        }
        else{
            break;
        }
    }
    return curr_node->data;
}

MarkovNode* get_next_random_node(MarkovNode *cur_markov_node){
    if(cur_markov_node->freq_list_size==0){
        return NULL;
    }

    //total frequency to calculate weighted probability
    int total_freq = 0;
    for(int i=0;i<cur_markov_node->freq_list_size;i++){
        total_freq += cur_markov_node->frequency_list[i].frequency;
    }

    int random_num = get_random_number(total_freq)+1;
    int curr_freq = 0;
    for(int i=0;i<cur_markov_node->freq_list_size;i++){
        curr_freq += cur_markov_node->frequency_list[i].frequency;
        if(random_num<=curr_freq){
            return cur_markov_node->frequency_list[i].markov_node;
        }
    }
    return NULL;
}

void generate_tweet(MarkovNode *first_node, int max_length){
    if (first_node == NULL) {
        return;
    }
    MarkovNode *curr_node = first_node;
    int words_counter = 0;

    while (curr_node && words_counter < max_length) {
        printf("%s", curr_node->data);
        words_counter++;
        if (curr_node->is_end_of_sentence || words_counter == max_length) {
            break;
        }
        printf(" ");
        curr_node = get_next_random_node(curr_node);
    }

}