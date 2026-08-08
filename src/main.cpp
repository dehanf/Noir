#include <iostream>

#include "CPUProcessor.h"
#include "ImageIO.h"

int main()
{
    const std::string source =
        "images/gradient.ppm";

    img::Image boxImage;

    if (!img::loadPPM(source, boxImage)) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    img::CPUProcessor::boxBlur(boxImage);

    img::savePPM(
        boxImage,
        "images/box_blur.ppm"
    );


    img::Image gaussianImage;

    if (!img::loadPPM(source, gaussianImage)) {
        return 1;
    }

    img::CPUProcessor::gaussianBlur(
        gaussianImage
    );

    img::savePPM(
        gaussianImage,
        "images/gaussian_blur.ppm"
    );


    img::Image sharpenImage;

    if (!img::loadPPM(source, sharpenImage)) {
        return 1;
    }

    img::CPUProcessor::sharpen(sharpenImage);

    img::savePPM(
        sharpenImage,
        "images/sharpen.ppm"
    );


    img::Image sobelImage;

    if (!img::loadPPM(source, sobelImage)) {
        return 1;
    }

    img::CPUProcessor::sobelEdgeDetection(
        sobelImage
    );

    img::savePPM(
        sobelImage,
        "images/sobel.ppm"
    );

    std::cout
        << "Milestone 5 filters generated.\n";

    return 0;
}