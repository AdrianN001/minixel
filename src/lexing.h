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

typedef struct token_t{
    int value;
    bool isOperator;
} token_t;

typedef struct variable_data { 
    struct variable_t* variables;
    int number_of_variables;
} variable_data_t;

 

bool isNumeric(char character){ return (int)character >= 48 && (int) character <= 57; }
// only uppercase letters counts as Alphabetic because of the cells are normally labaled in uppercases
bool isAlphabetic(char character ) {  return (int)character >= 65 && (int) character <= 90; } 
bool isArithmeticOperator(char character ) { return character == '+' || character == '-' || character == '*' || character == '/' || character == '='; }

variable_data_t eval_the_variables(minixel_t* instance, char* input){
    struct variable_t* list_of_variables = (struct variable_t*)malloc(sizeof(struct variable_t) * 10);
    size_t current_number_of_variables = 0;

    int current_pointer_to_char = 0; 
    
    while (current_pointer_to_char < strlen(input)){
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


        }else if (current_character == '{'){
            // Numeric literal
            
            int started_pointer = current_pointer_to_char;
            int numeric_literal = 0;
            current_pointer_to_char++;
            bool is_negative = false;
            if ( input[current_pointer_to_char] == '-'){
                is_negative = true;
                current_pointer_to_char++;
            }

            while(input[current_pointer_to_char] != '}'){
               
                int digit = input[current_pointer_to_char++] - 48;
                numeric_literal += digit;
                numeric_literal *= 10; // shift to left

            }

            list_of_variables[current_number_of_variables] = (struct variable_t){
                                                                                    .name = "LITERAL_CONSTANT",
                                                                                    .value = is_negative ? -1 * (numeric_literal / 10) : (numeric_literal / 10) ,
                                                                                    .position = started_pointer
                                                                                };

            current_number_of_variables++;
            current_pointer_to_char++;

        }else if ( isArithmeticOperator(current_character)){
            current_pointer_to_char++;
        }

        
    }

#ifdef DEBUG
    printf("\n\n[ !! ] DEBUG FLAG IS DEFINED [ !! ] \n\n");
    for (int i = 0; i < current_number_of_variables; i++){
        struct variable_t var = list_of_variables[i];
        printf("NAME: %s \t POSITION: %d \t VALUE: %d\n", var.name, var.position, var.value);        
    }
    printf("\n\n[ !! ] DEBUG FLAG IS DEFINED [ !! ] \n\n");

#endif

    
    return (variable_data_t){list_of_variables, current_number_of_variables};

}

int evaluate_the_arithm_ops(variable_data_t* variable_values, char* input){
    // eval the parenthesis


    // eval the multi / divide

    float current_chunk = variable_values->variables[0].value;

    token_t tokens[30];
    size_t current_token_number = 0;

    

    for (int current_index = 0; current_index < variable_values->number_of_variables - 1; current_index++){
        float new_value = 0.0F;
        struct variable_t current_variable = variable_values->variables[current_index];
        struct variable_t next_variable = variable_values->variables[current_index + 1];


        char current_operator = input[next_variable.position - 1];
        switch (current_operator)
        {
            case '*':
                if (current_chunk == INT_MIN){
                    // New chunk started
                    current_chunk = current_variable.value * next_variable.value;
                }else{
                    current_chunk *= (float)next_variable.value;
                }
                break;
            case '/':
                if (current_chunk == INT_MIN){
                    current_chunk = current_variable.value / next_variable.value;
                }else{
                    current_chunk /= (float)next_variable.value;
                }
                break;
            default:
                // + or - 
                
                if (current_chunk != INT_MIN) {
                    
                    // Clear the chunk and add it as a token.
                    token_t chunk_token = (token_t){.isOperator = false, 
                                                .value = current_chunk};
                    current_chunk = INT_MIN;
                    tokens[current_token_number++] = chunk_token;
                    
                }else{ 
                    // Add the variable which is in a addition or a subs. to the tokens
                    token_t variable_token = (token_t){.isOperator = false, 
                                                .value = current_variable.value};
                    
                    tokens[current_token_number++] = variable_token;
                }
                token_t operator_token = (token_t){ .isOperator = true,
                                                    .value = (int)current_operator};
                
                    tokens[current_token_number++] = operator_token;
                
                break;
            }
    }
    if (current_chunk != INT_MIN){
        
        token_t chunk_token = (token_t){.isOperator = false, 
                                                .value = current_chunk};
        tokens[current_token_number++] = chunk_token;
    }else{
        // In this case. the loop could not get to the last variable as "current variable"  ( because of the 2 windwow method )
        token_t variable_token = (token_t){.isOperator = false, 
                                                .value = variable_values->variables[variable_values->number_of_variables - 1].value};
        tokens[current_token_number++] = variable_token;          
    }
#ifdef DEBUG
    printf("\n\n[ !! ] DEBUG FLAG IS DEFINED [ !! ] \n\n");
    for (int i = 0; i < current_token_number; i++){
        
        if (tokens[i].isOperator){
            printf(" %c ", (char)tokens[i].value);
        }else{
            printf(" %d ", tokens[i].value);
        }

    }
    printf("\n\n [ !! ] DEBUG FLAG IS DEFINED [ !! ] \n\n");
#endif

    // evaluate additon and subs.
    

    int current_sum = tokens[0].value;
    for ( int current_token_index = 1; current_token_index < current_token_number - 1; current_token_index += 2){
        token_t current_operator = tokens[current_token_index];
        token_t current_number   = tokens[current_token_index + 1];

        if ((char)current_operator.value == '+'){
            current_sum += current_number.value; 
        }else{
            current_sum -= current_number.value;
        }

    }

    return current_sum;
}