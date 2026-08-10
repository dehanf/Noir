CXX = clang++

CXXFLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Iinclude \
	-Ithird_party/stb

SOURCES = \
	src/main.cpp \
	src/Image.cpp \
	src/ImageIO.cpp \
	src/CPUProcessor.cpp \
	src/StbImage.cpp

TARGET = build/noir

build:
	mkdir -p build images
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -rf build

.PHONY: build run clean