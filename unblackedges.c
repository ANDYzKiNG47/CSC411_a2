#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "queue.h"

void unblackEdges(Bit2_T* bit2);
void removeBlackEdge(Bit2_T* bit2, Queue* q, int row, int col);
int isInBounds(int row, int col, int height, int width);

int main(int argc, char** argv){
    
    //testQueue(); 
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

    unblackEdges(bit2);

    Bit2_print(bit2);
    Bit2_free(bit2);
    return 0;
}

// can be given a starting row and column of a black edge or NULL if one is not known
// similar to a path finding algorithm, the function follows the black edges
// of the image, and flips the bit to remove the black pixel
void unblackEdges(Bit2_T* bit2){
    
    int height = Bit2_getHeight(bit2);
    int width = Bit2_getWidth(bit2);
    Queue* q = Queue_new();
    
    // iterate through top of image
    for (int j = 0; j < width; ++j){
        int pixel = Bit2_get(bit2, 0, j);
        if (pixel == 1){
            removeBlackEdge(bit2, q, 0, j);
        }
    }
    
    // iterate through right side of image
    for (int i = 0; i < height; ++i){
        int pixel = Bit2_get(bit2, i, width-1);
        if (pixel == 1){
            removeBlackEdge(bit2, q, i, width-1);
        }
    }

    // iterate through bottom of image
    for (int j = 0; j < width; ++j){
        int pixel = Bit2_get(bit2, height-1, j);
        if (pixel == 1){
            removeBlackEdge(bit2, q, height-1, j);
        }
    }

    // iterate through left side of image 
    for (int i = 0; i < height; ++i){
        int pixel = Bit2_get(bit2, i, 0);
        if (pixel == 1){
            removeBlackEdge(bit2, q, i, 0);
        }
    }

    Queue_free(q);
}

void removeBlackEdge(Bit2_T* bit2, Queue* q, int row, int col){
    
    int offset_x[4] = {1, 0 , -1, 0};
    int offset_y[4] = {0, -1, 0, 1};
    int height = Bit2_getHeight(bit2);
    int width = Bit2_getWidth(bit2);
    // add start point to queue
    int* elem = malloc(sizeof(int)*2);
    elem[0] = row;
    elem[1] = col;
    Queue_append(q, elem);
    // flip the bit of the initial element
    Bit2_put(bit2, elem[0], elem[1], 0);

    // loop until no more black pixel neighbors are found
    int finished = 0;
    while (!finished){
        elem = Queue_pop(q);
        // if there is nothing in the queue, black edge has been fully removed
        if (elem == NULL){
            finished = 1;
            break;
        }
        // if neighbors are a black pixel, add them to queue
        for (int i = 0; i < 4; ++i){
            int neigh_row = elem[0] + offset_y[i];
            int neigh_col = elem[1] + offset_x[i];
            if (isInBounds(neigh_row, neigh_col, height, width)){
                int neigh = Bit2_get(bit2, neigh_row, neigh_col);
                if (neigh == 1){
                    int* new_elem = malloc(sizeof(int)*2);
                    new_elem[0] = neigh_row;
                    new_elem[1] = neigh_col;
                    // flip the bit
                    Bit2_put(bit2, new_elem[0], new_elem[1], 0);
                    Queue_append(q, new_elem);
                }
            }
        }
        free(elem);
    }
}

int isInBounds(int row, int col, int height, int width){

    if (row < 0 || col < 0 || row >= height || col >= width)
        return 0;
    else 
        return 1;
}

