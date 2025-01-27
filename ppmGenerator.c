#include "ppmGenerator.h"

int writeHeader(FILE* file, char* width, char* height){
    char* p3 = "P3\n";
    fwrite(p3, strlen(p3), 1, file);

    char widthAndHeight[30] = "";
    char* resultString = strcat(widthAndHeight, width);
    resultString = strcat(widthAndHeight, " ");
    resultString = strcat(widthAndHeight, height);
    resultString = strcat(widthAndHeight, "\n");
    resultString = strcat(widthAndHeight, "255");
    resultString = strcat(widthAndHeight, "\n");

    fwrite(resultString, strlen(resultString), 1, file);

    return 0;
}

int writeRandomBody(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    
    int numHeight = atoi(height);
    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

     for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];
        for(int j = 0; j < 3 * numWidth-1; j++){
            num = rand()%256;
            sprintf(numChar, "%d ", num);
            fwrite(numChar, strlen(numChar), 1, file);
        }
        sprintf(numChar, "%d\n", num);
        fwrite(numChar, strlen(numChar), 1, file);
     }
    return 0;
}

int writeHorizontalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

     for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];
        for(int j = 0; j < 3 * numWidth-1; j++){
            num = j/3;
            sprintf(numChar, "%d ", num);
            fwrite(numChar, strlen(numChar), 1, file);
        }
        num++;
        sprintf(numChar, "%d\n", num);
        fwrite(numChar, strlen(numChar), 1, file);
     }
    return 0;
}

int writeVerticalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

     for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];
        for(int j = 0; j < 3 * numWidth-1; j++){
            num = i;
            sprintf(numChar, "%d ", num);
            fwrite(numChar, strlen(numChar), 1, file);
        }
        num++;
        sprintf(numChar, "%d\n", num);
        fwrite(numChar, strlen(numChar), 1, file);
     }
    return 0;
}

int writeDiagonalGradient(FILE* file, char* width, char* height){
    int numWidth = atoi(width);
    int numHeight = atoi(height);

    printf("%d\n", numWidth);
    printf("%d\n", numHeight);

    int imageArray[numHeight][3*numWidth];
    printf("hello");

    float xScalingFactor = 256.0/(numWidth);
    float yScalingFactor = 256.0/numHeight;
    printf("xScaling %f\n", xScalingFactor);
    printf("yScaling %f\n", yScalingFactor);
    // if(xScalingFactor <= 0){
    //     xScalingFactor = 1;
    // }
    // if(yScalingFactor <= 0){
    //     yScalingFactor = 1;
    // }

    for(int i = 0; i < numHeight; i++){
        for(int j = 0; j < 3 * numWidth; j++){
            if(i>=j/3){
                imageArray[i][j] = (int)(yScalingFactor * i);
            }else{
                imageArray[i][j] = (int)(xScalingFactor* j/3);
            }
            
        }
     } 

    for(int i = 0; i < numHeight; i++){
        int num;
        char numChar[5];
        num = i;
        for(int j = 0; j < 3 * numWidth-1; j++){
            num = imageArray[i][j];
            sprintf(numChar, "%d ", num);
            fwrite(numChar, strlen(numChar), 1, file);
            
        }
        num = imageArray[i][3 * numWidth-1];
        sprintf(numChar, "%d\n", num);
        fwrite(numChar, strlen(numChar), 1, file);
       
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
        fread(buf2, 1, sizeof(buf2), txtFile);

        

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

        
        writeHeader(ppmFile, width, height);
        if(strcmp(type, "diagonalGrad") == 0){
            writeDiagonalGradient(ppmFile, width, height);
        }else if (strcmp(type, "rand") == 0)
        {
            writeRandomBody(ppmFile, width, height);
        }else if (strcmp(type, "horizontalGrad") == 0)
        {
            writeHorizontalGradient(ppmFile, width, height);
        }else if (strcmp(type, "verticalGrad") == 0)
        {
            writeVerticalGradient(ppmFile, width, height);
        }
        

        fclose(ppmFile);

    }
    
    return 0;
}