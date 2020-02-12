#include <stdio>
#include <stdlib>

typedef struct Bit2_T* Bit2_T;
extern Bit2_T Bit2_new(int width, int height);
extern void Bit2_free(Bit2_T* bit2);
extern int Bit2_get(Bit2_T bit2, int row, int column);
extern void Bit2_put(Bit2_T bit2, int row, int column, int value);
extern void Bit2_map_row_major(Bit2_T bit2,
        void apply(int width, int height, int bit, void* cl), void* cl);
extern void Bit2_map_col_major(Bit2_T bit2,
        void apply(int width, int height, int bit, void* cl), void* cl);

extern int Bit2_find_black_edge_pixel(Bit2_T bit2, int* row, int* column, void* cl);
extern int Bit2_unblack_edges(Bit2_T bit2, int* row, int* column, void* cl);
extern Bit2_T pbmread(const char* path);
extern void pbmwrite(FILE *fp, Bit2_T bitmap);
