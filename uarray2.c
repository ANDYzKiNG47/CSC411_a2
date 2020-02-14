#include "uarray2.h"

/*
* implementation of an unbounded 2d array
*
* created by Andrew Zelano and Isaac Pontarelli 2/14/2020
*/

// struct to hold data about the array
struct UArray2_T {
    int width;
    int height;
    int size;
    Array_T matrix;
};

// returns a new 2d array of the specified dimensions
UArray2_T* Uarray2_new(int width, int height, int size){

    UArray2_T* uarr2 = malloc(sizeof(UArray2_T));
    uarr2->width = width;
    uarr2->height = height;
    uarr2->size = size;
    // initialize outer array
    uarr2->matrix = Array_new(height, sizeof(Array_T*));
    // initialize inner arrays
    for (int i = 0; i < height; ++i){
        Array_T* p = Array_get(uarr2->matrix, i);
        *p = Array_new(width, size);
    }
    return uarr2;
}

// frees any given UArray2_T
void UArray2_free(UArray2_T* arr){
    
    // free inner arrays 
    for (int i = 0; i < arr->height; ++i){
        Array_T* p = Array_get(arr->matrix, i);
        Array_free(p);
    }
    Array_free(&arr->matrix);
    free(arr);

}

int UArray2_width(UArray2_T* arr){
    return arr->width;
}

int UArray2_height(UArray2_T* arr){
    return arr->height;
}

int UArray2_size(UArray2_T* arr){
    return arr->size;
}

// return a pointer to an element at a specific row & col
void* UArray2_get(UArray2_T* arr, int row, int column){

    Array_T* p = Array_get(arr->matrix, row);
    void* elem = Array_get(*p, column);
    return elem;
}

// appy a given function to each element in a row major pattern
void UArray2_map_row_major(UArray2_T* arr, apply_func apply, void* cl){
    
    for (int i = 0; i < arr->height; ++i){
        for (int j = 0; j < arr->width; ++j){
            void* e = UArray2_get(arr, i, j);
            apply(arr, i, j, e, cl);
        }
    }
}

// appy a given function to each element in a column major pattern
void UArray2_map_col_major(UArray2_T* arr, apply_func apply, void* cl){
    
    for (int j = 0; j < arr->width; ++j){
        for (int i = 0; i < arr->height; ++i){
            void* e = UArray2_get(arr, i, j);
            apply(arr, i, j, e, cl);
        }
    }
}

// appy a given function to each element in a block major pattern. 
// this is intended to be handy for sudoku
void UArray2_map_block_major(UArray2_T* arr, apply_func apply, void* cl){

    // hard coded dimensions of sudoku puzzle
    if (arr->height != 9 || arr->width != 9)
        return;

    // traverse top 3 blocks
    int j_idx = 0;
    for (int k = 0; k < 3; ++k){
        for (int i = 0; i < 3; ++i){
            for (int j = j_idx; j < j_idx + 3; ++j){
                void* e = UArray2_get(arr, i, j);
                apply(arr, i, j, e, cl);
            }
        }
        j_idx += 3;
    }

    // traverse middle 3 blocks
    j_idx = 0;
    for (int k = 0; k < 3; ++k){
        for (int i = 3; i < 6; ++i){
            for (int j = j_idx; j < j_idx + 3; ++j){
                void* e = UArray2_get(arr, i, j);
                apply(arr, i, j, e, cl);
            }
        }
        j_idx += 3;
    }

    // traverse bottom 3 blocks
    j_idx = 0;
    for (int k = 0; k < 3; ++k){
        for (int i = 6; i < 9; ++i){
            for (int j = j_idx; j < j_idx + 3; ++j){
                void* e = UArray2_get(arr, i, j);
                apply(arr, i, j, e, cl);
            }
        }
        j_idx += 3;
    }
}

// load a file into a 2d array
UArray2_T* UArray2_readPGM(FILE* input){
    
    // throw error if no input given
    if (input == NULL){
        fprintf(stderr, "Error: Invalid file\n");
        exit(1);
    }

    Pnmrdr_T pgmReader = Pnmrdr_new(input);
    Pnmrdr_mapdata pgmData = Pnmrdr_data(pgmReader);
    
    // check data type
    if (pgmData.type != Pnmrdr_gray){
        fprintf(stderr, "Error: Invalid image type\n");
        Pnmrdr_free(&pgmReader);
        exit(1);
    }
    
    UArray2_T* arr = Uarray2_new(pgmData.width, pgmData.height,  sizeof(int));
    int len = arr->width * arr->height;
    // load each "pixel" into the array
    for (int i = 0; i < len; ++i){
        int r = i / pgmData.height;
        int c = i % pgmData.width;
        int pixel = (int) Pnmrdr_get(pgmReader);
        int* e = UArray2_get(arr, r, c);
        *e = pixel;
    }
    Pnmrdr_free(&pgmReader);

    return arr;
}


















