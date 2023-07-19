#include "./minixel.h"
#include "./input.h"



int main(int argc, char** argv){
  if (argc != 3){ 
    printf("Usage: ./file [rows number] [colls number]");
    return -1;
  }
  const int rows = atoi(argv[1]);
  const int colls = atoi(argv[2]);
  
  minixel_t minixel_instance = initalize_minixel_board(rows, colls);
  


  while (1){
    char cell[10] = {0};
    print_cells(&minixel_instance);
    printf("Which cell to update? >>  ");
    scanf("%s", cell);
    if (!strlen(cell)){
      break;
    }
    cell_t* cell_to_update = get_cell_from_input(&minixel_instance, cell);
    
    
    char new_value[100] = {0};
    printf("What should be its value? \n(TYPE HERE)");
    scanf("%s", new_value);
    
    handle_new_value_input(new_value, cell_to_update, &minixel_instance);
    
  }
  
  printf("EXIT");

  return 0;
}
