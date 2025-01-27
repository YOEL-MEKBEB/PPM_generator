#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// write the header of the ppm file given in the parameter
// using the width and the height
int writeHeader(FILE* file, char* width, char* height);


// writes the body content of the ppm file
int writeRandomBody(FILE* file,  char* width, char* height);

// draws a horizontal gradient
int writeHorizontalGradient(FILE* file, char* width, char* height);

// draws a vertical gradient
int writeVerticalGradient(FILE* file, char* width, char* height);

// draws a diagonal gradient
int writeDiagonalGradient(FILE* file, char* width, char* height);