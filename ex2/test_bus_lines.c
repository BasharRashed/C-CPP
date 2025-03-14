#include "test_bus_lines.h"
#include "string.h"
#include "stdlib.h"
#include <stdbool.h>
#include <stdio.h>
//TODO add implementation here
#define NEXT 1

bool is_digit2(char c) {
    if (c >= '0' && c <= '9'){
        return true;
    }
    return false;
}
// Function to check if a string is purely numeric
bool is_number2(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_digit2(str[i])) {
            return false;
        }
    }
    return true;
}

int string_to_int2(const char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_digit2(str[i])) {
            return -1;
        }
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int compare_bus_names2(const char *name1, const char *name2) {
    if (is_number2(name1) && is_number2(name2)) {
        int num1 = string_to_int2(name1);
        int num2 = string_to_int2(name2);
        return (num1 > num2) - (num1 < num2);
    }

    return strcmp(name1, name2);
}
/**
 * This function sorts bus lines then checks if they're sorted by distance
 * using quick sort
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end){
    size_t num_of_lines = end - start;
    BusLine *start_copy = malloc(num_of_lines*sizeof(BusLine));
    if(start_copy == NULL){
        return false;
    }
    memcpy(start_copy, start, num_of_lines * sizeof(BusLine));
    quick_sort(start_copy,start_copy+num_of_lines,DISTANCE);
    const BusLine *current_bus = start_copy;
    for(;current_bus<end;current_bus++){
        if(current_bus->distance > (current_bus+NEXT)->distance){
            free(start_copy);
            return false;
        }
    }
    free(start_copy);
    return true;

}
/**
 * This function sorts bus lines then checks if they're sorted by duration
 * using quick sort
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end){
    size_t num_of_lines = end - start;
    BusLine *start_copy = malloc(num_of_lines*sizeof(BusLine));
    if(start_copy == NULL){
        return false;
    }
    memcpy(start_copy, start, num_of_lines * sizeof(BusLine));
    quick_sort(start_copy,start_copy+num_of_lines,DURATION);
    const BusLine *current_bus = start_copy;
    for(;current_bus<end;current_bus++){
        if(current_bus->duration > (current_bus+NEXT)->duration){
            free(start_copy);
            return false;
        }
    }
    free(start_copy);
    return true;
}

/**
 * This function sorts bus lines then checks if they're sorted by name
 * using bubble sort
 */
int is_sorted_by_name(const BusLine *start, const BusLine *end) {
    size_t num_of_lines = end - start;
    BusLine *start_copy = malloc(num_of_lines * sizeof(BusLine));
    if (start_copy == NULL) {
        return false;
    }
    memcpy(start_copy, start, num_of_lines * sizeof(BusLine));
    bubble_sort(start_copy,start_copy+num_of_lines);
    for (BusLine *curr = start_copy;
    curr < start_copy + num_of_lines - 1; curr++) {
        if (compare_bus_names2(curr->name, (curr + 1)->name) > 0) {
            free(start_copy);
            return false;
        }
    }
    free(start_copy);
    return true;
}


/**
 * This function checks whether the bus
 * line before and after sorting is the same
 */
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original){

    if((end_sorted - start_sorted) !=
    (end_original - start_original)){
        return false;
    }
    const BusLine *curr_sorted = start_sorted;
    const BusLine *curr_original = start_original;
    int counter = 0;
    for(; curr_sorted<end_sorted; curr_sorted++){
        for(; curr_original<end_original; curr_original++) {
            if(strcmp(curr_sorted->name,curr_original->name)==0){
                counter++;
            }
        }
        curr_original = start_original;
    }
    if (counter != (end_sorted - start_sorted)){
        return false;
    }
    return true;
}