#include "ImageIO.h"

#include <fstream>

#include "stb_image_write.h"
#include "stb_image.h"

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


bool loadImage(
    const std::string& filename,
    Image& image
)
{
    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = //char pointer to hold the image data
        stbi_load(
            filename.c_str(),// our image name 
            &width,// width variable's memory address
            &height,
            &channels,//we send references to our variable to the function and it will fill it with the number of channels in the image
            3
        );

    if (data == nullptr) {
        return false;
    }

    if (!image.resizeImage(width, height)) {// if the image resizing fails ,free the allocated memory and return false
        stbi_image_free(data);
        return false;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            const int index =
                (y * width + x) * 3;

            Pixel pixel{
                data[index],
                data[index + 1],
                data[index + 2]
            };

            image.setPixel(
                x,
                y,
                pixel
            );
        }
    }

    stbi_image_free(data);

    return true;
}

bool savePNG(
    const Image& image,
    const std::string& filename
)
{
    if (
        image.getWidth() <= 0 ||
        image.getHeight() <= 0 ||
        image.data() == nullptr
    ) {
        return false;
    }

    const int channels = 3;

    const int stride =
        image.getWidth() * channels;

    const int result =
        stbi_write_png(
            filename.c_str(),
            image.getWidth(),
            image.getHeight(),
            channels,
            image.data(),
            stride
        );

    return result != 0;
}

bool saveJPEG(
    const Image& image,
    const std::string& filename,
    int quality
)
{
    if (
        image.getWidth() <= 0 ||
        image.getHeight() <= 0 ||
        image.data() == nullptr
    ) {
        return false;
    }

    if (quality < 1) {
        quality = 1;
    }

    if (quality > 100) {
        quality = 100;
    }

    const int result =
        stbi_write_jpg(
            filename.c_str(),
            image.getWidth(),
            image.getHeight(),
            3,
            image.data(),
            quality
        );

    return result != 0;
}

}