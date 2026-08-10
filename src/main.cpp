#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "CPUProcessor.h"

int main()
{
    img::Image image;

    if (!img::loadImage(
            "images/input.jpg",
            image
        )) {
        std::cerr
            << "Failed to load image\n";

        return 1;
    }

    std::cout
        << "Loaded image: "
        << image.getWidth()
        << " x "
        << image.getHeight()
        << '\n';

    img::CPUProcessor::adjustBrightness(image, 50);

    if (!img::savePNG(
            image,
            "images/output.png"
        )) {
        std::cerr
            << "Failed to save PNG\n";

        return 1;
    }

    if (!img::saveJPEG(
            image,
            "images/output.jpg",
            90
        )) {
        std::cerr
            << "Failed to save JPEG\n";

        return 1;
    }

    std::cout
        << "JPEG/PNG test successful.\n";

    return 0;
}