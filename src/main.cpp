#include <iostream>
#include "Image.h"

int main(){
    img::Image image(100,100);
    img::Pixel red{255,0,0};
    image.setPixel(2,1,red);

    const img::Pixel& pixel = image.getPixel(2,1);

    std::cout
        << "Image size: "
        << image.getWidth()
        << " x "
        << image.getHeight()
        << '\n';

    std::cout
        << "Pixel (2, 1): "
        << static_cast<int>(pixel.r)
        << ", "
        << static_cast<int>(pixel.g)
        << ", "
        << static_cast<int>(pixel.b)
        << '\n';

    return 0;
}