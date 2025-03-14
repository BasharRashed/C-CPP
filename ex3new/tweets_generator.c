//Don't change the macros!
#include <stdio.h>
#include "markov_chain.h"
#include "linked_list.h"
#include "string.h"
#include <limits.h>
#define ALL_FILE 4
#define PART_OF_FILE 5
#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"
#define LC_MALLOC_FAIL "failed allocation for line copy."
#define MC_MALLOC_FAIL "failed allocation for markov chain."
#define LL_MALLOC_FAIL "failed allocation for linked list."
#define FILE_PATH argv[3]
#define TWEETS_TO_CREATE argv[2]
#define SEED argv[1]
#define WORDS_TO_READ argv[4]
#define MAX_LINE 1000
#define MAX_LENGTH 20
#define END_OF_LINE 1
#define NOT_END_OF_LINE 0
#define BASE 10
#define DELIMITERS " \n\t\r"
int fill_database(FILE *fp,int words_to_read,MarkovChain *markov_chain);
bool is_end_of_sentence(const void *word);
void print_funct(const void *data);
void* copy_funct(const void *data);
int cmp_funct(const void *data1,const void *data2);
void free_funct (void *data);


int main (int argc, char *argv[]){
    long seed = strtol(SEED,NULL,BASE);
    long tweets_to_create = strtol(TWEETS_TO_CREATE,NULL,BASE);
    long words_to_read = 0;
    srand(seed);
    if(argc != ALL_FILE && argc != PART_OF_FILE) {
        fprintf(stdout,NUM_ARGS_ERROR);
        return EXIT_FAILURE;}
    else{
        if (argc == ALL_FILE){
            words_to_read = INT_MAX;
        }
        else{
            words_to_read = strtol(WORDS_TO_READ,NULL,BASE);
        }
        FILE *fp = fopen(FILE_PATH,"r");
        if(fp == NULL){
            fprintf(stdout,FILE_PATH_ERROR);
            return EXIT_FAILURE;
        }
        MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
        if(markov_chain!=NULL){
            LinkedList *linked_list = malloc(sizeof(LinkedList));
            if(linked_list!=NULL) {
                markov_chain->database = linked_list;
                linked_list->first = NULL;
                linked_list->last = NULL;
                linked_list->size = 0;
                markov_chain->copy_func =copy_funct;
                markov_chain->free_data = free_funct;
                markov_chain->print_func = print_funct;
                markov_chain->comp_func = cmp_funct;
                markov_chain->is_last = is_end_of_sentence;
                fill_database(fp, words_to_read, markov_chain);
                fclose(fp);
            }
            else{
                fprintf(stdout,MC_MALLOC_FAIL);
                return EXIT_FAILURE;
            }}
        else{
            fprintf(stdout,LL_MALLOC_FAIL);
            return EXIT_FAILURE;
        }
        for(int i=0;i<tweets_to_create;i++){
            printf("Tweet %d: ", i + 1);
            MarkovNode *first_node = get_first_random_node(markov_chain);
            if (!first_node) {
                continue;}
            generate_random_sequence(markov_chain,first_node, MAX_LENGTH);
            printf("\n");}
        free_database(&markov_chain);
        return EXIT_SUCCESS;
    }}

bool is_end_of_sentence(const void *word){
    char *w = (char*) word;
    size_t len = strlen(word);
    if (len> 0 && w[len - 1] == '.') {
        return true;
    }
    return false;
}

int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain) {
    if (fp == NULL) {
        fprintf(stdout, FILE_PATH_ERROR);
        return 1;}
    char line[MAX_LINE];
    char *prev_word = NULL;
    int words_read = 0;
    while (fgets(line, sizeof(line), fp)
           && words_read <words_to_read) {
        char *line_copy = malloc(strlen(line) + 1);
        if (!line_copy) {
            fprintf(stdout,LC_MALLOC_FAIL);
            return 1;}
        strcpy(line_copy, line);
        char *word = strtok(line_copy,DELIMITERS);
        while (word && words_read < words_to_read) {
            Node *existing_node = get_node_from_database(markov_chain,word);
//            char *word_copy = NULL;
            if (!existing_node) {
//                word_copy = malloc(strlen(word) + 1);
//                if (!word_copy) {
//                    fprintf(stdout,ALLOCATION_ERROR_MESSAGE);
//                    free(line_copy);
//                    return 1;}
//                strcpy(word_copy, word);
                existing_node = add_to_database(markov_chain, word);
                if (!existing_node) {
                    free(word);
                    free(line_copy);
                    return 1;
                }}
            if (prev_word != NULL) {
                Node *prev_node = get_node_from_database(markov_chain,
                                                         prev_word);
                if (prev_node && prev_node->data->is_end_of_sentence == 0) {
                    MarkovNode *prev_markov_node = prev_node->data;
                    MarkovNode *new_markov_node = existing_node->data;
                    add_node_to_frequency_list(prev_markov_node,
                                               new_markov_node);}}
            MarkovNode *current_markov_node = existing_node->data;
            current_markov_node->is_end_of_sentence =
                    markov_chain->is_last(word)? END_OF_LINE:NOT_END_OF_LINE;
            prev_word = existing_node->data->data;
            word = strtok(NULL, DELIMITERS);
            words_read++;}
        free(line_copy);
        prev_word = NULL;}
    return 0;
}

void print_funct(const void *data) {
    printf("%s", (char *)data);
}
void* copy_funct(const void *data) {
    size_t len = strlen((char *)data);
    char *copy = malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, data);
    return copy;
}
int cmp_funct(const void *data1,const void *data2) {
    return strcmp((const char *)data1, (const char *)data2);
}
void free_funct(void *data) {
    free(data);
}


