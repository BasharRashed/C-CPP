#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_INPUT 60
#define MAX_INFO_INPUT 21
#define ONE_ARGUMENT 2
#define FIRST_ARGUMENT argv[1]
#define BY_DURATION "by_duration"
#define BY_DISTANCE "by_distance"
#define BY_NAME "by_name"
#define TEST "test"
#define USAGE_ERR "Usage: Enter (by_duration"\
"by_distance, by_name,test)\n"
#define NUM_ERR "Error: input must be a valid number.\n"
#define NUM_ERR2 "Error: Number of lines "\
"should be a positive integer\n"
#define NAME_ERR "Error: bus name should "\
"contains only digits and small chars\n"
#define DURATION_ERR "Error: duration should be "\
"an integer between 10 and 100 (includes)\n"
#define DISTANCE_ERROR "Error: distance should be "\
"an integer between 0 and 1000 (includes)\n"


#define TEST1_PASS "TEST 1 PASSED: "\
"The array is sorted by distance\n"
#define TEST2_PASS "TEST 2 PASSED: "\
"The array has the same items after sorting\n"
#define TEST3_PASS "TEST 3 PASSED: "\
"The array is sorted by duration\n"
#define TEST4_PASS "TEST 4 PASSED: "\
"The array has the same items after sorting\n"
#define TEST5_PASS "TEST 5 PASSED: "\
"The array is sorted by name\n"
#define TEST6_PASS "TEST 6 PASSED: "\
"The array has the same items after sorting\n"


#define TEST1_FAIL "TEST 1 FAILED: "\
"Not sorted by distance\n"
#define TEST2_FAIL "TEST 2 FAILED: "\
"Bus Lines changed after sorting by distance\n"
#define TEST3_FAIL "TEST 3 FAILED: "\
"Not sorted by duration\n"
#define TEST4_FAIL "TEST 4 FAILED: "\
"Bus Lines changed after sorting by duration\n"
#define TEST5_FAIL "TEST 5 FAILED: "\
"Not sorted by name\n"
#define TEST6_FAIL "TEST 6 FAILED: "\
"Bus Lines changed after sorting by name\n"
#define SIX_PASSED_TESTS 6
#define THREE_ARGS 3
#define FAILED (-1)

typedef enum {
    VALID_INPUT,
    INVALID_NAME,
    INVALID_DURATION,
    INVALID_DISTANCE,
    INVALID_FORMAT
} InputError;
/**
 * TODO add documentation
 */
int num_lines();
BusLine* enter_bus(int number_of_lines);
bool check_name(const char *name);
InputError get_bus_line_input(const char *input, BusLine *busLine);
int tests(const BusLine *start_org,const BusLine *end_org);
int duration();
int distance();
int name();
int test();


/**
 * This function starts the program
 */
int main (int argc, char *argv[])
{
    if (argc == ONE_ARGUMENT){
        if ((strcmp(FIRST_ARGUMENT, BY_DURATION) == 0)) {
            if(duration()){
                return EXIT_SUCCESS;
            }
            else{
                return EXIT_FAILURE;
            }
        }
        else if ((strcmp(FIRST_ARGUMENT, BY_DISTANCE) == 0)) {
            if(distance()){
                return EXIT_SUCCESS;
            }
            else{
                return EXIT_FAILURE;
            }
        }
        else if ((strcmp(FIRST_ARGUMENT, BY_NAME) == 0)) {
            if(name()){
                return EXIT_SUCCESS;
            }
            else{
                return EXIT_FAILURE;
            }
        }
        else if((strcmp(FIRST_ARGUMENT,TEST) == 0)){
            if(test()){
                return EXIT_SUCCESS;
            }
            else{
                return EXIT_FAILURE;
            }
        }
        else{
            fprintf(stdout,USAGE_ERR);
            return EXIT_FAILURE;
        }}
    else{
            fprintf(stdout,USAGE_ERR);
            return EXIT_FAILURE;
        }
}

/**
 * This function works if argv[1] == duration
 */
int duration(){
    int num_of_lines=0;
    do {
        num_of_lines = num_lines();
    } while (num_of_lines == FAILED);
    BusLine *bus_lines = enter_bus(num_of_lines);
    if (bus_lines != NULL) {
        quick_sort(bus_lines, bus_lines + num_of_lines, DURATION);
        for (BusLine *bus = bus_lines; bus < bus_lines + num_of_lines; bus++) {
            printf("%s,%d,%d\n", bus->name, bus->distance, bus->duration);
        }
        free(bus_lines);
        return true;
    } else {
        return false;
    }
}

/**
 * This function works if argv[1] == distance
 */
int distance(){
    int num_of_lines=0;
    do {
        num_of_lines = num_lines();
    } while (num_of_lines == FAILED);
    BusLine *bus_lines = enter_bus(num_of_lines);
    if (bus_lines != NULL) {
        quick_sort(bus_lines, bus_lines + num_of_lines, DISTANCE);
        for (BusLine *bus = bus_lines; bus < bus_lines + num_of_lines; bus++) {
            printf("%s,%d,%d\n", bus->name, bus->distance, bus->duration);
        }
        free(bus_lines);
        return true;
    } else {
        return false;
    }
}

/**
 * This function works if argv[1] == name
 */
int name(){
    int num_of_lines=0;
    do {
        num_of_lines = num_lines();
    } while (num_of_lines == FAILED);
    BusLine *bus_lines = enter_bus(num_of_lines);
    if (bus_lines != NULL) {
        bubble_sort(bus_lines,bus_lines+num_of_lines);
        for (BusLine *bus = bus_lines; bus < bus_lines + num_of_lines; bus++) {
            printf("%s,%d,%d\n", bus->name, bus->distance, bus->duration);
        }
        free(bus_lines);
        return true;
    } else {
        return false;
    }
}

/**
 * This function works if argv[1] == test
 */
int test(){
    int num_of_lines =0;
    do {
        num_of_lines = num_lines();
    } while (num_of_lines == FAILED);
    BusLine *bus_lines = enter_bus(num_of_lines);
    if (bus_lines != NULL) {
        if (tests(bus_lines, bus_lines + num_of_lines) == true) {
            free(bus_lines);
            return true;
        }
    }
    else{
        free(bus_lines);
        return false;
    }
    return false;
}

/**
 * This function takes the number of bus lines
 * returns -1 if not valid entered value
 */
int num_lines() {
    printf("Enter number of lines. Then enter\n");
    char input[MAX_INPUT];
    int number_of_lines = 0;
    char *endptr;
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
        number_of_lines = strtol(input, &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stdout, NUM_ERR);
            return -1;
        }
        if (number_of_lines <= 0) {
            fprintf(stdout, NUM_ERR2);
            return -1;
        }
    }
    return number_of_lines;
}

/**
 * This function returns enum InputError / valid input
 * and is used in entering buses to ensure valid inputting
 */
InputError get_bus_line_input(const char *input, BusLine *busLine) {
    char name[MAX_INFO_INPUT] = "";
    int duration = 0;
    int distance = 0;
    char distance_str[MAX_INFO_INPUT] = "";
    if (sscanf(input, "%20[^,],%20[^,],%d",
               name, distance_str, &duration) != THREE_ARGS) {
        return INVALID_FORMAT;
    }
    if (!check_name(name)) {
        return INVALID_NAME;
    }
    for(size_t i =0;i<strlen(distance_str);i++){
        if(distance_str[i] <'0' || distance_str[i] >'9'){
            return INVALID_DISTANCE;
        }
    }
    distance = strtol(distance_str,NULL,10);
    if (distance < 0 || distance > 1000) {
        return INVALID_DISTANCE;
    }
    if (duration < 10 || duration > 100) {
        return INVALID_DURATION;
    }
    strncpy(busLine->name, name, MAX_INFO_INPUT - 1);
    busLine->name[MAX_INFO_INPUT - 1] = '\0';
    busLine->duration = duration;
    busLine->distance = distance;
    return VALID_INPUT;
}

/**
 * This function inputs the info of entered buses
 */
BusLine* enter_bus(int number_of_lines) {
    BusLine* busLines = malloc(number_of_lines * sizeof(BusLine));
    if (busLines == NULL) {
        return NULL;
    }
    char input[MAX_INPUT];
    for (int i = 0; i < number_of_lines; i++) {
        printf("Enter line info. Then enter\n");
        if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\n")] = '\0';
            InputError error = get_bus_line_input(input,&busLines[i]);
            switch (error) {
                case VALID_INPUT:
                    break;
                case INVALID_NAME:
                    fprintf(stdout, NAME_ERR);
                    i--;
                    break;
                case INVALID_DURATION:
                    fprintf(stdout, DURATION_ERR);
                    i--;
                    break;
                case INVALID_DISTANCE:
                    fprintf(stdout, DISTANCE_ERROR);
                    i--;
                    break;
                case INVALID_FORMAT:
                default:
                    i--;
                    break;
            }
        } else {
            free(busLines);
            return NULL;
        }
    }
    return busLines;
}

/**
 * This function checks if entered name field is valid
 */
bool check_name(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] < '0' || name[i] > '9') &&
        (name[i] < 'a' || name[i] > 'z')) {
            return false;
        }
    }
    return true;
}

/**
 * This function makes 6 tests based on inputs
 */
int tests(const BusLine *start_org,const BusLine *end_org){
    long num_of_lines = end_org-start_org;
    int counter = 0;
    if(is_sorted_by_distance(start_org,end_org)==0){
        fprintf(stdout,TEST1_FAIL);}
    else{
        fprintf(stdout,TEST1_PASS);
        counter++;}
    BusLine *sorted_start = malloc(num_of_lines * sizeof(BusLine));
    if (sorted_start == NULL) {
        return 1;}
    memcpy(sorted_start, start_org, num_of_lines * sizeof(BusLine));
    quick_sort(sorted_start,sorted_start+num_of_lines,DISTANCE);
    if(is_equal(sorted_start,sorted_start+num_of_lines,
                start_org,end_org)==0){
        fprintf(stdout,TEST2_FAIL);}
    else{
        fprintf(stdout,TEST2_PASS);
        counter++;}
    if(is_sorted_by_duration(start_org,end_org)==0){
        fprintf(stdout,TEST3_FAIL);}
    else{
        fprintf(stdout,TEST3_PASS);
        counter++;}
    quick_sort(sorted_start,sorted_start+num_of_lines,DURATION);
    if(is_equal(sorted_start,sorted_start+num_of_lines,
                start_org,end_org)==0){
        fprintf(stdout,TEST4_FAIL);}
    else{
        fprintf(stdout,TEST4_PASS);
        counter++;}
    if(is_sorted_by_name(start_org,end_org)==0) {
        fprintf(stdout, TEST5_FAIL);
    }
    else {
        fprintf(stdout,TEST5_PASS);
        counter++;}
    bubble_sort(sorted_start,sorted_start+num_of_lines);
    if(is_equal(sorted_start,sorted_start+num_of_lines,
                start_org,end_org)==0){
        fprintf(stdout,TEST6_FAIL);}
    else{
        fprintf(stdout,TEST6_PASS);
        counter++;}
    if (counter == SIX_PASSED_TESTS){
        free(sorted_start);
        return true;}
    free(sorted_start);
    return false;}