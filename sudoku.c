#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"

/*
*
* implementation for the a sudoku solution checker
* created by Andrew Zelano and Isaac Pontarelli 2/14/2020
*	
*/

// function to be applied to each element in the sudoku
void apply(UArray2_T* arr, int row, int col, void* elem, void* cl);


int main(int argc, char** argv){
    
    FILE* input; 
    UArray2_T* uarr2; 
    if (argc == 2){
        input = fopen(argv[1], "r");
    }
    else if (argc == 1){
        input = stdin;
    }else{
        fprintf(stderr, "Error: Invalid arguments");
        exit(1);
    }
    // read file into 2d array
    uarr2 = UArray2_readPGM(input);
    fclose(input);
    int* cl = calloc(10, sizeof(int)*10);
    // check each row 
    UArray2_map_row_major(uarr2, apply, cl);
    // check each column
    UArray2_map_col_major(uarr2, apply, cl);
    // check each 3x3 block
    UArray2_map_block_major(uarr2, apply, cl);
 
    free(cl);
    UArray2_free(uarr2);

    return 0;
}

// sets all ements of array = 0
void clearArray(int* arr, int size){
    // invariant: any element to the left of i has a value of 0
    for (int i = 0; i < size; ++i){
        arr[i] = 0;
    }
}

// first element of cl stores count
// resets when count == 9 (iterations)
// exits if any duplicates are found
// resets closure if no duplicates are found and continues 
void apply(UArray2_T* arr, int row, int col, void* elem, void* cl){

    (void) arr;
    (void) row;
    (void) col;

    int* check = (int*) cl;
    int* e = (int*) elem;

    if (check[*e] != 0){
        fprintf(stderr, "Invalid sudoku\n");
        exit(1);
    }else{
        check[*e] = *e;
        check[0] += 1;
    }

    if (check[0] == 9){
        clearArray(check, 10);
    }

}

