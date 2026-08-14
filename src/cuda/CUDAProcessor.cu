#include "CUDAProcessor.h"

#include "CUDAUtils.cuh"
#include "PointFilters.cuh"

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
        cuda_detail::calculateBlocks(
            pixelCount,
            threadsPerBlock
        );

    cuda_detail::invertKernel<<<
        blocks,
        threadsPerBlock
    >>>(
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
        cuda_detail::calculateBlocks(
            pixelCount,
            threadsPerBlock
        );

    cuda_detail::grayscaleKernel<<<
        blocks,
        threadsPerBlock
    >>>(
        devicePixels,
        pixelCount
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}


bool CUDAProcessor::brightness(
    Image& image,
    int amount
)
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
        cuda_detail::calculateBlocks(
            pixelCount,
            threadsPerBlock
        );

    cuda_detail::brightnessKernel<<<
        blocks,
        threadsPerBlock
    >>>(
        devicePixels,
        pixelCount,
        amount
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}


bool CUDAProcessor::contrast(
    Image& image,
    float factor
)
{
    if (factor < 0.0f) {
        return false;
    }

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
        cuda_detail::calculateBlocks(
            pixelCount,
            threadsPerBlock
        );

    cuda_detail::contrastKernel<<<
        blocks,
        threadsPerBlock
    >>>(
        devicePixels,
        pixelCount,
        factor
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}


bool CUDAProcessor::threshold(
    Image& image,
    unsigned char thresholdValue
)
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
        cuda_detail::calculateBlocks(
            pixelCount,
            threadsPerBlock
        );

    cuda_detail::thresholdKernel<<<
        blocks,
        threadsPerBlock
    >>>(
        devicePixels,
        pixelCount,
        thresholdValue
    );

    return cuda_detail::downloadImage(
        image,
        devicePixels,
        bytes
    );
}


}