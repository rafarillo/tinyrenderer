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

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	
	image.write_tga_file("output.tga");

	return 0;
}

