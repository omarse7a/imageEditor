#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <algorithm>

using namespace std;

unsigned char image[SIZE][SIZE][RGB];   //primary image
unsigned char image2[SIZE][SIZE][RGB];  //spare image(for editing)


void menu();
void loadImage();
void saveImage();
void BW();
void invert();
void mergeImage();
void flip();
void rotateImage();
void DL();
void blur();
void crop();


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
                blur();
                break;
            case 'd':
                crop();
                break;
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
void loadImage(){   //This function is used to load the primary RGB image and a spare RGB image for editing
    char imageFileName[100];
    cout << "Enter the image file name you want to edit: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image); //load the image into a 3D array
    readRGBBMP(imageFileName, image2);  //load the image into a 3D array
}

//_________________________________________
void saveImage(){   //This function is used to save the RGB image after implementing filters in a new file
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);   //save the 3D array into an image
    cout << "Save successfully\n";
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
void mergeImage(){
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

//____________________________________________
void rotateImage(){ //This function rotates the image by a given degrees
    int degree;
    cout << "Rotate (90), (180) or (270) degrees\n";
    cin >> degree;
    if(degree == 90) {
        for (int i = 0; i < SIZE; ++i) {    //replacing each row(starting from first row) with the corresponding column(starting from last column)
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image2[j][SIZE-i-1][k];
                }
            }
        }
    }
    else if(degree == 180){     //replacing each row(starting from first row) with the reversed corresponding row(starting from last row)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image2[SIZE-i-1][SIZE-j-1][k];
                }
            }
        }
    }
    else if(degree == 270){     //replacing each row(starting from first row) with the reversed corresponding column(starting from first column)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image2[SIZE-j-1][i][k];
                }
            }
        }
    }
}

//___________________________________________
void DL(){      //This function manipulates the brightness
    char brightness;
    cout << "Do you want to darken(d) or lighten(l)?\n";
    cin >> brightness;
    if(brightness == 'd'){      //decrease the brightness of each pixel to 50% of the original;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][j][k]/2;
                }
            }
        }
    }
    else if(brightness == 'l'){     //if 150% of the original brightness > white(255) make it white
        for (int i = 0; i < SIZE; ++i) {    // else increase the brightness by 50%
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    if(1.5*image[i][j][k] < 255)
                        image[i][j][k] += image[i][j][k] / 2;
                    else
                        image[i][j][k] = 255;
                }
            }
        }
    }
}

//___________________________________________
void blur() {    //The blur filter takes the average of the 9 pixels and put it in the middle pixel
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {

                image[i][j][k] = (image[i - 1][j][k]+ image[i + 1][j][k] + image[i][j - 1][k] + image[i][j + 1][k] + image[i][j][k]
                                  + image[i - 2][j][k] + image[i + 2][j][k] + image[i][j - 2][k] + image[i][j + 2][k]) / 9;
            }
        }
    }
}

//____________________________________________
void crop() {
    cout << "Please enter coordinates (x, y) and length(l), width(w)\n";
    int x, y, l, w;
    cin >> x >> y >> l >> w;    //entering the positions.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;    //here i made the whole image white first.
                if (i >= x && l + x > i && j >= y && w + y > j)    //first & third conditions to make the image white tell i,j come to the x,y positions
                    image[i][j][k] = image2[i][j][k];   //second & last conditions to put the pixels from image2 in image.
            }
        }
    }
}