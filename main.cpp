// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:    main.cpp
// Last Modification Date:	7/10/2023
// Author1 and ID and Group:	Omar Sameh / 20220224
// Author2 and ID and Group:	Mohamed Hisham / 20220310
// Author3 and ID and Group:	Seif Eldin Ahmed Elkammar / 20220468
// Teaching Assistant:		xxxxx xxxxx
// Purpose:..........

#include <iostream>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];    //primary image
unsigned char image2[SIZE][SIZE];   //spare image(for editing)


void menu();
void loadImage();
void saveImage();
void BW();
void invert();
void mergeImage();
void flip();
void rotateImage();
void DL();
void detectEdge();  //msh sha8ala
void enlarge();
void shrink();

int main()
{
    cout << "Welcome to our image editing program\n";
    loadImage();
    menu();
    char op;
    while(cin >> op, op != '0'){
        switch (op) {
            case '1':
                BW();
                break;
            case '2':
                invert();
                break;
            case '3':
                mergeImage();
                break;
            case '4':
                flip();
                break;
            case '5':
                rotateImage();
                break;
            case '6':
                DL();
                break;
            case '7':
                detectEdge(); //msh sha8ala
                break;
            case '8':
                enlarge();
                break;
            case '9':
                shrink();
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 's':
                saveImage();
                break;
        }

        menu();
    }
    return 0;
}

//_________________________________________
void menu(){
    cout << "select a filter to apply or 0 to exit:\n";
    cout << "\n\t1-Black & White Filter\n";
    cout << "\t2-Invert Filter\n";
    cout << "\t3-Merge Filter \n";
    cout << "\t4-Flip Image\n";
    cout << "\t5-Rotate Image\n";
    cout << "\t6-Darken and Lighten Image\n";
    cout << "\t7-Detect Image Edges \n";
    cout << "\t8-Enlarge Image\n";
    cout << "\t9-Shrink Image\n";
    cout << "\ta-Mirror 1/2 Image\n";
    cout << "\tb-Shuffle Image\n";
    cout << "\tc-Blur Image\n";
    cout << "\td-Crop Image\n";
    cout << "\te-Skew Image Right  \n";
    cout << "\tf-Skew Image Up  \n";
    cout << "\ts-Save the image to a file\n";
    cout << "\t0-Exit\n";
}

//_________________________________________
void loadImage(){   //This function is used to load the primary image and a spare image for editing
    char imageFileName[100];
    cout << "Enter the image file name you want to edit: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
    readGSBMP(imageFileName, image2);
}

//_________________________________________
void saveImage(){   //This function is used to save the image after implementing filters in a new file
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void BW(){      //This function turns the image to black&white version
    int sum = 0, avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            sum += image[i][j];
        }
    }
    avg = sum/(SIZE*SIZE);      //calculating the average brightness of the pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++){
            if(image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

//_________________________________________
void invert(){      //This function invert the brightness of each pixel
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

//_________________________________________
void mergeImage(){      //This function merges two images together
    unsigned char imageMerge[SIZE][SIZE];
    char imageFileName[100];
    cout << "Enter the image file name you to merge with: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, imageMerge); //loading another image for the merge
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + imageMerge[i][j])/2; //calculating the average brightness of the two images
        }
    }
}

//_________________________________________
void flip(){        //This function flips the image horizontally or vertically
    char dir;
    cout << "Flip horizontally(h) or vertically(v)\n";
    cin >> dir;
    if(dir == 'h'){         //if the input is h it flips horizontally
        reverse(begin(image), end(image)); //it reverses the whole 2D array
    }
    else if(dir == 'v'){        //if the input is v it flips vertically
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[i][SIZE-j-1];  //it reverses the columns of 2D array
            }
        }
    }
    else{
        cout << "Invalid input!\n";
        flip();
        return;
    }
}

//_________________________________________
void rotateImage(){ //This function rotates the image by a given degrees
    int degree;
    cout << "Rotate (90), (180) or (270) degrees\n";
    cin >> degree;
    if(degree == 90) {
        for (int i = 0; i < SIZE; ++i) {    //replacing each row(starting from first row) with the corresponding column(starting from last column)
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[j][SIZE-i-1];
            }
        }
    }
    else if(degree == 180){     //replacing each row(starting from first row) with the reversed corresponding row(starting from last row)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[SIZE-i-1][SIZE-j-1];
            }
        }
    }
    else if(degree == 270){     //replacing each row(starting from first row) with the reversed corresponding column(starting from first column)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[SIZE-j-1][i];
            }
        }
    }
}

//_________________________________________
void DL(){      //This function manipulates the brightness
    char brightness;
    cout << "Do you want to darken(d) or lighten(l)?\n";
    cin >> brightness;
    if(brightness == 'd'){      //decrease the brightness of each pixel to 50% of the original;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j]/2;
            }
        }
    }
    else if(brightness == 'l'){     //if 150% of the original brightness > white(255) make it white
        for (int i = 0; i < SIZE; ++i) {    // else increase the brightness by 50%
            for (int j = 0; j < SIZE; ++j) {
                if(1.5*image[i][j] < 255)
                    image[i][j] += image[i][j]/2;
                else
                    image[i][j] = 255;
            }
        }
    }
}

//_________________________________________
void detectEdge(){            //msh sha8ala
    for (int i = 1; i < SIZE-1; ++i) {
        for (int j = 1; j < SIZE-1; ++j) {
            int brightDiffX = abs(image[i][j-1] - image[i][j+1]);
            int brightDiffY = abs(image[i-1][j] - image[i+1][j]);
            if(brightDiffX + brightDiffY > 256)
                image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }
}

//_________________________________________
void enlarge(){     //Enlarge the pixel by repeating it four times in the image array
    int quarter;
    cout << "Select a quarter to enlarge first(1), second(2), third(3), fourth(4)\n";
    cin >> quarter;
    if(quarter == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {       //indices i/2 and j/2 to get the first quarter only
                image[i][j] = image2[i/2][j/2];    //and repeating the same pixel twice in each row
            }                                      //and repeating it twice in each column
        }
    }
    else if(quarter == 2){
        for (int i = 0; i < SIZE; ++i) {        //indices i/2 and SIZE/2 + j/2 to get the second quarter only
            for (int j = 0; j < SIZE; ++j) {        //and repeating the same pixel twice in each row
                image[i][j] = image2[i/2][SIZE/2 + j/2]; //and repeating it twice in each column
            }
        }
    }
    else if(quarter == 3){
        for (int i = 0; i < SIZE; ++i) {        //indices SIZE/2 + i/2 and j/2 to get the third quarter only
            for (int j = 0; j < SIZE; ++j) {        //and repeating the same pixel twice in each row
                image[i][j] = image2[SIZE/2 + i/2][j/2];    //and repeating it twice in each column
            }
        }
    }
    else if(quarter == 4){
        for (int i = 0; i < SIZE; ++i) {        //indices SIZE/2 + i/2 and SIZE/2 + j/2 to get the fourth quarter only
            for (int j = 0; j < SIZE; ++j) {        //and repeating the same pixel twice in each row
                image[i][j] = image2[SIZE/2 + i/2][SIZE/2 + j/2];   //and repeating it twice in each column
            }
        }
    }
}

//_________________________________________
void shrink(){      //Shrink image by skipping pixels
    int scale;
    cout << "Shrink to half(1), third(2) or quarter(3) it's original dimensions?\n";
    cin >> scale;
    for (int i = 0; i < SIZE; ++i) {        //making the primary image all white
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }
    if(scale == 1){
        for (int i = 0; i < SIZE; i+=2) {       //shrink to half its original dimensions
            for (int j = 0; j < SIZE; j+=2) {   //for each pixel of the original image we put
                image[i/2][j/2] = image2[i][j]; //a pixel in shrunk image and skip the next
            }
        }
    }
    else if(scale == 2){
        for (int i = 0; i < SIZE; i+=3) {       //shrink to third its original dimensions
            for (int j = 0; j < SIZE; j+=3) {   //for each pixel of the original image we put
                image[i/3][j/3] = image2[i][j]; //a pixel in shrunk image and skip the next two pixels
            }
        }
    }
    else if(scale == 3){
        for (int i = 0; i < SIZE; i+=4) {       //shrink to quarter its original dimensions
            for (int j = 0; j < SIZE; j+=4) {   //for each pixel of the original image we put
                image[i/4][j/4] = image2[i][j]; //a pixel in shrunk image and skip the next three pixels
            }
        }
    }
}

//_________________________________________