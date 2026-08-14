#include "PointFilters.cuh"

namespace img {
namespace cuda_detail {


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


__global__ void brightnessKernel(
    Pixel* pixels,
    int pixelCount,
    int amount
)
{
    const int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index >= pixelCount) {
        return;
    }

    Pixel& pixel = pixels[index];

    pixel.r = clampChannel(
        static_cast<int>(pixel.r) + amount
    );

    pixel.g = clampChannel(
        static_cast<int>(pixel.g) + amount
    );

    pixel.b = clampChannel(
        static_cast<int>(pixel.b) + amount
    );
}


__global__ void contrastKernel(
    Pixel* pixels,
    int pixelCount,
    float factor
)
{
    const int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index >= pixelCount) {
        return;
    }

    Pixel& pixel = pixels[index];

    const int red =
        static_cast<int>(
            (static_cast<int>(pixel.r) - 128)
            * factor
            + 128
        );

    const int green =
        static_cast<int>(
            (static_cast<int>(pixel.g) - 128)
            * factor
            + 128
        );

    const int blue =
        static_cast<int>(
            (static_cast<int>(pixel.b) - 128)
            * factor
            + 128
        );

    pixel.r = clampChannel(red);
    pixel.g = clampChannel(green);
    pixel.b = clampChannel(blue);
}


__global__ void thresholdKernel(
    Pixel* pixels,
    int pixelCount,
    unsigned char thresholdValue
)
{
    const int index =
        blockIdx.x * blockDim.x
        + threadIdx.x;

    if (index >= pixelCount) {
        return;
    }

    Pixel& pixel = pixels[index];

    const int intensity =
        static_cast<int>(
            0.299f * pixel.r +
            0.587f * pixel.g +
            0.114f * pixel.b
        );

    const unsigned char value =
        intensity >= thresholdValue
            ? 255
            : 0;

    pixel.r = value;
    pixel.g = value;
    pixel.b = value;
}


}
}