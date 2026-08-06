#include "ImageIO.h"

#include <fstream>

namespace img {

bool savePPM(
    const Image& image,
    const std::string& filename
)
{
    std::ofstream file{filename};

    if (!file) {
        return false;
    }

    // PPM header
    file << "P3\n";
    file << image.getWidth()
         << ' '
         << image.getHeight()
         << '\n';
    file << "255\n";

    // PPM pixel data
    for (int y = 0; y < image.getHeight(); ++y) { // Traversing through the image
        for (int x = 0; x < image.getWidth(); ++x) {
            const Pixel& pixel = image.getPixel(x, y);

            file << static_cast<int>(pixel.r) << ' '
                 << static_cast<int>(pixel.g) << ' '
                 << static_cast<int>(pixel.b) << '\n';
        }
    }

    return true;
}

bool loadPPM(
    const std::string& filename,
    Image& image
)
{
    std::ifstream file{filename};

    if (!file) {
        return false;
    }

    std::string format;
    int width;
    int height;
    int maxValue;

    if (!(file >> format
               >> width
               >> height
               >> maxValue)) {
        return false;
    }

    if (format != "P3") {
        return false;
    }

    if (width <= 0 || height <= 0) {
        return false;
    }

    if (maxValue != 255) {
        return false;
    }

    if (!image.resizeImage(width, height)) {
        return false;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int red;
            int green;
            int blue;

            if (!(file >> red >> green >> blue)) {
                return false;
            }

            if (
                red < 0 || red > 255 ||
                green < 0 || green > 255 ||
                blue < 0 || blue > 255
            ) {
                return false;
            }

            const Pixel pixel{
                static_cast<unsigned char>(red),
                static_cast<unsigned char>(green),
                static_cast<unsigned char>(blue)
            };

            image.setPixel(x, y, pixel);
        }
    }

    return true;
}

}