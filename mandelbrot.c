/*
 * =====================================================================================
 *
 *       Filename:  mandelbrot.cpp
 *
 *    Description:  
 *      This is a neat little toy for generating images of the mandelbrot 
 *      set. Usage string is at the top of the file. Enjoy!
 *
 *    Author:  Reid Watson (rawatson), rawatson@stanford.edu
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <FreeImage.h>


/* We default to outputting an 800x800 .png with 24 bits per pixel */
#define WIDTH 800
#define HEIGHT 800
#define BPP 24

const char* USAGE_STRING = "USAGE: %s [x] [y] [span] output.png\n\
  x:          minimum value to render on the real line\n\
  y:          minimum value to render on the complex line\n\
  span:       how far from x and y to render\n\
  output.png: where to place output\n";

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_pixel_color
 *  Description:  
 * =====================================================================================
 */
RGBQUAD get_pixel_color(int x, int y, double llx, double lly, double s) 
{
    RGBQUAD color = {0,0,0,0};
    return color;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  generate_image
 *  Description:  
 * =====================================================================================
 */
int generate_image(double llx, double lly, double s, char* filename) 
{
	FreeImage_Initialise(0);
	
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP, 0, 0, 0);
	if (!bitmap)
    {
		fputs("Could not allocate bitmap!", stderr);
		return 1;
	}
	
	for (int x = 0; x < WIDTH; x++) 
    {
		for (int y = 0; y < HEIGHT; y++) 
        {
            RGBQUAD color = get_pixel_color(x, y, llx, lly, s);
			FreeImage_SetPixelColor(bitmap, x, y, &color);
        }
    }
	
	if (FreeImage_Save(FIF_PNG, bitmap, filename, 0)) 
		puts("Image successfully saved!");
	
	FreeImage_DeInitialise();
	return 0;
}

int main(int argc, char* argv[]) 
{
	puts("Mandelbrot generator loaded.");
	
	if (argc != 5)
    {
		fprintf(stderr, USAGE_STRING, argv[0]);
		exit(1);
	}
	
    /* Parse program arguments */
	double llx = atof(argv[1]);
	double lly = atof(argv[2]);
	double s = atof(argv[3]);
	char* filename = argv[4];

    /* Exit with the return code from generateImage */
	return generate_image(llx, lly, s, filename);
}
