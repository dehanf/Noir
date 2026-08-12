#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "CUDAProcessor.h"

int main()
{
    img::Image image;

    std::cerr << "1. Loading image...\n";

    if (!img::loadImage("images/input.jpg", image)) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    std::cerr
        << "2. Image loaded: "
        << image.getWidth()
        << " x "
        << image.getHeight()
        << '\n';

    std::cerr << "3. Starting CUDA invert...\n";

    if (!img::CUDAProcessor::invert(image)) {
        std::cerr << "CUDA invert failed\n";
        return 1;
    }

    std::cerr << "4. CUDA invert completed.\n";

    std::cerr << "5. Saving image...\n";

    if (!img::savePNG(
            image,
            "images/cuda_invert.png"
        )) {
        std::cerr << "Failed to save image\n";
        return 1;
    }

    std::cerr << "6. Finished!\n";

    return 0;
}