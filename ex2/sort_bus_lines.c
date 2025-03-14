#include "sort_bus_lines.h"
#include <stdlib.h>
#include <stdbool.h>
//TODO add implementation here

/**
 * This function swaps two entered values
 */
void swap(BusLine *a, BusLine *b){
    BusLine temp = *a;
    *a = *b;
    *b = temp;
}

bool is_digit(char c) {
    if (c >= '0' && c <= '9'){
        return true;
    }
    return false;
}
// Function to check if a string is purely numeric
bool is_number(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_digit(str[i])) {
            return false;
        }
    }
    return true;
}

int string_to_int(const char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_digit(str[i])) {
            return -1;
        }
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int compare_bus_names(const char *name1, const char *name2) {
    if (is_number(name1) && is_number(name2)) {
        int num1 = string_to_int(name1);
        int num2 = string_to_int(name2);
        return (num1 > num2) - (num1 < num2);
    }

    return strcmp(name1, name2);
}

/**
 * This function sorts bus lines using bubbleSort algorithm
 */
void bubble_sort (BusLine *start, BusLine *end){
    for(BusLine *i = start;i < end-1;i++){
        for(BusLine *j = start;j < end-(i-start)-1;j++){
            if (compare_bus_names(j->name, (j + 1)->name) > 0) {
                swap(j, j + 1);
            }
        }
    }
}

/**
 * This function sorts bus lines using quicksort algorithm
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type){
    if (start < end - 1) {
        BusLine *pivot = partition(start, end, sort_type);

        quick_sort(start, pivot, sort_type);
        quick_sort(pivot + 1, end, sort_type);
    }
}


/**
 * This function is part of quicksort algorithm
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type){
    BusLine *pivot = end - 1;  // Last element as the pivot
    BusLine *i = start - 1;   // Index for smaller elements

    for (BusLine *j = start; j < pivot; j++) {
        if (sort_type == DISTANCE && j->distance <= pivot->distance){
            i++;
            swap(i, j);
        }
        else if (sort_type == DURATION && j->duration <= pivot->duration){
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, pivot);
    return i + 1;
}

