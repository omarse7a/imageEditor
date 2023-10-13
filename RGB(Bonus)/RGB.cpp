// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <algorithm>
using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
void menu();
void loadImage();
void saveImage();
void BW();
void invert();
void merge();
void flip();

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
                merge();
                break;
            case '4':
                flip();
                break;
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 's':
                saveImage();
                break;
            default:
                cout << "Invalid input, Try again\n";
        }

        menu();
    }
    return 0;
}

//_________________________________________
void menu(){
    cout << "\nselect a filter to apply or 0 to exit:\n";
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
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the image file name you want to edit: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
    readRGBBMP(imageFileName, image2);

}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_________________________________________
void BW() {
    int sum, avg;
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            sum = 0;
            for (int k = 0; k < RGB; ++k) {
                sum += image[i][j][k];
            }
            avg = sum/RGB;
            if(avg < 128) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 0;
                }
            }
            else{
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                }
            }
        }
    }
}

//_________________________________________
void invert(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

//_________________________________________
void merge(){
    unsigned char imageMrg[SIZE][SIZE][RGB];
    char imageFileName[100];
    cout << "Enter the image file name you to merge with: ";
    cin >> imageFileName;
    strcat(imageFileName, ".BMP");
    readRGBBMP(imageFileName, imageMrg);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = (image[i][j][k] + imageMrg[i][j][k]) / 2;
            }
        }
    }
}

//_________________________________________
void flip() { //This function flips the image horizontally or vertically
    char dir;
    cout << "Flip horizontally(h) or vertically(v)\n";
    cin >> dir;
    if (dir == 'h') {         //if the input is h it flips horizontally
        reverse(begin(image), end(image)); //it reverses the whole 3D array
    }
    else if(dir == 'v'){        //if the input is v it flips vertically
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image2[i][SIZE-j-1][k];  //it reverses the columns of 3D array
                }
            }
        }
    }
}