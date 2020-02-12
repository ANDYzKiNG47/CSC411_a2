#include "bit2.h"

struct Bit2_T{
    int width;
    int height;
    Array_T arr;    
};

Bit2_T* Bit2_new(int width, int height){
    
    Bit2_T* bit = malloc(sizeof(Bit2_T));
    bit->width = width;
    bit->height = height;
    bit->arr = Array_new(height, sizeof(Bit_T*));
    for (int i = 0; i < height; ++i){
        Bit_T* p = Array_get(bit->arr, i);
        *p = Bit_new(width);
    }
    return bit;
}

void Bit2_free(Bit2_T* bit2){
    
    for (int i = 0; i < bit2->height; ++i){
        Bit_T* p = Array_get(bit2->arr, i);
        Bit_free(p);
    }
    Array_free(&bit2->arr);
    free(bit2);
}

int Bit2_get(Bit2_T* bit2, int row, int column){
    
    Bit_T bitv = Array_get(bit2->arr, row);
    int elem = Bit_get(bitv, column);
    return elem;  
}

void Bit2_put(Bit2_T* bit2, int row, int column, int value){

    Bit_T bitv = Array_get(bit2->arr, row);
    int prev = Bit_put(bitv, column, value);
    (void) prev;
}

void Bit2_map_row_major(Bit2_T* bit2, apply_func apply, void* cl){

    for (int i = 0; i < bit2->height; ++i){
        Bit_T bitv = Array_get(bit2->arr, i);
        for (int j = 0; j < bit2->width; ++j){
            int bit = Bit_get(bitv, j);
            apply(i, j, bit, cl);
        }
    }
}
void Bit2_map_col_major(Bit2_T* bit2, apply_func apply, void* cl){

    for (int j = 0; j < bit2->width; ++j){
        for (int i = 0; i < bit2->height; ++i){
            Bit_T bitv = Array_get(bit2->arr, i);
            int bit = Bit_get(bitv, j);
            apply(i, j, bit, cl);
        }
    }
}

int Bit2_find_black_edge_pixel(Bit2_T* bit2, int* row, int* column, void* cl){
    (void) bit2;
    (void) row;
    (void) column;
    (void) cl;
    return 0;
}

int Bit2_unblack_edges(Bit2_T* bit2, int* row, int* column, void* cl){
    (void) bit2;
    (void) row;
    (void) column;
    (void) cl;
    return 0;   
}

Bit2_T* pbmread(const char* path){
    (void) path;
    return NULL;
}
void pbmwrite(FILE *fp, Bit2_T* bitmap){
    (void) fp;
    (void) bitmap;    
}










































