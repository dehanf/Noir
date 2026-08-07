#include <iostream>

#include "CPUProcessor.h"
#include "Image.h"
#include "ImageIO.h"

int main()
{
    const std::string inputPath =
        "images/gradient.ppm";

    img::Image invertedImage;

    if (!img::loadPPM(inputPath, invertedImage)) {
        std::cerr << "Failed to load input image\n";
        return 1;
    }

    img::CPUProcessor::invert(invertedImage);

    if (!img::savePPM(
            invertedImage,
            "images/gradient_inverted.ppm"
        )) {
        std::cerr << "Failed to save inverted image\n";
        return 1;
    }

    img::Image grayscaleImage;

    if (!img::loadPPM(inputPath, grayscaleImage)) {
        std::cerr << "Failed to load input image\n";
        return 1;
    }

    img::CPUProcessor::grayscale(grayscaleImage);

    if (!img::savePPM(
            grayscaleImage,
            "images/gradient_grayscale.ppm"
        )) {
        std::cerr << "Failed to save grayscale image\n";
        return 1;
    }

    img::Image brightImage;

    if (!img::loadPPM(inputPath, brightImage)) {
        std::cerr << "Failed to load input image\n";
        return 1;
    }

    img::CPUProcessor::adjustBrightness(
        brightImage,
        50
    );

    if (!img::savePPM(
            brightImage,
            "images/gradient_bright.ppm"
        )) {
        std::cerr << "Failed to save bright image\n";
        return 1;
    }

    img::Image contrastImage;

    if (!img::loadPPM(inputPath, contrastImage)) {
        std::cerr << "Failed to load input image\n";
        return 1;
    }

    img::CPUProcessor::adjustContrast(
        contrastImage,
        1.8
    );

    if (!img::savePPM(
            contrastImage,
            "images/gradient_contrast.ppm"
        )) {
        std::cerr << "Failed to save contrast image\n";
        return 1;
    }

    img::Image thresholdImage;

    if (!img::loadPPM(inputPath, thresholdImage)) {
        std::cerr << "Failed to load input image\n";
        return 1;
    }

    img::CPUProcessor::threshold(
        thresholdImage,
        128
    );

    if (!img::savePPM(
            thresholdImage,
            "images/gradient_threshold.ppm"
        )) {
        std::cerr << "Failed to save threshold image\n";
        return 1;
    }

    std::cout
        << "CPU filters completed successfully:\n"
        << "- images/gradient_inverted.ppm\n"
        << "- images/gradient_grayscale.ppm\n"
        << "- images/gradient_bright.ppm\n"
        << "- images/gradient_contrast.ppm\n"
        << "- images/gradient_threshold.ppm\n";

    return 0;
}