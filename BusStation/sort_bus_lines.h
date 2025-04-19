#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define
// EX2_REPO_SORTBUSLINES_H and
// #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * TODO add documentation
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * This function uses BubbleSort algorithm to sort Struct BusLines by name
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * This function uses BubbleSort algorithm
 * to sort Struct BusLines by Duration or Distance
 * based on sort_type.
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * part of the QuickSort algorithm where it chooses a pivot and creates
 * left and right part where the left part
 * has elements "sorted" lower than the pivot
 * and the right part has elements
 * the are "sorted" higher than the pivot.
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between
// #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
