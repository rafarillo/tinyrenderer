#include "tgaimage.h"
#include "line.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	// image.set(52, 41, red);
	Line l1 = Line(13, 20, 80, 40);
	Line l2 = Line(20, 13, 40, 80, &red);
	Line l3 = Line(80, 40, 13, 20, &red);
	l1.draw1(image);
	l2.draw2(image);
	l3.draw2(image);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

