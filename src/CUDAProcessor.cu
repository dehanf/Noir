#include "CUDAProcessor.h"

#include <cuda_runtime.h>
#include <iostream>
#include <cstddef>

namespace img {
bool CUDAProcessor::invert(Image& image)
{
    Pixel* devicePixels = nullptr;
    int pixelCount = 0;
    std::size_t bytes = 0;

    if (!cuda_detail::uploadImage(
            image,
            devicePixels,
            pixelCount,
            bytes
        )) {
        return false;
    }

    const int threadsPerBlock = 256;

    const int blocks =
        (
            pixelCount +
            threadsPerBlock - 1
        )
        / threadsPerBlock;

    invertKernel<<<blocks, threadsPerBlock>>>(
        devicePixels,
        pixelCount
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}

bool CUDAProcessor::grayscale(Image& image)
{
    Pixel* devicePixels = nullptr;
    int pixelCount = 0;
    std::size_t bytes = 0;

    if (!cuda_detail::uploadImage(
            image,
            devicePixels,
            pixelCount,
            bytes
        )) {
        return false;
    }

    const int threadsPerBlock = 256;

    const int blocks =
        (
            pixelCount +
            threadsPerBlock - 1
        )
        / threadsPerBlock;

    grayscaleKernel<<<blocks, threadsPerBlock>>>(
        devicePixels,
        pixelCount
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}


}
