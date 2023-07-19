#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define VALUE_SIZE 30
#define ROWS 25
#define COLLS 20

typedef struct cell{
  int row;
  int collumn;
  int value;
} cell_t;



cell_t initalize_cell(int row, int collumn ){
    cell_t new_cell = (cell_t){ 
                      .row = row,
                      .collumn = collumn,
                      .value = INT_MIN
                    };

    return new_cell;
}
