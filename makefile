NVCC = nvcc

NVCCFLAGS = \
	-std=c++17 \
	-Iinclude \
	-Ithird_party/stb \
	-Xcompiler=-Wall,-Wextra

SOURCES = \
	src/main.cpp \
	src/Image.cpp \
	src/ImageIO.cpp \
	src/CPUProcessor.cpp \
	src/stbImage.cpp \
	src/CUDAProcessor.cu

TARGET = build/noir

build:
	mkdir -p build images
	$(NVCC) $(NVCCFLAGS) $(SOURCES) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -rf build

.PHONY: build run clean