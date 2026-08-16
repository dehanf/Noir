# Noir

Noir is a small C++17/CUDA image-processing project. It stores images in a custom RGB pixel buffer, loads common image formats with `stb_image`, applies CPU or GPU filters, and writes processed images with `stb_image_write`.

The current executable path is CUDA-focused: it loads `images/input.jpg`, applies a CUDA invert filter, and saves the result as `images/cuda_invert.png`.

## Quick Start

```sh
make build
make run
```

Before running, place an input image at `images/input.jpg`. The path is currently hard-coded and is case-sensitive on some systems, so `input.JPG` may not work everywhere.

The `images/` directory is ignored by git and is created by the makefile for local input and output files.

## Requirements

- CUDA Toolkit with `nvcc` available on `PATH`
- CUDA-capable GPU and compatible NVIDIA driver
- `make`
- C++17 support through `nvcc`

The stb headers used for image loading and writing are vendored in `third_party/stb`.

## Build Commands

Build the main executable:

```sh
make build
```

Run the executable:

```sh
make run
```

Remove build output:

```sh
make clean
```

The main executable is written to `build/noir`. The makefile compiles CUDA code with relocatable device code enabled through `-rdc=true`.

## Current Program Flow

`src/main.cpp` currently performs one fixed pipeline:

1. Load `images/input.jpg` into an `img::Image`
2. Apply `img::CUDAProcessor::invert(image)`
3. Save the result to `images/cuda_invert.png`

Progress and error messages are printed to standard error. The app does not currently accept command-line arguments, so changing the input path, output path, or active filter requires editing `src/main.cpp`.

## Features

- Custom `Image` and `Pixel` types for 3-channel RGB image storage
- Image loading through `stb_image`
- PNG and JPEG output through `stb_image_write`
- ASCII PPM (`P3`) load/save helpers
- In-place CPU filters through `CPUProcessor`
- CUDA point filters through `CUDAProcessor`
- Standalone CUDA experiment programs under `tests/`

## Available Filters

CPU filters:

- `CPUProcessor::grayscale`
- `CPUProcessor::invert`
- `CPUProcessor::adjustBrightness`
- `CPUProcessor::adjustContrast`
- `CPUProcessor::threshold`
- `CPUProcessor::boxBlur`
- `CPUProcessor::gaussianBlur`
- `CPUProcessor::sharpen`
- `CPUProcessor::sobelEdgeDetection`

CUDA filters:

- `CUDAProcessor::invert`
- `CUDAProcessor::grayscale`
- `CUDAProcessor::brightness`
- `CUDAProcessor::contrast`
- `CUDAProcessor::threshold`

## Project Structure

```text
.
|-- include/
|   |-- CPUProcessor.h
|   |-- CUDAProcessor.h
|   |-- Image.h
|   |-- ImageIO.h
|   `-- Pixel.h
|-- src/
|   |-- cuda/
|   |   |-- CUDAProcessor.cu
|   |   |-- CUDAUtils.cuh
|   |   |-- PointFilters.cu
|   |   `-- PointFilters.cuh
|   |-- CPUProcessor.cpp
|   |-- Image.cpp
|   |-- ImageIO.cpp
|   |-- main.cpp
|   `-- stbImage.cpp
|-- tests/
|   |-- cuda_array.cu
|   `-- cuda_smoke.cu
|-- third_party/
|   `-- stb/
|-- images/
`-- makefile
```

## Image I/O Notes

- `loadImage` requests 3-channel RGB data from stb.
- `savePNG` writes RGB PNG files.
- `saveJPEG` writes RGB JPEG files and clamps quality to `1..100`.
- `loadPPM` and `savePPM` support ASCII PPM files in `P3` format with a max channel value of `255`.

## CUDA Test Programs

The files in `tests/` are standalone CUDA programs and are not wired into the makefile.

Example manual builds:

```sh
mkdir -p build
nvcc -std=c++17 tests/cuda_smoke.cu -o build/cuda_smoke
nvcc -std=c++17 tests/cuda_array.cu -o build/cuda_array
```

Run them directly:

```sh
./build/cuda_smoke
./build/cuda_array
```

## Development Notes

- `Image` owns a heap-allocated `Pixel` array and implements copy construction, copy assignment, resizing, and raw data access.
- `ImageIO` contains both PPM helpers and stb-backed image loading/output helpers.
- `CPUProcessor` implements in-place CPU transformations.
- `CUDAProcessor` uploads the image buffer to the GPU, launches point-filter kernels, synchronizes, and copies the result back.
- CUDA helpers and kernels live under `src/cuda/`: `CUDAUtils.cuh` handles upload/download/block-count helpers, while `PointFilters.cu` contains the point-filter kernels declared in `PointFilters.cuh`.
