#include "Image.h"

namespace img{


Image::Image(int width,int height){
    this->width = width;
    this->height = height;
    this->pixels = new Pixel[width * height];
}

/*  
Image::Image(int,width,int height):width{width},
 height{height},
  pixels{new Pixel[width * height]{}};
*/

Image::~Image(){ //destructor
    delete[] pixels;
}

int Image::getWidth() const{
    return width;
}

int Image::getHeight() const{
    return height;
}

Pixel& Image::getPixel(int x,int y){
    return pixels[y*width+x];

}

const Pixel& Image::getPixel(int x,int y) const{
    return pixels[y*width+x];
}

void Image::setPixel(int x, int y, const Pixel& pixel){
    pixels[y*width + x] = pixel;

}


}