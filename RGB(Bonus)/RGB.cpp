// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: Image Editor for colored images
// Last Modification Date:	18/10/2023
// Author1 and ID and Group:	Omar Sameh Mohamed / 20220224 / omar.seha90@gmail.com
// Author2 and ID and Group:	Mohamed Hisham Zidan / 20220310 / mohamedzidan783@gmail.com
// Author3 and ID and Group:	Seif Eldin Ahmed Elkammar / 20220468 / seif_elkammar@hotmail.com
// Teaching Assistant:		xxxxx xxxxx
// Purpose:..........

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <algorithm>
#include <cmath>

using namespace std;

unsigned char image[SIZE][SIZE][RGB];   //primary image
unsigned char image2[SIZE][SIZE][RGB];  //spare image(for editing)


void menu();
void loadImage();
void copyImage();
void saveImage();
void BW();
void invert();
void mergeImage();
void flip();
void rotateImage();
void DL();
void detectEdge();
void enlarge();
void shrink();
void mirror();
void shuffle();
void blur();
void crop();
void skewRight();
void skewUp();

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
                detectEdge();
                break;
            case '8':
                enlarge();
                break;
            case '9':
                shrink();
                break;
            case 'a':
                mirror();
                break;
            case 'b':
                shuffle();
                break;
            case 'c':
                blur();
                break;
            case 'd':
                crop();
                break;
            case 'e':
                skewRight();
                break;
            case 'f':
                skewUp();
                break;
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
}

//_________________________________________
void copyImage(){               //This function is used to copy the contents of image(array) to image2(array)
    for (int i = 0; i < SIZE; ++i) {    //used to implement some filters
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
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
void BW() {     //This function turns the RGB image to the black & white version
    int sum, avg;
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            sum = 0;
            for (int k = 0; k < RGB; ++k) { //looping to find the average color of each pixel
                sum += image[i][j][k];  //sum of colors in each pixel
            }
            avg = sum/RGB;  //calculating the average
            if(avg < 128) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 0; //turn the pixel to black if the average color is less than 128
                }                       //for each pixel
            }
            else{
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;   //turn the pixel to white if the average color is greater than 128
                }                           //for each pixel
            }
        }
    }
}

//_________________________________________
void invert(){  //This function invert the brightness of each pixel
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255 - image[i][j][k]; //invert each color in a pixel
            }
        }
    }
}

//_________________________________________
void mergeImage(){      //This function merges two images together
    unsigned char imageMrg[SIZE][SIZE][RGB];
    char imageFileName[100];
    cout << "Enter the image file name you to merge with: ";
    cin >> imageFileName;
    strcat(imageFileName, ".BMP");
    readRGBBMP(imageFileName, imageMrg);  //loading another image for the merge
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = (image[i][j][k] + imageMrg[i][j][k]) / 2;  //replacing each pixel with the average brightness of the two images
            }
        }
    }
}

//_________________________________________
void flip() { //This function flips the image horizontally or vertically
    copyImage();
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

//_________________________________________
void rotateImage(){ //This function rotates the image by a given degrees
    copyImage();
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

//_________________________________________
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
                    image[i][j][k] =(255+image[i][j][k])*0.5;
                }
            }
        }
    }
}

//_________________________________________
void detectEdge(){      //This function detect the edges of every object in the image
    int sum, avg1, avg2, avg3;
    for (int i = 1; i < SIZE-1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            sum = 0;
            for (int k = 0; k < RGB; ++k) {
                sum += image[i][j][k];
            }
            avg1 = sum/RGB; //calculating the average of edge pixel colors to get the grey scale version
            sum = 0;
            for (int k = 0; k < RGB; ++k) {
                sum += image[i][j+1][k];
            }
            avg2 = sum/RGB; //calculating the average of the pixel(one column after edge pixel) colors to get the grey scale version
            sum = 0;
            for (int k = 0; k < RGB; ++k) {
                sum += image[i+1][j][k];
            }
            avg3 = sum/RGB; //calculating the average of the pixel(one row after edge pixel) colors to get the grey scale version
            int brightDiffX = abs(avg1 - avg2); //the brightness difference on x-axis
            int brightDiffY = abs(avg1 - avg3); //the brightness difference on y-axis
            if (brightDiffX > 30 || brightDiffY > 30)   // checking if the pixel is an edge by brightness difference
                for (int k = 0; k < RGB; ++k) {        //30 is not a special number it just gives the best results)
                    image[i][j][k] = 0;
                }
            else
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                }
        }
    }
}

//_________________________________________
void enlarge(){     //Enlarge the pixel by repeating it four times in the image array
    copyImage();
    int quarter;
    cout << "Select a quarter to enlarge first(1), second(2), third(3), fourth(4)\n";
    cin >> quarter;
    if(quarter == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {       //indices i/2 and j/2 to get the first quarter only
                for (int k = 0; k < RGB; ++k) {        //and repeating the same pixel twice in each row
                    image[i][j][k] = image2[i/2][j/2][k];   //and repeating it twice in each column
                }
            }
        }
    }
    else if(quarter == 2){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {       //indices i/2 and SIZE/2 + j/2 to get the second quarter only
                for (int k = 0; k < RGB; ++k) {     //and repeating the same pixel twice in each row
                    image[i][j][k] = image2[i/2][SIZE/2 + j/2][k]; //and repeating it twice in each column
                }
            }
        }
    }
    else if(quarter == 3){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {            //indices SIZE/2 + i/2 and j/2 to get the third quarter only
                for (int k = 0; k < RGB; ++k) {             //and repeating the same pixel twice in each row
                    image[i][j][k] = image2[SIZE/2 + i/2][j/2][k];    //and repeating it twice in each column
                }
            }
        }
    }
    else if(quarter == 4){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {            //indices SIZE/2 + i/2 and SIZE/2 + j/2 to get the fourth quarter only
                for (int k = 0; k < RGB; ++k) {             //and repeating the same pixel twice in each row
                    image[i][j][k] = image2[SIZE/2 + i/2][SIZE/2 + j/2][k];   //and repeating it twice in each column
                }
            }
        }
    }
}

//_________________________________________
void shrink(){      //Shrink image by skipping pixels
    copyImage();
    int scale;
    cout << "Shrink to half(1), third(2) or quarter(3) it's original dimensions?\n";
    cin >> scale;
    for (int i = 0; i < SIZE; ++i) {        //making the primary image all white
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;
            }
        }
    }
    if(scale == 1){
        for (int i = 0; i < SIZE; i+=2) {       //shrink to half its original dimensions
            for (int j = 0; j < SIZE; j+=2) {   //for each pixel of the original image we put
                for (int k = 0; k < RGB; ++k) {
                    image[i/2][j/2][k] = image2[i][j][k]; //a pixel in shrunk image and skip the next
                }
            }
        }
    }
    else if(scale == 2){
        for (int i = 0; i < SIZE; i+=3) {       //shrink to third its original dimensions
            for (int j = 0; j < SIZE; j+=3) {   //for each pixel of the original image we put
                for (int k = 0; k < RGB; ++k) {
                    image[i/3][j/3][k] = image2[i][j][k]; //a pixel in shrunk image and skip the next two pixels
                }
            }
        }
    }
    else if(scale == 3){
        for (int i = 0; i < SIZE; i+=4) {       //shrink to quarter its original dimensions
            for (int j = 0; j < SIZE; j+=4) {   //for each pixel of the original image we put
                for (int k = 0; k < RGB; ++k) {
                    image[i/4][j/4][k] = image2[i][j][k]; //a pixel in shrunk image and skip the next three pixels
                }
            }
        }
    }
}
//_______________________________________
void mirror() {//This filter mirrors 1/2 of the image as seen here in order: Left 1/2, Right 1/2, Upper 1/2 and Lower 1/2.
    copyImage();
    cout << "Mirror left(l), right(r), upper(u), down(d)\n";
    char side;
    cin >> side;
    if (side == 'l') {
        for (int i = 0; i < SIZE; ++i) {        //we put the first half of the image in image1
            for (int j = 0;
                 j < SIZE / 2; ++j) {// then put the first half of the image again in the second half of image1.
                for (int k = 0; k < RGB; ++k) {
                    image[i][SIZE - j][k] = image2[i][j][k];
                }
            }
        }
    } else if (side == 'r') {//Here we did the same thing, but in reverse.
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][SIZE - j][k] = image2[i][j][k];
                }
            }
        }
    } else if (side == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) {//here we need the upper half of i indices
            for (int j = 0; j < SIZE; ++j) {//and we put that in reverse in the second half of the image
                for (int k = 0; k < RGB; ++k) {
                    image[SIZE - i][j][k] = image2[i][j][k];
                }
            }
        }
    } else
        for (int i = SIZE / 2; i < SIZE; ++i) {//here we need the lower half of the image
            for (int j = 0; j < SIZE; ++j) {//and we put that in reverse in the second half of the image
                for (int k = 0; k < RGB; ++k) {
                    image[SIZE - i][j][k] = image2[i][j][k];
                }
            }
        }
}
//_______________________________________
void shuffle(){     //shuffle function is used to display the image quarters in any order
    copyImage();
    int order, pos = 1;
    cout << "Enter the new order of quarters?\n";
    while(pos <= 4) {   //looping on every quarter
        cin >> order;   //if the order is equal to pos, then leave the quarter as it is
        if(pos == 1) { //first quarter
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        if (order == 2) {
                            image[i][j][k] = image2[i][SIZE / 2 +j][k];    //replacing the first quarter with the second
                        } else if (order == 3) {
                            image[i][j][k] = image2[SIZE / 2 + i][j][k];    //replacing the first quarter with the third
                        } else if (order == 4) {
                            image[i][j][k] = image2[SIZE / 2 + i][SIZE / 2 +j][k];   //replacing the first quarter with the fourth
                        }
                    }
                }
            }
        }
        else if(pos == 2) { //second quarter
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = SIZE / 2; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        if (order == 1) {
                            image[i][j][k] = image2[i][j -
                                                       SIZE / 2][k];    //replacing the second quarter with the first
                        } else if (order == 3) {
                            image[i][j][k] = image2[SIZE / 2 + i][j - SIZE /2][k];   //replacing the second quarter with the third
                        } else if (order == 4) {
                            image[i][j][k] = image2[SIZE / 2 +i][j][k];    //replacing the second quarter with the fourth
                        }
                    }
                }
            }
        }
        else if(pos == 3) {  //third quarter
            for (int i = SIZE / 2; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        if (order == 1) {
                            image[i][j][k] = image2[i - SIZE / 2][j][k];    //replacing the third quarter with the first
                        } else if (order == 2) {
                            image[i][j][k] = image2[i - SIZE / 2][SIZE / 2 +j][k];   //replacing the third quarter with the second
                        } else if (order == 4) {
                            image[i][j][k] = image2[i][SIZE / 2 +j][k];    //replacing the third quarter with the fourth
                        }
                    }
                }
            }
        }
        else {   //fourth quarter
            for (int i = SIZE / 2; i < SIZE; ++i) {
                for (int j = SIZE / 2; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        if (order == 1) {
                            image[i][j][k] = image2[i - SIZE / 2][j - SIZE /2][k];   //replacing the fourth quarter with the first
                        } else if (order == 2) {
                            image[i][j][k] = image2[i - SIZE / 2][j][k];    //replacing the fourth quarter with the second
                        } else if (order == 3) {
                            image[i][j][k] = image2[i][j - SIZE / 2][k];    //replacing the fourth quarter with the third
                        }
                    }
                }
            }
        }
        pos++;
    }
}

//_________________________________________
void blur() {    //The blur filter takes the average of the 9 pixels and put it in the middle pixel
    for (int c = 0; c < 3; ++c) { //this loop repeats the process 3 times to make it more blurry
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = (image[i - 1][j][k]+ image[i + 1][j][k] + image[i][j - 1][k] + image[i][j + 1][k] + image[i][j][k]
                                      + image[i - 2][j][k] + image[i + 2][j][k] + image[i][j - 2][k] + image[i][j + 2][k]) / 9;
                }
            }
        }
    }
}

//_________________________________________
void crop() {   //here we crop part of the image and make the rest white.
    copyImage();
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
//_______________________________________
void skewRight(){       //Skewing the image vertically  by the given angle
    copyImage();
    double degree, rad, x, move, step;
    cout << "Enter the skewing degree\n";
    cin >> degree;
    rad = (degree*(22.0/7.0)) /180.0; //calculating the angle in radian
    x = SIZE / (1 + 1/tan(rad));    //the dimension(columns) after shrinking
    step = ceil(SIZE - x);      //the pixels starting point in each row
    move = step/SIZE;     //the value of movement to the left in each row
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;      //making the primary image all white
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][int(j*(x/SIZE)) + int(step)][k] = image2[i][j][k];   //using j*(x/SIZE) for shrinking the image to fit in x columns
            }                                                        //adding (step) to it to make a starting point for the pixels in each row
        }
        step -= move; //decrementing step for each row
    }
}

//_________________________________________
void skewUp(){      //Skewing the image horizontally by the given angle
    copyImage();
    double degree, rad, x, move, step;
    cout << "Enter the skewing degree\n";
    cin >> degree;
    rad = (degree*(22.0/7.0)) /180.0; //calculating the angle in radian
    x = SIZE / (1 + 1/tan(rad));    //the dimension(rows) after shrinking
    step = ceil(SIZE - x);      //the pixels starting point in each column
    move = step/SIZE;     //the value of movement up in each column
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;      //making the primary image all white
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        step = ceil(SIZE - x);
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {             //using i*(x/SIZE) for shrinking the image to fit in x rows
                image[int(i*(x/SIZE) + int(step))][j][k] = image2[i][j][k];   //adding (step) to it to make a starting point for the pixels in each column
            }
            step -= move;    //decrementing step for each column
        }
    }
}