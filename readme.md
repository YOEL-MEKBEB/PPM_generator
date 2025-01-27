# PPM_generator

## what it does
##### This project focuses on creating 4 different kinds of ppm depending on the input txt file that the user provides. 
##### It can generate ppm file with randomly generated pixels, a horizontal gradient, a vertical gradient, and a diagonal gradient.

## How it works
##### The program takes in user input from the command line; it takes in the name of a txt file (or the path of the location) and creates a ppm file with the same name as the txt file.
##### The txt file should contain the all of the following seperated by space: keyword "imsize", the width, the height, the keyword "type", the type of ppm file to create, and finally a new line.
| type | output ppm file type |
|------|----------------------|
|diagonalGrad| a black to white diagonal gradient|
|horizontalGrad| a black to white horizontal gradient|
|verticalGrad| a black to white vertical gradient|
|rand| randomly generated colors for the pixels|

##### Example: imsize 256 256 type diagonalGrad
##### this will create a black and white diagonal gradient ppm file of size 256 x 256

### Note: if you want to use diagonalGrad, make sure the width and height is less 800 x 800 for consistent performance.
