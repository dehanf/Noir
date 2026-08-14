#ifndef CUDA_UTILS_CUH
#define CUDA_UTILS_CUH

#include <cuda_runtime.h>

#include <cstddef>
#include <iostream>

#include "Image.h"

namespace img {
namespace cuda_detail {


inline bool uploadImage(
    Image& image,
    Pixel*& devicePixels,
    int& pixelCount,
    std::size_t& bytes
)
{
    const int width = image.getWidth();
    const int height = image.getHeight();

    if (
        width <= 0 ||
        height <= 0 ||
        image.data() == nullptr
    ) {
        return false;
    }

    pixelCount = width * height;

    bytes =
        static_cast<std::size_t>(pixelCount)
        * sizeof(Pixel);

    cudaError_t error =
        cudaMalloc(
            reinterpret_cast<void**>(&devicePixels),
            bytes
        );

    if (error != cudaSuccess) {
        std::cerr
            << "cudaMalloc failed: "
            << cudaGetErrorString(error)
            << '\n';

        return false;
    }

    error = cudaMemcpy(
        devicePixels,
        image.data(),
        bytes,
        cudaMemcpyHostToDevice
    );

    if (error != cudaSuccess) {
        std::cerr
            << "CPU -> GPU copy failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        devicePixels = nullptr;

        return false;
    }

    return true;
}


inline bool downloadImage(
    Image& image,
    Pixel* devicePixels,
    std::size_t bytes
)
{
    cudaError_t error =
        cudaGetLastError();

    if (error != cudaSuccess) {
        std::cerr
            << "Kernel launch failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        return false;
    }

    error = cudaDeviceSynchronize();

    if (error != cudaSuccess) {
        std::cerr
            << "Kernel execution failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        return false;
    }

    error = cudaMemcpy(
        image.data(),
        devicePixels,
        bytes,
        cudaMemcpyDeviceToHost
    );

    if (error != cudaSuccess) {
        std::cerr
            << "GPU -> CPU copy failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        return false;
    }

    cudaFree(devicePixels);

    return true;
}


inline int calculateBlocks(
    int pixelCount,
    int threadsPerBlock
)
{
    return (
        pixelCount +
        threadsPerBlock - 1
    ) / threadsPerBlock;
}


}
}

#endif