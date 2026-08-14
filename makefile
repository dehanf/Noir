NVCC = nvcc

NVCCFLAGS = \
	-std=c++17 \
	-rdc=true \
	-Iinclude \
	-Isrc/cuda \
	-Ithird_party/stb \
	-Xcompiler=-Wall,-Wextra

SOURCES = \
	src/main.cpp \
	src/Image.cpp \
	src/ImageIO.cpp \
	src/CPUProcessor.cpp \
	src/stbImage.cpp \
	src/cuda/CUDAProcessor.cu \
	src/cuda/PointFilters.cu

TARGET = build/noir

build:
	mkdir -p build images
	$(NVCC) $(NVCCFLAGS) $(SOURCES) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -rf build

.PHONY: build run clean