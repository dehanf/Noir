#ifndef CUDA_PROCESSOR_H
#define CUDA_PROCESSOR_H

#include "Image.h"

namespace img {

class CUDAProcessor {
public:
    static bool invert(Image& image);

    static bool grayscale(Image& image);

    static bool brightness(
        Image& image,
        int amount
    );

    static bool contrast(
        Image& image,
        float factor
    );

    static bool threshold(
        Image& image,
        unsigned char thresholdValue = 128
    );
};

}

#endif