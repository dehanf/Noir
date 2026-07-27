#ifndef IMAGE_H
#define IMAGE_H

#include "Pixel.h"

namespace img {

class Image{

private:
    int width;
    int height;

    Pixel* pixels;
public:
    Image(int width, int height); //constructor

    ~Image(); //destructor

    int getWidth() const; //getter
    int getHeight() const; //getter

    Pixel& getPixel(int x,int y);

    const Pixel& getPixel(int x,int y) const;
    //first const is for the reference  second is for the function
    // 1. returned object is const
    // 2. The function does not modify the object

    void setPixel(int x,int y, const Pixel& pixel); // set the pixel to x,y without modifyin gthe pixel





    };
}

#endif