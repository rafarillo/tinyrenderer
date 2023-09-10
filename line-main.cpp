#include "tgaimage.h"
#include "line.hpp"
#include "model.hpp"
#include "geometry.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);

const int width  = 800;
const int height = 800;

void MainDrawLines(int argc, char **argv, TGAImage &image)
{
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

	Line example(0, 0, 50, 50), 
		example2(13, 20, 80, 40), 
		example3(20, 13, 40, 80), 
		example4(80, 40, 13, 20);
		
	example.draw4(image, red);
	example2.draw4(image, green);
	example3.draw4(image, blue);
	example4.draw4(image, white);

	image.write_tga_file("output.tga");
}