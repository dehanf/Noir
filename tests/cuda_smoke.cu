#include <iostream>
#include <cstdio>
#include <cuda_runtime.h>

__global__ void helloKernel()
{
    printf(
        "Hello from GPU thread %d\n",
        threadIdx.x
    );
}


int main()
{
    int deviceCount = 0;

    cudaError_t error =
        cudaGetDeviceCount(&deviceCount);

    if (error != cudaSuccess) {
        std::cerr
            << "CUDA error: "
            << cudaGetErrorString(error)
            << '\n';

        return 1;
    }

    std::cout
        << "CUDA devices found: "
        << deviceCount
        << '\n';

    cudaDeviceProp properties{};

    cudaGetDeviceProperties(
        &properties,
        0
    );

    std::cout
        << "GPU: "
        << properties.name
        << '\n';

    helloKernel<<<1, 4>>>();

    error = cudaDeviceSynchronize();

    if (error != cudaSuccess) {
        std::cerr
            << "Kernel error: "
            << cudaGetErrorString(error)
            << '\n';

        return 1;
    }

    return 0;
}