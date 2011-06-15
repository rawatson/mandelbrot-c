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
#include <stdbool.h>
#include <complex.h>

#include <FreeImage.h>

/* We default to outputting an 800x800 .png with 24 bits per pixel */
#define WIDTH 800
#define HEIGHT 800
#define BPP 24

/* Determine how many steps to run before we assume a point is valid */
#define MAX_ITERATIONS 1000

/* Usage string detailing our four parameters */
const char* USAGE_STRING = "USAGE: %s [x] [y] [span] output.png\n\
  x:          minimum value to render on the real line\n\
  y:          minimum value to render on the complex line\n\
  span:       how far from x and y to render\n\
  output.png: where to place output\n";

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  scale_to_range
 *  Description:  Establishes a function f:[0,1] -> [min,max] which is scales a value 
 *      to a specified range.  Basically, it returns the value that is value units
 *      in [min, max]
 * =====================================================================================
 */
inline double scale_to_range(double value, double min, double max)
{
    return value * min + ( 1 - value ) * max;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_pixel_color
 *  Description:  
 * =====================================================================================
 */
RGBQUAD get_pixel_color(int x, int y, double llx, double lly, double s) 
{
    /* I'm declaring this one in front, in case I want to be more artsy later */
    RGBQUAD color;

    /* Convert our x and y values into a coordinate in the complex plane */
    complex initial = scale_to_range(x / WIDTH, llx, llx + s) 
                            + scale_to_range(y / WIDTH, lly, lly + s) * I;

    complex current = initial;
    for(int iter = 0 ; iter < MAX_ITERATIONS && cabs(current - initial) < 2; iter++)
        current = cpow(current,2) + initial;

    int color_val = cabs(current-initial) < 2 ? 0 : 255;
    color.rgbRed   = color_val;
    color.rgbGreen = color_val;
    color.rgbBlue  = color_val;
    
    return color;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  generate_image
 *  Description:  When called with the arguments to ./mandlebrot, this function will do
 *      all of the heavy lifting necessary to compute the image and write the result to
 *      the specified output file.  
 *
 *      This function deals mainly with the image library interaction, and the hard work
 *      is done in determining what color each pixel should be.
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
