#include "Image.h"

namespace img{

Image::Image()
    : width{0},
      height{0},
      pixels{nullptr}
{
}

Image::Image(int width,int height){
    this->width = width;
    this->height = height;
    this->pixels = new Pixel[width * height];
}

Image::Image(const Image& other):width{other.width},height{other.height},pixels{nullptr}{ //copy constructor
    if (other.pixels != nullptr){
        pixels = new Pixel[width * height];
        
        for(int i=0;i<width*height;i++){
            pixels[i] = other.pixels[i];
        }
    }
}

Image& Image::operator=(const Image& other) //copy assignment
{
    if (this == &other) {
        return *this;
    }

    Pixel* newPixels = nullptr;

    if (other.pixels != nullptr) {
        newPixels =
            new Pixel[other.width * other.height];

        for (
            int i = 0;
            i < other.width * other.height;
            ++i
        ) {
            newPixels[i] = other.pixels[i];
        }
    }

    delete[] pixels;

    pixels = newPixels;
    width = other.width;
    height = other.height;

    return *this;
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

bool Image::resizeImage(
    int newWidth,
    int newHeight
)
{
    if (newWidth <= 0 || newHeight <= 0) {
        return false;
    }

    Pixel* newPixels =
        new Pixel[newWidth * newHeight]{}; //first allocate the memory for the new pixel array

    delete[] pixels; //delete the old pixel array to avoid memory leak

    pixels = newPixels; //assign the new pixel array to the pixels member variable
    width = newWidth;
    height = newHeight;

    return true;
}

Pixel* Image::data(){
    return pixels;

}
const Pixel* Image::data() const{
    return pixels;
}

