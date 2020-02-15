#include "bit2.h"

/*
*
* implementation of a 2d bit array
* created by Andrew Zelano and Isaac Pontarelli 2/14/2020
*
*/

// struct to hold data
struct Bit2_T{
    int width;
    int height;
    Array_T arr;    
};

// creates and returns a new 2d bit array
Bit2_T* Bit2_new(int width, int height){
    
    Bit2_T* bit = malloc(sizeof(Bit2_T));
    bit->width = width;
    bit->height = height;
    // outer array
    bit->arr = Array_new(height, sizeof(Bit_T*));
    // inner bit vectors
    // invariant: every index to the left of i contains a bit vector
    for (int i = 0; i < height; ++i){
        Bit_T* p = Array_get(bit->arr, i);
        *p = Bit_new(width);
    }
    return bit;
}

// free given 2d bit array 
void Bit2_free(Bit2_T* bit2){
    
    // free inner bit vecots
    // invariant: every index to the left of i will be empty
    for (int i = 0; i < bit2->height; ++i){
        Bit_T* p = Array_get(bit2->arr, i);
        Bit_free(p);
    }
    // free outer array
    Array_free(&bit2->arr);
    free(bit2);
}

int Bit2_getHeight(Bit2_T* bit2){
    return bit2->height;
}

int Bit2_getWidth(Bit2_T* bit2){
    return bit2->width;
}

// returns bit at the given row & col
int Bit2_get(Bit2_T* bit2, int row, int column){
    
    Bit_T *bitv = Array_get(bit2->arr, row);
    int elem = Bit_get(*bitv, column);
    return elem;  
}

// modifies the bit at given row & col
void Bit2_put(Bit2_T* bit2, int row, int column, int value){

    Bit_T *bitv = Array_get(bit2->arr, row);
    int prev = Bit_put(*bitv, column, value);
    (void) prev;
}

// apply a function to each element in the 2d array in row major order
void Bit2_map_row_major(Bit2_T* bit2, apply_func apply, void* cl){

    // invariant: every array above i will have every element in it passed to the apply function
    for (int i = 0; i < bit2->height; ++i){
        Bit_T bitv = Array_get(bit2->arr, i);
        // invariant: every element to the left of j will have been passed to apply function
        for (int j = 0; j < bit2->width; ++j){
            int bit = Bit_get(bitv, j);
            apply(i, j, bit, cl);
        }
    }
}

// apply a function to each element in the 2d array in col major order
void Bit2_map_col_major(Bit2_T* bit2, apply_func apply, void* cl){

    for (int j = 0; j < bit2->width; ++j){
        for (int i = 0; i < bit2->height; ++i){
            Bit_T bitv = Array_get(bit2->arr, i);
            int bit = Bit_get(bitv, j);
            apply(i, j, bit, cl);
        }
    }
}

// read file into 2d array
Bit2_T* pbmread(FILE* input){
    
    if (input == NULL){
        fprintf(stderr, "Error: Invalid file\n");
        exit(1);
    }

    Pnmrdr_T pgmReader = Pnmrdr_new(input);
    Pnmrdr_mapdata pgmData = Pnmrdr_data(pgmReader);
    
    if (pgmData.type != Pnmrdr_bit){
        fprintf(stderr, "Error: Invalid image type\n");
        Pnmrdr_free(&pgmReader);
        exit(1);
    }

    Bit2_T* bit2 = Bit2_new(pgmData.width, pgmData.height);
    
    // read each "pixel" into the 2d array
    // invariant: every array above i will have a pixel value in each index
    for (int i = 0; i < (int) pgmData.height; ++i){
        // invariant: every element to the left of j will have a pixel value stored in it
        for (int j = 0; j < (int) pgmData.width; ++j){
            int pixel = (int) Pnmrdr_get(pgmReader);
            Bit2_put(bit2, i, j, pixel);
        }
    }
    Pnmrdr_free(&pgmReader);

    return bit2;
}

// print out the 2d array in a pnm format
void Bit2_print(Bit2_T* bit2){
    // print header
    printf("P1\n");
    printf("%d %d\n", bit2->width, bit2->height);
    // print the bits in ascii format
    for (int i = 0; i < bit2->height; ++i){
        for (int j = 0; j < bit2->width; ++j){
            int bit = Bit2_get(bit2, i, j);
            printf("%d", bit);
        }
    }
    printf("\n");
}










































