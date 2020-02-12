#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "bit.h"

// 2D bit array represented as an array of bit vectors
// Top left is (0,0)
typedef struct Bit2_T Bit2_T;

typedef void (*apply_func) (int row, int col, int bit, void* cl);

// creates an array of height bit vectors, width long
Bit2_T* Bit2_new(int width, int height);

// iterates through array and frees bit vectors
// then frees array
void Bit2_free(Bit2_T* bit2);

// returns the value of a bit at (row, column)
int Bit2_get(Bit2_T* bit2, int row, int column);

// changes value of a bit at (row, column) to value
void Bit2_put(Bit2_T* bit2, int row, int column, int value);

// iterates through all elements of bit2 row by row and 
// performs apply on each element
void Bit2_map_row_major(Bit2_T* bit2, apply_func apply, void* cl);

// iterates through all elements of bit column by column and
// performs apply on each element
void Bit2_map_col_major(Bit2_T* bit2, apply_func apply, void* cl);


// unblack edges functions
//
// looks for a black edge pixel starting with the top left of the image
// returns 0 if no black edges are found
int Bit2_find_black_edge_pixel(Bit2_T* bit2, int* row, int* column, void* cl);

// can be given a starting row and column of a black edge or NULL if one is not known
// similar to a path finding algorithm, the function follows the black edges
// of the image, and flips the bit to remove the black pixel
int Bit2_unblack_edges(Bit2_T* bit2, int* row, int* column, void* cl);


// auxilary functions
// 
// reads a pbm file into a Bit2_T struct
Bit2_T* pbmread(const char* path);

// writes a Bit2_t struct to a pbm file
// creates a pbm file if one does not exist
void pbmwrite(FILE *fp, Bit2_T* bitmap);

#endif
