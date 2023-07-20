#pragma once
#include "./minixel.h"
#include "./cell.h"

cell_t* get_cell_from_input(minixel_t* instance, char* cell_name);
#include "./lexing.h"


// Returns pointer
  // Caller doesn't takes responsibility because it returns a pointer from an array
  // Without creating a new object
cell_t* get_cell_from_input(minixel_t* instance, char* cell_name){
  
  int collumn = (int)cell_name[0]; //ascii character
  collumn -= 65;
  int row = atoi(&cell_name[1]) -1 ;
  
  return &(instance->board[(instance->number_of_colls * row) + collumn]);
}

int handle_calculation(minixel_t* instance, char* input){

  variable_data_t variables = eval_the_variables( instance,  input);
  int result = evaluate_the_arithm_ops(&variables, input);
  return result;
}

void handle_new_value_input(char* new_value, cell_t* cell_to_change, minixel_t* instance){
  if (new_value[0] == '='){
    //there is no need for the '='
    int result = handle_calculation(instance, &(new_value[1]));
    cell_to_change->value = result;
  }else {
    cell_to_change->value = atoi(new_value);
  }
  
}
