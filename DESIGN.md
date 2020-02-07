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
- [ ] *When a representation satisfies all invariants, what abstract thing from
step [<-] does it represent?*
- [ ] *What test cases have you devised?*
- [ ] *What programming idioms will you need?*

Bit2 Checklist:

- [ ] 	*What is the abstract thing you are trying to represent?*
	* A high resolution scan stored as a bitmap.
- [ ] *What functions will you offer, and what are the contracts of that those
functions must meet?* 
- [ ] *What examples do you have of what the functions are supposed to do?*
- [ ] *What representation will you use, and what invariants will it satisfy?*
- [ ] *When a representation satisfies all invariants, what abstract thing from
step [<-] does it represent?*
- [ ] *What test cases have you devised?* 
- [ ] *What programming idioms will you need?*
