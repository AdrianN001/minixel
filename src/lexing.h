#pragma once 
#include <stdbool.h>
#include "./minixel.h"
#include "./input.h"

#define is_alpanumeric(x) ( isNumeric(x) && isAlphabetic(x) )


struct variable_t{
  char* name; 
  int   value;
  int   position;
};

bool isNumeric(char character){ return (int)character >= 48 && (int) character <= 57; }
// only uppercase letters counts as Alphabetic because of the cells are normally labaled in uppercases
bool isAlphabetic(char character ) {  return (int)character >= 65 && (int) character <= 90; } 
bool isArithmeticOperator(char character ) { return character == '+' || character == '-' || character == '*' || character == '/' || character == '='; }

struct variable_t* eval_the_variables(minixel_t* instance, char* input){
    struct variable_t* list_of_variables = (struct variable_t*)malloc(sizeof(struct variable_t) * 10);
    size_t current_number_of_variables = 0;

    int current_pointer_to_char = 0; 
    const int length_of_input = strlen(input);
    
    while (current_pointer_to_char < length_of_input){
        char current_character = input[current_pointer_to_char];
        if (current_character == ' ') {
            current_pointer_to_char++;
            continue;
        }

        if (isAlphabetic(current_character)){ // Variable started
            int started_pointer = current_pointer_to_char;
            char* variable = (char*)malloc(sizeof(char) * 4);
            int pointer_to_variable = 0;


            // Looping through while the pointer points to the variable
            while ( isAlphabetic(input[current_pointer_to_char]) || isNumeric(input[current_pointer_to_char]) ){

                variable[pointer_to_variable] = input[current_pointer_to_char];
                pointer_to_variable++;
                current_pointer_to_char++;

            }
            variable[pointer_to_variable] = '\0';

            // Fetch the value of the variable;
            cell_t* searched_variable = get_cell_from_input(instance, variable);
            int value_of_variable = searched_variable->value;

            //Update the array with the new variable
            list_of_variables[current_number_of_variables] = (struct variable_t){
                .name = variable,
                .value = value_of_variable,
                .position = started_pointer
            };
            current_number_of_variables++;


        }else if ( isArithmeticOperator(current_character)){
            current_pointer_to_char++;
        }


    }

#ifdef DEBUG
    for (int i = 0; i < current_number_of_variables; i++){
        struct variable_t var = list_of_variables[i];
        printf("NAME: %s \t POSITION: %d \t VALUE: %d\n", var.name, var.position, var.value);        
    }

#endif


    return list_of_variables;

}