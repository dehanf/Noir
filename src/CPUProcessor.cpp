#include "CPUProcessor.h"
#include <cmath> // for std::sqrt

namespace img {

unsigned char clampChannel(int value){
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    else {
        return static_cast<unsigned char>(value);
    }
}

void CPUProcessor::invert(Image& image){ //invert the image by subtracting each channel value from 255
    for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = static_cast<unsigned char>(255 - pixel.r);
            pixel.g = static_cast<unsigned char>(255 - pixel.g);
            pixel.b = static_cast<unsigned char>(255 - pixel.b);
        }
    }
}

void CPUProcessor::adjustBrightness(Image& image, int brightness) //adjust the brightness of the image by adding the brightness value to each channel value and clamping the result to the range [0, 255]
    {
        for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = clampChannel(pixel.r + brightness);
            pixel.g = clampChannel(pixel.g + brightness);
            pixel.b = clampChannel(pixel.b + brightness);
        }
    }

}

void CPUProcessor::adjustContrast(Image& image,float contrast)//adjust the contrast of the image by multiplying each channel value by the contrast value and clamping the result to the range [0, 255]
{
    {
        for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x, y);
            pixel.r = clampChannel((static_cast<int>(pixel.r)-128)*contrast + 128);
            pixel.g = clampChannel((static_cast<int>(pixel.g)-128)*contrast + 128);
            pixel.b = clampChannel((static_cast<int>(pixel.b)-128)*contrast + 128);

        }
    }

}

}

void CPUProcessor::grayscale(Image& image){ //grayscale the image by calculating the luminance of each pixel and setting each channel to that value
    for(int y=0;y<image.getHeight();y++){
        for(int x=0;x<image.getWidth();x++){
            Pixel& pixel = image.getPixel(x,y);
            const int gray = static_cast<int>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            const unsigned char grayValue = clampChannel(gray);
            pixel.r = grayValue;
            pixel.g = grayValue;
            pixel.b = grayValue;           
        }
    }
}
void CPUProcessor::threshold( //apply a binary threshold to the image
    Image& image,
    unsigned char thresholdValue
)
{
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            Pixel& pixel = image.getPixel(x, y);

            const int intensity = static_cast<int>(
                0.299 * pixel.r +
                0.587 * pixel.g +
                0.114 * pixel.b
            );

            const unsigned char outputValue =
                intensity >= thresholdValue
                    ? 255
                    : 0;

            pixel.r = outputValue;
            pixel.g = outputValue;
            pixel.b = outputValue;
        }
    }
}

void CPUProcessor::applyKernel3x3(// common function for 3 by 3 kernel convolution operations
    Image& image,
    const int kernel[3][3],
    int divisor
)
{
    const int width = image.getWidth();
    const int height = image.getHeight();

    if (width < 3 || height < 3) {
        return;
    }

    if (divisor == 0) {
        divisor = 1;
    }

    Image output{width, height};

    // Copy the original image first.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output.setPixel(
                x,
                y,
                image.getPixel(x, y)
            );
        }
    }

    // Skip the outer border.
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {

            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {

                    const Pixel& pixel =
                        image.getPixel(
                            x + kx,
                            y + ky
                        );

                    const int weight =
                        kernel[ky + 1][kx + 1]; // getting the corresponding weight from the kernel

                    redSum +=
                        static_cast<int>(pixel.r)
                        * weight;

                    greenSum +=
                        static_cast<int>(pixel.g)
                        * weight;

                    blueSum +=
                        static_cast<int>(pixel.b)
                        * weight;
                }
            }

            Pixel result{
                clampChannel(redSum / divisor),
                clampChannel(greenSum / divisor),
                clampChannel(blueSum / divisor)
            };

            output.setPixel(x, y, result);
        }
    }

    // Copy result back into original image.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image.setPixel(
                x,
                y,
                output.getPixel(x, y)
            );
        }
    }
}


void CPUProcessor::boxBlur(Image& image)
{
    const int kernel[3][3] = {// kernel used for box blur
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    applyKernel3x3(
        image,
        kernel,
        9
    );
}

void CPUProcessor::gaussianBlur(Image& image)
{
    const int kernel[3][3] = {// kernel used for gaussian blur
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    applyKernel3x3(
        image,
        kernel,
        16
    );
}

void CPUProcessor::sharpen(Image& image)
{
    const int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    applyKernel3x3(
        image,
        kernel,
        1
    );
}

void CPUProcessor::sobelEdgeDetection(Image& image)
{
    const int width = image.getWidth();
    const int height = image.getHeight();

    if (width < 3 || height < 3) {
        return;
    }

    // Sobel works with brightness, so remove color first.
    grayscale(image);

    Image output{width, height};

    const int gxKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int gyKernel[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {

            int gx = 0;
            int gy = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {

                    const Pixel& pixel =
                        image.getPixel(
                            x + kx,
                            y + ky
                        );

                    const int intensity =
                        static_cast<int>(pixel.r);

                    gx += intensity
                        * gxKernel[ky + 1][kx + 1];

                    gy += intensity
                        * gyKernel[ky + 1][kx + 1];
                }
            }

            const int magnitude =
                static_cast<int>(
                    std::sqrt(
                        gx * gx +
                        gy * gy
                    )
                );

            const unsigned char edge =
                clampChannel(magnitude);

            output.setPixel(
                x,
                y,
                Pixel{edge, edge, edge}
            );
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image.setPixel(
                x,
                y,
                output.getPixel(x, y)
            );
        }
    }
}


}

