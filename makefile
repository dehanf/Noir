CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SOURCES = src/main.cpp src/Image.cpp src/ImageIO.cpp
TARGET = build/noir

build:
	mkdir -p build images
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -rf build
	rm -f images/*.ppm

.PHONY: build run clean