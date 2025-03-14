#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024
#define FOUR_ARGUMENTS 5
#define ONE_ARGUMENT_TEST 2
#define TEST_ERR1 "The given command is invalid.\n"
#define TEST_ERR2 "The given shift value is invalid.\n"
#define TEST_ERR3 "The given file is invalid.\n"
#define TEST_ERR4 "Usage: cipher test\n"
#define COMMAND argv[1]
#define SHIFT_VALUE argv[2]
#define INPUT_FILE_DIR argv[3]
#define OUTPUT_FILE_DIR argv[4]
#define TEST_NUMBERS 0

// your code goes here
bool is_integer(char str[]);
bool four_args(char *argv[]);
bool one_args(char *argv[]);

int main (int argc, char *argv[])
{
    // 4 argument case
    if(argc == FOUR_ARGUMENTS)
    {
        return four_args(argv);
    }
    // 1 argument case
    else if (argc == ONE_ARGUMENT_TEST) {
        return one_args(argv);
    }
    else
    {
        fprintf(stderr,"The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;
    }
    }

bool is_integer(char str[]){
    // function that checks if str[] can be an int
    bool isint = true;
    if (str[0]=='-'){
        str++;
    }
    for (int i =0; str[i] != '\0';i++){
        if (str[i] < '0' || '9'< str[i]){
            isint = false;
        }
    }
    return isint;
}
bool four_args(char *argv[]){
    if ((strcmp(COMMAND,"cipher")!=0) && strcmp(COMMAND,"decipher")!=0) {
        fprintf(stderr,TEST_ERR1);
        return EXIT_FAILURE;
    }
    else if(!is_integer(SHIFT_VALUE)){
        fprintf(stderr,TEST_ERR2);
        return EXIT_FAILURE;
    }
    else {
        FILE *input = fopen(INPUT_FILE_DIR,"r");
        if (input == NULL){
            fprintf(stderr,TEST_ERR3);
            return EXIT_FAILURE;
        }
        FILE *output = fopen(OUTPUT_FILE_DIR,"w");
        if (output == NULL){
            fprintf(stderr,TEST_ERR3);
            return EXIT_FAILURE;
        }
        char line[MAX_LINE_LENGTH + 1];
        long k = strtol(SHIFT_VALUE,NULL,10);
        if(strcmp(COMMAND,"cipher")==0){
            while(fgets(line,sizeof(line),input)){
                cipher(line,k);
                fputs(line,output);
            }
            fclose(input);
            fclose(output);
            return EXIT_SUCCESS;
        }
        else if (strcmp(COMMAND,"decipher")==0) {
            while (fgets(line, sizeof(line), input)) {
                decipher(line, k);
                fputs(line, output);
            }
            fclose(input);
            fclose(output);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

bool one_args(char *argv[]){
    int counter = 0;
    if (strcmp(COMMAND, "test") != 0) {
        fprintf(stderr, TEST_ERR4);
        return EXIT_FAILURE;
    }
    else
    {
        if (test_cipher_non_cyclic_lower_case_positive_k()){
            counter++;
        }
        if(test_cipher_cyclic_lower_case_special_char_positive_k()){
            counter++;
        }
        if(test_cipher_non_cyclic_lower_case_special_char_negative_k ()){
            counter++;
        }
        if(test_cipher_cyclic_lower_case_negative_k ()){
            counter++;
        }
        if(test_cipher_cyclic_upper_case_positive_k ()){
            counter++;
        }
        if(test_decipher_non_cyclic_lower_case_positive_k ()){
            counter++;
        }
        if(test_decipher_cyclic_lower_case_special_char_positive_k ()){
            counter++;
        }
        if(test_decipher_non_cyclic_lower_case_special_char_negative_k ()){
            counter++;
        }
        if(test_decipher_cyclic_lower_case_negative_k ()){
            counter++;
        }
        if(test_decipher_cyclic_upper_case_positive_k ()){
            counter++;
        }
    }
    if (counter == TEST_NUMBERS){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

