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
    
    Bit_T *bitv = Array_get(bit2->arr, row);
    int elem = Bit_get(*bitv, column);
    return elem;  
}

void Bit2_put(Bit2_T* bit2, int row, int column, int value){

    Bit_T *bitv = Array_get(bit2->arr, row);
    int prev = Bit_put(*bitv, column, value);
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
    int len = pgmData.width * pgmData.height;
    for (int i = 0; i < len; ++i){
        int r = i / (pgmData.height-1);
        int c = i % pgmData.width;
        int pixel = (int) Pnmrdr_get(pgmReader);
	Bit2_put(bit2, r, c, pixel);
    }
    Pnmrdr_free(&pgmReader);

    return bit2;
}

void Bit2_print(Bit2_T* bit2){
    printf("P1\n");
    printf("%d %d\n", bit2->width, bit2->height);
    for (int i = 0; i < bit2->height; ++i){
        for (int j = 0; j < bit2->width; ++j){
            int bit = Bit2_get(bit2, i, j);
            printf("%d", bit);
        }
    }
    printf("\n");
}










































