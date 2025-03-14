#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between
// #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * This function checks if the bus lines are sorted by distance.
 * @return 0 if not sorted.
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end);

/**
 * This function checks if the bus lines are sorted by duration.
 * @return 0 if not sorted.
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end);

/**
 * This function checks if the bus lines are sorted by name.
 * @return 0 if not sorted.
 */
int is_sorted_by_name (const BusLine *start, const BusLine *end);

/**
 * This function checks whether the array/pointers to
 * BusLines haven't changed after sorting.
 * @return 0 in case the array/pointers changed.
 */
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
