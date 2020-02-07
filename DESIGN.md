Andrew Zelano
Isaac Pontarelli

Design Document   -   CSC 411   -    Assignment 2: iii

Uarray2 Checklist:

- [ ] *What is the abstract thing you are trying to represent?*
	- A set of sodoku solutions stored in a portable grey map file.
- [ ] *What functions will you offer, and what are the contracts of that those functions must meet?* 
	* extern UArray2\_T Uarray2\_new(int width, int height, int size); Initializes a new UAarray2\_T struct with width x height deminsions and stores elelemts of 'size' bytes
	* extern void UArray2\_free(UArray2\_T\* arr); iterates through each nested array and deallocates, then dellocates outer array
	* extern int UArray2\_width(UArray2\_T arr); returns the width of the array
	* extern int UArray2\_height(UArray2\_T arr); returns the height of the array
	* extern int UArray2\_size(UArray2\_T arr); returns the size of the elements stored in the nested arrays. 
	* extern void\* UArray2\_get(UArray2\_T arr, int row, int column); returns a void pointer to an elements at (row,column)
	* extern void UArray2\_map\_row\_major(UArray2\_T arr,void apply(UArray2\_T arr, int\* row, int\* column, void\* elem, void\* cl), void\* cl); map functions iterate through 2D array and performs apply function on each element. NULL can be passed  to apply for row and column if not needed
	*  extern void UArray2\_map\_col\_major(UArray2\_T arr, void apply(UArray2\_T arr, int\* row, int\* column, void\* elem, void\* cl), void\* cl); iterates through 2D array column by column and applies function to each element
	* extern void UArray2\_map\_block\_major(UArray2\_T arr, void apply(UArray2\_T arr, int\* row, int\* column, void\* elem, void\* cl), void\* cl); iterates through the array in blocks of sqrt(n) x sqrt(n)

	These functions make it clear that UArray2 is a mutable abstraction

- [ ] *What examples do you have of what the functions are supposed to do?*
	* 
- [ ] *What representation will you use, and what invariants will it satisfy?*
	* We will use Hanson arrays to implemt our 2d Array. Which is either
		* a Null pointer
		* a pointer p to an array of pointers p->1, p->2, ..., p->n to other hanson arrays.
			* Either p->1 is null or p->1 is of size n where n is the width    
- [ ] *When a representation satisfies all invariants, what abstract thing from
step [<-] does it represent?* 
	* the NULL pointer represents an empty image
	* a nonnull pointer p represents a bitmap image
- [ ] *What test cases have you devised?*
	* Test cases are left as an exercise in creativity for the reader
- [ ] *What programming idioms will you need?*
	* The idioms for pointers and storing values in an unboxed array
	* The idiom for Allocating memory
	

Bit2 Checklist:

- [ ] 	*What is the abstract thing you are trying to represent?*
	* A high resolution scan stored as a bitmap.
- [ ] *What functions will you offer, and what are the contracts of that those
functions must meet?* 
    * extern Bit2\_T Bit2\_new(int width, int height); creates an array of 'height' bit vectors, 'width' long
    * extern void Bit2\_free(Bit2\_T\* bit2); iterates through array and frees bit vectors, then frees the array
    * extern int Bit2\_get(Bit2\_T bit2, int row, int column); returns the value of a bit at (row, column)
    * extern void Bit2\_put(Bit2\_T bit2, int row, int column, int value); changes value of a bit at (row, column) to 'value'
    * extern void Bit2\_map\_row\_major(Bit2\_T bit2,void apply(int width, int height, int bit, void\* cl), void\* cl); iterates through all elements of bit2 row by row and performs apply on each element
    * extern void Bit2\_map\_col\_major(Bit2\_T bit2,void apply(int width, int height, int bit, void\* cl), void\* cl); iterates through all elements of bit2 column by column and performs apply on each element
    * extern int Bit2\_find\_black\_edge\_pixel(Bit2\_T bit2, int\* row, int\* column, void\* cl); looks for a black edge pixel starting with the top left of the image. returns 0 if no black edges are found
    * extern int Bit2\_unblack\_edges(Bit2\_T bit2, int\* row, int\* column, void\* cl); can be gicen a starting row and oclumn of a black edge or NULL if one is not known. similar to a path finding algoritm,
the function travels to the neighbors of the original black edge pixel, and flips the bit to remove the black pixel
    * extern Bit2\_T pbmread(const char\* path); reads a pbm file into a Bit2\_T struct
    * extern void pbmwrite(FILE \*fp, Bit2\_T bitmap); writes a Bit2\_T struct to a pbm file. creates a pbm file if one does not exist

- [ ] *What examples do you have of what the functions are supposed to do?*
- [ ] *What representation will you use, and what invariants will it satisfy?*
- [ ] *When a representation satisfies all invariants, what abstract thing from
step [<-] does it represent?*
- [ ] *What test cases have you devised?* 
- [ ] *What programming idioms will you need?*
