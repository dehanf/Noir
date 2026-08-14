#ifndef CUDA_PROCESSOR_H
#define CUDA_PROCESSOR_H

#include "Image.h"

namespace img {

class CUDAProcessor {
public:
    static bool invert(Image& image);
    static bool grayscale(Image& image);
};

}

#endif