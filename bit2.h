#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED
typedef struct Bit2_T* Bit2_T;
extern Bit2_T Bit2_new(int width, int height);
extern void Bit2_free(Bit2_T* bit_arr);




// auxilary functions
extern Bit2_T pbmread(const char* path);
extern void pbmwrite(FILE *fp, Bit2_T bitmap);
#endif
