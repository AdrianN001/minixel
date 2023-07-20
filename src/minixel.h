#pragma once
#include "./cell.h"

typedef struct minixel{ 
  cell_t* board;
  short number_of_rows;
  short number_of_colls;
} minixel_t;


minixel_t initalize_minixel_board(int rows, int colls){
    const int number_of_cells = rows*colls;

    minixel_t instance; 
    instance.number_of_rows = rows;
    instance.number_of_colls = colls;
    instance.board = (cell_t*)malloc(sizeof(cell_t) * number_of_cells); 
    
    
    
    
      for (int i = 0;  i < rows; i++){
          for (int j = 0; j < colls; j++){
            instance.board[(i * colls) + j] = initalize_cell(i, j);
          }
      }
      
      return instance;
}
      
void free_minixel_board(minixel_t* instance){
  if (instance->board){
    free(instance->board);
   }
}

void print_cells(minixel_t* instance ){
  printf("\t");
  for (int header = 65; header < (65 + instance->number_of_colls); header++){
    printf("   %c\t", (char)header);
  }
  printf("\n");
  
  for (int i = 0; i < instance->number_of_rows; i++){
      printf("  %d\t", i+1); // Print the ID of the row
    for (int j = 0; j < instance->number_of_colls; j++){
        
        if (  instance->board[(instance->number_of_colls * i ) + j].value  == INT_MIN ){
          //printf("|#%d# \t", (instance->number_of_colls * i ) + j);
          printf("| \t");
        }else{
          printf("|%d \t", instance->board[(instance->number_of_colls * i ) + j].value);
        }
        
      }
      printf("|\n");
    }
}



