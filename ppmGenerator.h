#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// write the header of the ppm file given in the parameter
// using the width and the height
// returns 0 on success and -1 on failure
int writeHeader(FILE* file, char* width, char* height);


// writes the body content of the ppm file
// returns 0 on success and -1 on failure
int writeRandomBody(FILE* file,  char* width, char* height);

// draws a horizontal gradient
// returns 0 on success and -1 on failure
int writeHorizontalGradient(FILE* file, char* width, char* height);

// draws a vertical gradient
// returns 0 on success and -1 on failure
int writeVerticalGradient(FILE* file, char* width, char* height);

// draws a diagonal gradient
// returns 0 on success and -1 on failure
int writeDiagonalGradient(FILE* file, char* width, char* height);