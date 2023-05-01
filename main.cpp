#include "tgaimage.h"
#include "line.hpp"
#include "model.hpp"
#include "geometry.hpp"
#define WIDTH 800
#define HEIGHT 800

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	/* --- LESSON 1 --- Drawing Lines
		TGAImage image(100, 100, TGAImage::RGB);
		Line l1 = Line(13, 20, 80, 40);
		Line l2 = Line(20, 13, 40, 80, &red);
		Line l3 = Line(80, 40, 13, 20, &red);
		l1.draw1(image);
		l2.drawBest(image);
		l3.drawBest(image);
		image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
		image.write_tga_file("output.tga");
	*/
	// LESSON 1 APPLICATION

	if(argc < 2)
	{
		printf("HOW TO USE: ./main {filename}");
		return 1;
	}
	
	Model* model = new Model(argv[1]);
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	for(int i = 0; i < model->nFaces(); i++)
	{
		std::vector<int> face = model->face(i);
		for(int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			Vec3f vf = model->vert(face[(j+1)%3]);

			int x0 = (v0.x + 1.0) * WIDTH * 0.5;
			int xf = (vf.x + 1.0) * WIDTH * 0.5;

			int y0 = (v0.y + 1.0) * HEIGHT * 0.5;
			int yf = (vf.y + 1.0) * HEIGHT * 0.5;

			Vec2i p0 = Vec2i(x0, y0);
			Vec2i pf = Vec2i(xf, yf);
			Line l = Line(p0, pf, &white);

			l.draw(image);
		}
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;

	return 0;
}

