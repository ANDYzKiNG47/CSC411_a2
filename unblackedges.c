#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"

int Bit2_find_black_edge_pixel(Bit2_T* bit2, int* row, int* column, void* cl);
int Bit2_unblack_edges(Bit2_T* bit2, int* row, int* column, void* cl);

int main(int argc, char** argv){
    
    FILE* input; 
    if (argc == 2){
        input = fopen(argv[1], "r");
    }
    else if (argc == 1){
        input = stdin;
    }else{
        fprintf(stderr, "Error: Invalid arguments");
        exit(1);
    }
    Bit2_T* bit2 = pbmread(input);
    fclose(input);

    Bit2_print(bit2);
    Bit2_free(bit2);
    return 0;
}

// looks for a black edge pixel starting with the top left of the image
// returns 0 if no black edges are found
int Bit2_find_black_edge_pixel(Bit2_T* bit2, int* row, int* column, void* cl){
    
    (void) bit2;
    (void) row;
    (void) column;
    (void) cl;
    return 0;
}


// can be given a starting row and column of a black edge or NULL if one is not known
// similar to a path finding algorithm, the function follows the black edges
// of the image, and flips the bit to remove the black pixel
int Bit2_unblack_edges(Bit2_T* bit2, int* row, int* column, void* cl){
    (void) bit2;
    (void) row;
    (void) column;
    (void) cl;
    return 0;
}

