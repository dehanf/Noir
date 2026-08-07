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

private:

    static unsigned char clamp(int value); // clamping stays private because it is a helper function that is only used internally by the class methods
    // double uses 8 bytes, but unsigned char uses only 1 byte
};
}


#endif CPU_PROCESSOR_H