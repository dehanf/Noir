#include <iostream>
#include <cuda_runtime.h>

__global__ void doubleValues(int* values, int count)
{
    int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index < count) {
        values[index] *= 2;
    }
}

int main()
{
    const int count = 5;

    int values[count] = {
        1, 2, 3, 4, 5
    };

    int* deviceValues = nullptr;

    cudaMalloc(
        &deviceValues,
        count * sizeof(int)
    );

    cudaMemcpy(
        deviceValues,
        values,
        count * sizeof(int),
        cudaMemcpyHostToDevice
    );

    doubleValues<<<1, 5>>>(
        deviceValues,
        count
    );

    cudaDeviceSynchronize();// after kernel launch, synchronize the device to ensure all threads have completed

    cudaMemcpy(
        values,
        deviceValues,
        count * sizeof(int),
        cudaMemcpyDeviceToHost
    );

    cudaFree(deviceValues);//memory deallocation on the device
    for (int value : values) {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    return 0;
}