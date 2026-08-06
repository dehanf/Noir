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

}

#endif