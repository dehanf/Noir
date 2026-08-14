#include "CUDAProcessor.h"
#include "CUDAUtils.cuh"

#include <cuda_runtime.h>





namespace img {

    
__device__ unsigned char clampChannel(int value)
{
    if (value < 0) {
        return 0;
    }

    if (value > 255) {
        return 255;
    }

    return static_cast<unsigned char>(value);
}

__global__ void invertKernel(
    Pixel* pixels,
    int pixelCount
)
{
    const int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index >= pixelCount) {
        return;
    }

    Pixel& pixel = pixels[index];

    pixel.r = 255 - pixel.r;
    pixel.g = 255 - pixel.g;
    pixel.b = 255 - pixel.b;
}


__global__ void grayscaleKernel(
    Pixel* pixels,
    int pixelCount
)
{
    const int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index >= pixelCount) {
        return;
    }

    Pixel& pixel = pixels[index];

    const unsigned char gray =
        static_cast<unsigned char>(
            0.299f * pixel.r +
            0.587f * pixel.g +
            0.114f * pixel.b
        );

    pixel.r = gray;
    pixel.g = gray;
    pixel.b = gray;
}