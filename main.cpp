#include <iostream>
#include <cstring>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];


void menu();
void loadImage();
void saveImage();
void BW();
void invert();
void merge();
void flip();
void rotate();

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
    cout << "\t5-Darken and Lighten Image \n";
    cout << "\t6-Rotate Image\n";
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
void merge(){
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
                swap(image[i][j], image[i][SIZE-j-1]);
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
void rotate(){
    
}

//_________________________________________