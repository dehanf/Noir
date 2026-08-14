# Noir

Noir is a small C++17/CUDA image-processing project. It stores images in a custom RGB pixel buffer, loads image files with `stb_image`, applies CPU or GPU filters, and writes processed images back to disk with `stb_image_write`.

The current executable path is CUDA-focused: it loads `images/input.jpg`, applies a CUDA invert filter, and saves the result to `images/cuda_invert.png`.

## Features

- Custom `Image` and `Pixel` types for RGB image storage
- Image loading through `stb_image`
- PNG and JPEG output through `stb_image_write`
- ASCII PPM (`P3`) load/save helpers
- CPU filters in `CPUProcessor`:
  - grayscale
  - invert
  - brightness adjustment
  - contrast adjustment
  - threshold
  - box blur
  - gaussian blur
  - sharpen
  - Sobel edge detection
- CUDA filters in `CUDAProcessor`:
  - invert
  - grayscale
- Standalone CUDA experiments under `tests/`

## Project Structure

```text
.
├── include/
│   ├── CPUProcessor.h
│   ├── CUDAProcessor.h
│   ├── Image.h
│   ├── ImageIO.h
│   └── Pixel.h
├── src/
│   ├── cuda/
│   │   ├── CUDAUtils.cuh
│   │   └── PointFilters.cu
│   ├── CPUProcessor.cpp
│   ├── CUDAProcessor.cu
│   ├── Image.cpp
│   ├── ImageIO.cpp
│   ├── main.cpp
│   └── stbImage.cpp
├── tests/
│   ├── cuda_array.cu
│   └── cuda_smoke.cu
├── third_party/
│   └── stb/
├── images/
└── makefile
```

## Requirements

- CUDA Toolkit with `nvcc` available on `PATH`
- CUDA-capable GPU and compatible driver
- `make`
- C++17 support through `nvcc`

The stb headers used for image loading and writing are included in `third_party/stb`.

## Build

```sh
make build
```

This creates the main executable at:

```text
build/noir
```

## Run

```sh
make run
```

The program currently:

1. Loads `images/input.jpg`
2. Applies `img::CUDAProcessor::invert`
3. Saves `images/cuda_invert.png`

Progress messages are printed to standard error.

## Clean

```sh
make clean
```

This removes the `build/` directory.

## Changing the Input or Filter

The current app does not take command-line arguments. To process a different image or call a different filter, edit `src/main.cpp`.

The input path is currently hard-coded here:

```cpp
img::loadImage("images/input.jpg", image)
```

The active filter is currently:

```cpp
img::CUDAProcessor::invert(image)
```

CPU filters are available through `CPUProcessor`, but the current `main.cpp` does not call them.

## Image I/O Notes

- `loadImage` uses stb and requests 3-channel RGB data.
- `savePNG` writes RGB PNG files.
- `saveJPEG` writes RGB JPEG files and clamps the JPEG quality argument to `1..100`.
- `loadPPM` and `savePPM` support ASCII PPM files in `P3` format with a max channel value of `255`.

## CUDA Test Programs

The files in `tests/` are standalone CUDA programs and are not wired into the makefile.

Example manual builds:

```sh
mkdir -p build
nvcc -std=c++17 tests/cuda_smoke.cu -o build/cuda_smoke
nvcc -std=c++17 tests/cuda_array.cu -o build/cuda_array
```

Then run them directly:

```sh
./build/cuda_smoke
./build/cuda_array
```

## Development Notes

- `Image` owns a heap-allocated `Pixel` array and implements copy construction, copy assignment, resizing, and raw data access.
- `ImageIO` contains both PPM helpers and stb-backed general image loading/output helpers.
- `CPUProcessor` implements in-place CPU transformations.
- `CUDAProcessor` uploads the image buffer to the GPU, launches point-filter kernels, synchronizes, and copies the result back.
