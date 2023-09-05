#include "tgaimage.h"
#include "line.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

	Line example(0, 0, 50, 50), 
		example2(13, 20, 80, 40), 
		example3(20, 13, 40, 80), 
		example4(80, 40, 13, 20);
		
	example.draw1(image, red);
	example2.draw2(image, green);
	example3.draw2(image, blue);
	example4.draw2(image, white);

	image.write_tga_file("output.tga");
	return 0;
}

