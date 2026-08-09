# Noir

Noir is a small C++ image-processing project that reads ASCII PPM images, applies CPU-based filters, and writes the processed images back to disk.

The project currently focuses on learning-friendly image operations: custom image storage, PPM file input/output, per-pixel filters, and 3x3 convolution filters.

## Features

- Load and save PPM images in `P3` format
- Store image data with a custom `Image` and `Pixel` model
- Apply basic per-pixel filters:
  - grayscale
  - invert
  - brightness adjustment
  - contrast adjustment
  - threshold
- Apply convolution filters:
  - box blur
  - gaussian blur
  - sharpen
  - Sobel edge detection

## Project Structure

```text
.
├── include/
│   ├── CPUProcessor.h
│   ├── Image.h
│   ├── ImageIO.h
│   └── Pixel.h
├── src/
│   ├── CPUProcessor.cpp
│   ├── Image.cpp
│   ├── ImageIO.cpp
│   └── main.cpp
├── images/
│   └── *.ppm
└── makefile
```

## Requirements

- A C++17-compatible compiler
- `make`

The included `makefile` uses `clang++` by default.

## Build

```sh
make build
```

This creates the executable at:

```text
build/noir
```

## Run

```sh
make run
```

The current program reads:

```text
images/gradient.ppm
```

It then generates:

```text
images/box_blur.ppm
images/gaussian_blur.ppm
images/sharpen.ppm
images/sobel.ppm
```

## Clean

```sh
make clean
```

Note: `make clean` removes the `build/` directory and every `.ppm` file in `images/`, including sample input images.

## Using Different Images

To process a different input image, update the `source` path in `src/main.cpp`:

```cpp
const std::string source = "images/gradient.ppm";
```

Input images must be ASCII PPM files using the `P3` format with a max channel value of `255`.

## Development Notes

- Core image data lives in `Image`.
- Pixel RGB values are stored as `unsigned char` in `Pixel`.
- PPM loading and saving is handled by `ImageIO`.
- Image transformations are implemented as static methods in `CPUProcessor`.
