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

}