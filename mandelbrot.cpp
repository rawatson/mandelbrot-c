#include <string>
#include <iostream>
#include <FreeImage.h>
#include <cstdlib>

using namespace std;

#define WIDTH 800
#define HEIGHT 800
#define BPP 24

void getPixelColor(int x, int y, RGBQUAD & color) {
	color.rgbRed = 255;
	color.rgbGreen = 255;
	color.rgbBlue = 255;
}
/**
 * Generates an image of the complex plane from lower left corner x + iy with sidelengths s.
 */
int generateImage(double llx, double lly, double s, char* filename) {
	FreeImage_Initialise();
	
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color;
	
	if (!bitmap) {
		cerr << "Could not allocate bitmap!" << endl;
		return 1;
	}
	
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			getPixelColor(x,y,color);
			FreeImage_SetPixelColor(bitmap, x, y, &color);
		}
	}
	
	if (FreeImage_Save(FIF_PNG, bitmap, filename, 0)) {
		cout << "Image successfully saved!" << endl;
	}
	
	FreeImage_DeInitialise();
	return 0;
}

int main(int argc, char* argv[]) {
	
	cout << "Mandelbrot generator loaded." << endl;
	
	if (argc != 5) {
		cerr << "Expected 4 arguments: x y s output.png" << endl;
		exit(1);
	}
	
	double llx = atof(argv[1]);
	double lly = atof(argv[2]);
	double s = atof(argv[3]);
	char* filename = argv[4];
	
	int success = generateImage(llx, lly, s, filename);
	return success;
}