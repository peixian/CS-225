CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Werror
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

testimage : png.o image.o testimage.o rgbapixel.o
	clang++ $(LDFLAGS) png.o image.o rgbapixel.o testimage.o -o testimage

png.o : png.h png.cpp rgbapixel.o
	clang++ $(CXXFLAGS) png.cpp
image.o : image.h image.cpp
	clang++ $(CXXFLAGS) image.cpp
testimage.o : testimage.cpp
	clang++ $(CXXFLAGS) testimage.cpp
rgbapixel.o : rgbapixel.h rgbapixel.cpp
	clang++ $(CXXFLAGS) rgbapixel.cpp
