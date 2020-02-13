#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "queue.h"

int Bit2_unblack_edges(Bit2_T* bit2);
int isInBounds(int row, int col, int height, int width);
void removeBlackEdge(Bit2_T* bit2, Queue* q, int row, int col);


/*
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
*/

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

// can be given a starting row and column of a black edge or NULL if one is not known
// similar to a path finding algorithm, the function follows the black edges
// of the image, and flips the bit to remove the black pixel
int Bit2_unblack_edges(Bit2_T* bit2){
    
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
    return 0;
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
    
    // loop until no more black pixel neighbors are found
    int finished = 0;
    while (!finished){
        elem = Queue_pop(q);
        // if there is nothing in the queue, black edge has been fully removed
        if (elem == NULL){
            finished = 1;
            break;
        }
        // flip the bit
        Bit2_put(bit2, elem[0], elem[1], 0);
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

