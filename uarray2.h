#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED
typedef struct UArray2_T* UArray2_T;
extern UArray2_T Uarray2_new(int width, int height, int size);
extern void UArray2_free(UArray2_T* arr);
extern int UArray2_width(UArray2_T arr);
extern int UArray2_height(UArray2_T arr);
extern int UArray2_size(UArray2_T arr);
extern void* UArray2_get(UArray2_T arr, int width, int height);
// need to modify the apply function
// functions are copies of Bit_map as of now
extern void UArray2_map_row_major(UArray2_T arr,
        void apply(int n, int bit, void* cl), void* cl);
extern void UArray2_map_col_major(UArray2_T arr,
        void apply(int n, int bit, void* cl), void* cl);
#endif
