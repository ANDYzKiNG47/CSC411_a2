#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "queue.h"

int Bit2_find_black_edge_pixel(Bit2_T* bit2, int* row, int* column, void* cl);
int Bit2_unblack_edges(Bit2_T* bit2, int* row, int* column, void* cl);
int isInBounds(int* row, int* col, int* height, int* width);


void testQueue(){
    Queue* q = Queue_new();
    for (int i = 0; i < 5; ++i){
        int* temp = malloc(sizeof(int)*2);
        temp[0] = i;
        temp[1] = i+1;
        Queue_append(q, temp);
    }
    int* elem;
    while(Queue_getHead(q) != NULL){
        elem = Queue_pop(q);
        printf("( %d , %d )\n", elem[0], elem[1]);
        free(elem);
    }
    Queue_free(q);
}

int main(int argc, char** argv){
    
    testQueue();    
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

int isInBounds(int* row, int* col, int* height, int* width){

    if (*row < 0 || *col < 0 || *row >= *height || *col >= *width)
        return 0;
    else 
        return 1;
}

