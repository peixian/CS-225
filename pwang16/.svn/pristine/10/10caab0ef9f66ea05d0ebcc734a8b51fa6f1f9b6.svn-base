mp1 : main.o rgbapixel.o png.o
	clang++ main.o rgbapixel.o png.o  -lpng -o mp1

main.o : png.h rgbapixel.h main.cpp 
	clang++ -c main.cpp

png.o : png.h png.cpp 
	clang++ -c png.cpp

rgbapixel.o : rgbapixel.h rgbapixel.cpp 
	clang++ -c rgbapixel.cpp

