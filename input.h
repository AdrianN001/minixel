#pragma once
#include "./cell.h"
#include "./minixel.h"

cell_t* get_cell_from_input(minixel_t* instance, char* cell_name){
  int collumn = (int)cell_name[0]; //ascii character
  collumn -= 65;
  int row = atoi(&cell_name[1]) -1 ;
  
  return &(instance->board[(instance->number_of_colls * row) + collumn]);
}

int handle_calculation(minixel_t* instance, char* input){
  return 1;
}

void handle_new_value_input(char* new_value, cell_t* cell_to_change, minixel_t* instance){
  if (new_value[0] == '='){
    int result = handle_calculation(instance, new_value);
    cell_to_change->value = result;
  }else {
    cell_to_change->value = atoi(new_value);
  }
  
}
