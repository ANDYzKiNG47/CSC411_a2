#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED
typedef struct UArray2_T* UArray2_T;
// initializes a new UAarray2_T struct with
// width x height deminsions and stores elelemts of 'size' bytes
extern UArray2_T Uarray2_new(int width, int height, int size);
// iterates through each nested array and deallocates, then dellocates outer array
extern void UArray2_free(UArray2_T* arr);
// returns the width and height of the 2D array respectively
// 2D array struct knows its demensions so the function is constant
extern int UArray2_width(UArray2_T arr);
extern int UArray2_height(UArray2_T arr);
// returns the size of the elements stored in the nested arrays
// 2D array struct stores this. Constant time
extern int UArray2_size(UArray2_T arr);
// returns a pointer to an elements at (row,column)
// user is responsible for casting void* pointer to correct type
// can be used to modify elements
extern void* UArray2_get(UArray2_T arr, int row, int column);
// map functions iterate through 2D array and
// performs apply function on each element
// -1 can be passed  to apply for row and column if not needed
//
// iterates through 2D array row by row
extern void UArray2_map_row_major(UArray2_T arr,
        void apply(UArray2_T arr, int row, int column, void* elem, void* cl), void* cl);
// iterates through 2D array column by column
extern void UArray2_map_col_major(UArray2_T arr,
        void apply(UArray2_T arr, int row, int column, void* elem, void* cl), void* cl);
// iterates through the array in blocks of sqrt(n) x sqrt(n)
// can only be used is n is a perfect square
extern void UArray2_map_block_major(UArray2_T arr,
        void apply(UArray2_T arr, int row, int column, void* elem, void* cl), void* cl);
#endif
