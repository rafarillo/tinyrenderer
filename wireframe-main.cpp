#include "tgaimage.h"
#include "line.hpp"
#include "model.hpp"
#include "geometry.hpp"

const int width  = 800;
const int height = 800;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);

void MainDrawWireFrame(int argc, char ** argv, TGAImage &image)
{
    Model *model = NULL;
	if(argc < 2)
	{
		printf("Using the program in the wrong way. ./main.exe file.obj");
		model = new Model("obj/african_head.obj");
	}
	else
	{
		model = new Model(argv[1]);
	}

	for(int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		for(int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			Vec3f vf = model->vert(face[(j+1)%3]);
			int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int xf = (vf.x+1.)*width/2.;
            int yf = (vf.y+1.)*height/2.;
			Line line(x0, y0, xf, yf);
            line.draw5(image, white);
		}
	}

	image.flip_vertically();
	image.write_tga_file("output.tga");
	delete model;
}