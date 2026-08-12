#include "CUDAProcessor.h"

#include <cuda_runtime.h>
#include <iostream>
#include <cstddef>

namespace img {

__global__ void invertKernel(
    Pixel* pixels,
    int pixelCount
)
{
    int index =
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


bool CUDAProcessor::invert(Image& image)
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

    const int pixelCount =
        width * height;

    const std::size_t bytes =
        static_cast<std::size_t>(pixelCount)
        * sizeof(Pixel);

    // CPU-side pointer variable whose value
    // will be a GPU memory address.
    Pixel* devicePixels = nullptr;

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

    // CPU -> GPU
    error = cudaMemcpy(
        devicePixels,
        image.data(),
        bytes,
        cudaMemcpyHostToDevice
    );

    if (error != cudaSuccess) {
        std::cerr
            << "Host to device copy failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        return false;
    }

    const int threadsPerBlock = 256;

    const int blocks =
        (
            pixelCount +
            threadsPerBlock - 1
        )
        / threadsPerBlock;

    // Launch the GPU kernel
    invertKernel<<<blocks, threadsPerBlock>>>(
        devicePixels,
        pixelCount
    );

    error = cudaGetLastError();

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

    // GPU -> CPU
    error = cudaMemcpy(
        image.data(),
        devicePixels,
        bytes,
        cudaMemcpyDeviceToHost
    );

    if (error != cudaSuccess) {
        std::cerr
            << "Device to host copy failed: "
            << cudaGetErrorString(error)
            << '\n';

        cudaFree(devicePixels);
        return false;
    }

    cudaFree(devicePixels);

    return true;
}

}