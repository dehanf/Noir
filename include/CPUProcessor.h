#ifndef CPU_PROCESSOR_H
#define CPU_PROCESSOR_H

#include "Image.h"

namespace img{

class CPUProcessor{

public:
    static void grayscale(Image& image);
    static void invert(Image& image);

    static void adjustBrightness(Image& image, int brightness);

    static void adjustContrast(Image& image, float contrast);

    static void threshold(Image& image, unsigned char threshold=128);

    // convolution filters
    static void boxBlur(Image& image);
    static void gaussianBlur(Image& image);
    static void sharpen(Image& image);
    static void sobelEdgeDetection(Image& image);


private:

    static unsigned char clamp(int value); // clamping stays private because it is a helper function that is only used internally by the class methods
    // double uses 8 bytes, but unsigned char uses only 1 byte

    static void applyKernel3x3(Image& image, const int kernel[3][3], int divisor);
};
}


#endif 