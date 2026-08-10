#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <string>

#include "Image.h"

namespace img {

bool savePPM(
    const Image& image, //DO NOT COPY: pass by rerference cause real images could contain million pixels
    const std::string& filename
);

bool loadPPM(const std::string& filename, Image& image);

bool loadImage(
    const std::string& filename,
    Image& image //DO NOT COPY: pass by rerference cause real images could contain million pixels also no const
);

bool savePNG(
    const Image& image,
    const std::string& filename
);

bool saveJPEG(
    const Image& image,//only saving the image
    const std::string& filename,
    int quality = 90
);


}

#endif