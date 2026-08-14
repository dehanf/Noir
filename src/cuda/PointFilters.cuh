#ifndef POINT_FILTERS_CUH
#define POINT_FILTERS_CUH

#include "Pixel.h"

namespace img {
namespace cuda_detail {

__global__ void invertKernel(
    Pixel* pixels,
    int pixelCount
);

__global__ void grayscaleKernel(
    Pixel* pixels,
    int pixelCount
);

__global__ void brightnessKernel(
    Pixel* pixels,
    int pixelCount,
    int amount
);

__global__ void contrastKernel(
    Pixel* pixels,
    int pixelCount,
    float factor
);

__global__ void thresholdKernel(
    Pixel* pixels,
    int pixelCount,
    unsigned char thresholdValue
);

}
}

#endif