CXX = clang++
LD = clang++ 
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
mp1 : main.o rgbapixel.o png.o
	clang++ $(LDFLAGS) main.o rgbapixel.o png.o -o mp1

main.o : png.h rgbapixel.h main.cpp 
	clang++ $(CXXFLAGS) main.cpp

png.o : png.h png.cpp 
	clang++ $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.h rgbapixel.cpp 
	clang++ $(CXXFLAGS) rgbapixel.cpp

