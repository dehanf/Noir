build:
	clang++ -std=c++17 src/*.cpp -Iinclude -o build/image_app

run: build
	./build/image_app