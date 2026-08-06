#include <iostream>

#include "Image.h"
#include "ImageIO.h"

void fillSolid(
    img::Image& image,
    const img::Pixel& color
)
{
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            image.setPixel(x, y, color);
        }
    }
}

void fillStripes(img::Image& image)
{
    const img::Pixel red{255, 0, 0};
    const img::Pixel green{0, 255, 0};
    const img::Pixel blue{0, 0, 255};

    const int stripeHeight = image.getHeight() / 3;

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            if (y < stripeHeight) {
                image.setPixel(x, y, red);
            }
            else if (y < stripeHeight * 2) {
                image.setPixel(x, y, green);
            }
            else {
                image.setPixel(x, y, blue);
            }
        }
    }
}

void fillCheckerboard(
    img::Image& image,
    int blockSize = 40
)
{
    const img::Pixel black{0, 0, 0};
    const img::Pixel white{255, 255, 255};

    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            const int blockX = x / blockSize;
            const int blockY = y / blockSize;

            const bool isWhite =
                (blockX + blockY) % 2 == 0;

            if (isWhite) {
                image.setPixel(x, y, white);
            }
            else {
                image.setPixel(x, y, black);
            }
        }
    }
}

void fillGradient(img::Image& image)
{
    const int width = image.getWidth();
    const int height = image.getHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const unsigned char red =
                static_cast<unsigned char>(
                    255 * x / (width - 1)
                );

            const unsigned char green =
                static_cast<unsigned char>(
                    255 * y / (height - 1)
                );

            const img::Pixel color{
                red,
                green,
                128
            };

            image.setPixel(x, y, color);
        }
    }
}

int main()
{
    img::Image redImage{400, 300};
    fillSolid(redImage, img::Pixel{255, 0, 0});

    if (!img::savePPM(redImage, "images/red.ppm")) {
        std::cerr << "Failed to save red.ppm\n";
        return 1;
    }

    img::Image stripesImage{400, 300};
    fillStripes(stripesImage);

    if (!img::savePPM(
            stripesImage,
            "images/stripes.ppm"
        )) {
        std::cerr << "Failed to save stripes.ppm\n";
        return 1;
    }

    img::Image checkerboardImage{400, 300};
    fillCheckerboard(checkerboardImage);

    if (!img::savePPM(
            checkerboardImage,
            "images/checkerboard.ppm"
        )) {
        std::cerr << "Failed to save checkerboard.ppm\n";
        return 1;
    }

    img::Image gradientImage{400, 300};
    fillGradient(gradientImage);

    if (!img::savePPM(
            gradientImage,
            "images/gradient.ppm"
        )) {
        std::cerr << "Failed to save gradient.ppm\n";
        return 1;
    }
    img::Image loadedImage;

    if (!img::loadPPM(
            "images/gradient.ppm",
            loadedImage
        )) {
        std::cerr
            << "Failed to load gradient.ppm\n";

        return 1;
    }

    if (!img::savePPM(
            loadedImage,
            "images/gradient_copy.ppm"
        )) {
        std::cerr
            << "Failed to save gradient_copy.ppm\n";

        return 1;
    }

    std::cout
        << "Loaded image size: "
        << loadedImage.getWidth()
        << " x "
        << loadedImage.getHeight()
        << '\n';

    std::cout
        << "Generated and loaded images successfully:\n"
        << "- images/red.ppm\n"
        << "- images/stripes.ppm\n"
        << "- images/checkerboard.ppm\n"
        << "- images/gradient.ppm\n"
        << "- images/gradient_copy.ppm\n";

    return 0;
}