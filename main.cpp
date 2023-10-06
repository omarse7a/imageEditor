#include <iostream>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];


void menu();
void loadImage();
void saveImage();
void BW();
void invert();
void mergeImage();
void flip();
void rotateImage();
void DL();

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
void loadImage(){
    char imageFileName[100];
    cout << "Enter the image file name you want to edit: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
    readGSBMP(imageFileName, image2);
}

//_________________________________________
void saveImage(){
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void BW(){
    int sum = 0, avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            sum += image[i][j];
        }
    }
    avg = sum/(SIZE*SIZE);
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
void invert(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

//_________________________________________
void mergeImage(){
    unsigned char imageMerge[SIZE][SIZE];
    char imageFileName[100];
    cout << "Enter the image file name you to merge with: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, imageMerge);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + imageMerge[i][j])/2;
        }
    }
}

//_________________________________________
void flip(){
    char dir;
    cout << "Flip horizontally(h) or vertically(v)\n";
    cin >> dir;
    if(dir == 'h'){
        reverse(begin(image), end(image));
    }
    else if(dir == 'v'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                swap(image[i][j], image2[i][SIZE-j-1]);
            }
        }
    }
}

//_________________________________________
void rotateImage(){
    int degree;
    cout << "Rotate (90), (180) or (270) degrees\n";
    cin >> degree;
    if(degree == 90) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[j][SIZE-i-1];
            }
        }
    }
    else if(degree == 180){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[SIZE-i-1][SIZE-j-1];
            }
        }
    }
    else if(degree == 270){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[SIZE-j-1][i];
            }
        }
    }
}

//_________________________________________
void DL(){
    char brightness;
    cout << "Do you want to darken(d) or lighten(l)?\n";
    cin >> brightness;
    if(brightness == 'd'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j]/2;
            }
        }
    }
    else if(brightness == 'l'){
        for (int i = 0; i < SIZE; ++i) {
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
