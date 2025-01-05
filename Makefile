CC=clang++
CSTD=-std=c++17
WARN=-Wall -Wextra -Wpedantic -Werror

SOURCE=src/*.cpp src/glad/*.cpp
MANDELBROT=src/mandelbrot/*.cpp
LOGISTIC=src/logistic/*.cpp

INCLUDE=-Iinclude 
LINKGL=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
DEBUG=-g3 -O0
RELEASE=-g -O3

COMMON=$(CC) $(CSTD) $(WARN) $(SOURCE) $(INCLUDE) $(LINKGL)

all:  mandelbrot logistic
mandelbrot: $(SOURCE) $(MANDELBROT)
	$(COMMON) $(MANDELBROT) $(RELEASE) -o mandelbrot
mandelbrot_debug: $(SOURCE) $(MANDELBROT)
	$(COMMON) $(MANDELBROT) $(DEBUG) -o mandelbrot
logistic: $(SOURCE) $(LOGISTIC)
	$(COMMON) $(LOGISTIC) $(RELEASE) -o logistic
logistic_debug: $(SOURCE) $(LOGISTIC)
	$(COMMON) $(LOGISTIC) $(DEBUG) -o logistic
clean:
	rm -rf mandelbrot logistic
