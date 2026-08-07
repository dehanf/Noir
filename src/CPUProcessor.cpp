#include "CPUProcessor.h"

namespace img {

unsigned char clampChannel(int value){
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    else {
        return static_cast<unsigned char>(value);
    }
}

void CPUProcessor::invert(Image& image){ //invert the image by subtracting each channel value from 255
    for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = static_cast<unsigned char>(255 - pixel.r);
            pixel.g = static_cast<unsigned char>(255 - pixel.g);
            pixel.b = static_cast<unsigned char>(255 - pixel.b);
        }
    }
}

void CPUProcessor::adjustBrightness(Image& image, int brightness) //adjust the brightness of the image by adding the brightness value to each channel value and clamping the result to the range [0, 255]
    {
        for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = clampChannel(pixel.r + brightness);
            pixel.g = clampChannel(pixel.g + brightness);
            pixel.b = clampChannel(pixel.b + brightness);
        }
    }

}

void CPUProcessor::adjustContrast(Image& image,float contrast)
{
    {
        for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = clampChannel((static_cast<int>(pixel.r)-128)*contrast + 128);
            pixel.g = clampChannel((static_cast<int>(pixel.g)-128)*contrast + 128);
            pixel.b = clampChannel((static_cast<int>(pixel.b)-128)*contrast + 128);

        }
    }

}

}

void CPUProcessor::grayscale(Image& image){
    for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x,y);
            const int gray = static_cast<int>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            const unsigned char grayValue = clampChannel(gray);
            pixel.r = grayValue;
            pixel.g = grayValue;
            pixel.b = grayValue;           
        }
    }
}
void CPUProcessor::threshold(
    Image& image,
    unsigned char thresholdValue
)
{
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel& pixel = image.getPixel(x, y);

            const int intensity = static_cast<int>(
                0.299 * pixel.r +
                0.587 * pixel.g +
                0.114 * pixel.b
            );

            const unsigned char outputValue =
                intensity >= thresholdValue
                    ? 255
                    : 0;

            pixel.r = outputValue;
            pixel.g = outputValue;
            pixel.b = outputValue;
        }
    }
}


}



