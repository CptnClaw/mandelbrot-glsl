CC=clang++
CSTD=-std=c++17
WARN=-Wall -Wextra -Wpedantic -Werror
SOURCE=src/*.cpp src/glad/*.cpp
MANDELBROT=src/mandelbrot/*.cpp
INCLUDE=-Iinclude 
LINKGL=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
OUTPUT=mandelbrot-glsl
DEBUG=-g3 -O0
RELEASE=-g -O3

COMMON=$(CC) $(CSTD) $(WARN) $(SOURCE) $(INCLUDE) $(LINKGL)

all:  mandelbrot
mandelbrot: $(SOURCE) $(MANDELBROT)
	$(COMMON) $(MANDELBROT) $(RELEASE) -o mandelbrot
debug: 
	$(COMMON) $(MANDELBROT) $(DEBUG) -o mandelbrot
clean:
	rm -rf mandelbrot
