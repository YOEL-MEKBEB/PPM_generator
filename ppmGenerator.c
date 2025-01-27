#include "ppmGenerator.h"

int writeHeader(FILE* file, char* width, char* height){
    char* p3 = "P3\n";
    if(fwrite(p3, strlen(p3), 1, file) < 1){
        perror("failed to write header\n");
        return -1;
    }

    // concatenates all the strings together to make the header for the ppm file
    char widthAndHeight[30] = "";
    char* resultString = strcat(widthAndHeight, width);
    resultString = strcat(widthAndHeight, " ");
    resultString = strcat(widthAndHeight, height);
    resultString = strcat(widthAndHeight, "\n");
    resultString = strcat(widthAndHeight, "255");
    resultString = strcat(widthAndHeight, "\n");

    //writes the entire string to the file provided to the function
    if(fwrite(resultString, strlen(resultString), 1, file) < 1){
        perror("failed to write header\n");
        return -1; 
    }

    return 0;
}

int writeRandomBody(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    
    int numHeight = atoi(height);
    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    // loops through the size of the image to set each pixel value and write to the file
    for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];

        // j < 3 * numWidth because each pixel will have 3 number associated with it
        for(int j = 0; j < 3 * numWidth; j++){
            num = rand()%256; // 0 to 2555
            // limit the number of character used
            if(j%15 == 0){
                if(sprintf(numChar, "%d\n", num) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
            }else{
                if(sprintf(numChar, "%d ", num) == -1){
                    printf("sprintf failed in writeRandomBody\n");
                    return -1;
                }
            }
            if(fwrite(numChar, strlen(numChar), 1, file) < 1){
                perror("failed to write in writeRandomBody\n");
                return -1; 
            }
        }
    }
    return 0;
}

int writeHorizontalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    // loops through the size of the image to set each pixel value and write to the file
    for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];

        // j < 3 * numWidth-1 because each pixel will have 3 number associated with it
        for(int j = 0; j < 3 * numWidth; j++){
            num = j/3;
            // limit the number of character used
            if(j%15 == 0){
                if(sprintf(numChar, "%d\n", num) == -1){
                    printf("sprintf failed in writeHorizontalGradient\n");
                    return -1;
                }
            }else{
                if(sprintf(numChar, "%d ", num) == -1){
                    printf("sprintf failed in writeHorizontalGradient\n");
                    return -1;
                }
            }
            
            if(fwrite(numChar, strlen(numChar), 1, file) < 1){
                perror("failed to write in writeHorizontalGradient\n");
                return -1;  
            }
        }
    }
    return 0;
}

int writeVerticalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    // loops through the size of the image to set each pixel value and write to the file
    for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];

        // j < 3 * numWidth-1 because each pixel will have 3 number associated with it
        for(int j = 0; j < 3 * numWidth; j++){
            num = i;
            // limit the number of character used
            if(j%15 == 0){
                if(sprintf(numChar, "%d\n", num) == -1){
                    printf("sprintf failed in writeVerticalGradient\n");
                    return -1;
                }
            }else{
                if(sprintf(numChar, "%d ", num) == -1){
                    printf("sprintf failed in writeVerticalGradient\n");
                    return -1;
                }
            }
            
            if(fwrite(numChar, strlen(numChar), 1, file) < 1){
                perror("failed to write in writeVerticalGradient\n");
                return -1;  
            }
        }
    }
    return 0;
}

int writeDiagonalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    // creates an array of the same size as the ppm to simplify the pixel value calculations
    // not efficient for large file sizes
    int imageArray[numHeight][3*numWidth];

    //scaling factors to adjust pixel values in loop relative to the size of the image
    float xScalingFactor = 256.0/(numWidth);
    float yScalingFactor = 256.0/numHeight;
    printf("xScaling %f\n", xScalingFactor);
    printf("yScaling %f\n", yScalingFactor);

    // loops through the size of the image to set each pixel value
    for(int i = 0; i < numHeight; i++){
        for(int j = 0; j < 3 * numWidth; j++){
            // this method ensures that the pixel color value doesn't exceed 255
            if(i>=j/3){
                imageArray[i][j] = 255 - (int)(yScalingFactor * i);
            }else{
                imageArray[i][j] = 255 - (int)(xScalingFactor* j/3);
            }
            
        }
     } 

    // loops through the size of the image to write to the file
    for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];
        num = i;

        // j < 3 * numWidth-1 because each pixel will have 3 number associated with it
        for(int j = 0; j < 3 * numWidth; j++){
            num = imageArray[i][j];

            // limit the number of character used
            if(j%15 == 0){
                if(sprintf(numChar, "%d\n", num) == -1){
                    printf("sprintf failed in writeDiagonalGradient\n");
                    return -1;
                }
            }else{
                if(sprintf(numChar, "%d ", num) == -1){
                    printf("sprintf failed in writeDiagonalGradient\n");
                    return -1;
                }
            }
            if(fwrite(numChar, strlen(numChar), 1, file) < 1){
                perror("failed to write in writeDiagonalGradient\n");
                return -1;  
            }
            
        }
       
     } 
    
    return 0;
}


int main() {
    char buf[20];
    char* delimiter = " ";
    printf("format for txt file:\n\"imsize\" width height \"type\" type\n");
    printf("where type can either be\n\"rand\" for random\n");
    printf("\"diagonalGrad\" for diagonal gradient\n");
    printf("\"horizontalGrad\" for horizontal gradient\n");
    printf("\"verticalGrad\" for vertical gradient\n");
    printf("example of txt file: imsize 256 256 type diagonalGrad\n");

    while(1){
        printf("Enter name of file(type q to quit): ");
        scanf("%s", buf);
        if(strcmp(buf, "q") == 0){
            printf("quiting...\n");
            return 0;
        }

        FILE* txtFile = fopen(buf, "r");

        if(txtFile == NULL){
            printf("this file doesn't exist\n");
            return 1;
        }

        char buf2[50];
        if(fread(buf2, 1, sizeof(buf2), txtFile) < 0){
            printf("failed to read");
            return 1;
        }

        char *token = strtok(buf2, delimiter);
        if(strcmp(token, "imsize") != 0){
            printf("invalid text format\n");
            return 1;
        }
    
        char *width = strtok(NULL, delimiter);
        char *height = strtok(NULL," ");
        char *type = strtok(NULL, " ");
        if(strcmp(type, "type") == 0){
            type =  strtok(NULL, "\n");
        }
        else{
            printf("type was not included\n");
            return 1;
        }

        fclose(txtFile);

        char* ppm = strtok(buf, ".");
        ppm = strcat(ppm, ".ppm");
        printf("Your new file is : %s\n", ppm);
        //printf("Your height is : %s\n", height);
        FILE* ppmFile = fopen(ppm, "w");

        
        if(writeHeader(ppmFile, width, height) == -1){
            fclose(ppmFile);
            printf("writeHeader failed\n");
            return 1;

        }

        // calls the appropriate functions depending on txt file structure
        if(strcmp(type, "diagonalGrad") == 0){
            if(writeDiagonalGradient(ppmFile, width, height) == -1){
                fclose(ppmFile);
                printf("writeDiagonalGradient failed\n");
                return 1;
            }
        }else if (strcmp(type, "rand") == 0){
            if(writeRandomBody(ppmFile, width, height)==-1){
                fclose(ppmFile);
                printf("writeRandomBody failed\n");
                return 1;
            }
        }else if (strcmp(type, "horizontalGrad") == 0){
            if(writeHorizontalGradient(ppmFile, width, height) == -1){
                fclose(ppmFile);
                printf("writeHorizontalGradient failed\n");
                return 1;
            }
        }else if (strcmp(type, "verticalGrad") == 0){
            if(writeVerticalGradient(ppmFile, width, height) == -1){
                fclose(ppmFile);
                printf("writeVerticalGradient failed\n");
                return 1;
            }
        }
        
        fclose(ppmFile);

    }
    
    return 0;
}