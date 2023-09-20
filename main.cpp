#include "tgaimage.h"
#include "model.hpp"
#include "geometry.hpp"
#include "triangle.hpp"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);

const int width  = 300;
const int height = 300;

void rasterize(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color, int ybuffer[]) {
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }
    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);
        int y = p0.y*(1.-t) + p1.y*t + .5;
        if (ybuffer[x]<y) {
            ybuffer[x] = y;
            image.set(x, 0, color);
        }
    }
}

void Exapmle1D()
{
	{ // just dumping the 2d scene (yay we have enough dimensions!)
        TGAImage scene(width, height, TGAImage::RGB);
		Line l1(Vec2i(20, 34),   Vec2i(744, 400)), 
		l2(Vec2i(120, 434), Vec2i(444, 400)), 
		l3(Vec2i(330, 463), Vec2i(594, 200));

        // scene "2d mesh"
        l1.draw5(scene, red);
        l2.draw5(scene, green);
        l3.draw5(scene, blue);

        // screen line
        Line l(Vec2i(10, 10), Vec2i(790, 10));
		l.draw5(scene, white);

        scene.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        scene.write_tga_file("scene.tga");
    }

	 {
        TGAImage render(width, 16, TGAImage::RGB);
        int ybuffer[width];
        for (int i=0; i<width; i++) {
            ybuffer[i] = std::numeric_limits<int>::min();
        }
        rasterize(Vec2i(20, 34),   Vec2i(744, 400), render, red,   ybuffer);
        rasterize(Vec2i(120, 434), Vec2i(444, 400), render, green, ybuffer);
        rasterize(Vec2i(330, 463), Vec2i(594, 200), render, blue,  ybuffer);

        // 1-pixel wide image is bad for eyes, lets widen it
        for (int i=0; i<width; i++) {
            for (int j=1; j<16; j++) {
                render.set(i, j, render.get(i, 0));
            }
        }
        render.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        render.write_tga_file("render.tga");
    }
}


int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);
	TGAImage diffuseImage(width, height, TGAImage::RGB);
	float zBuffer[width*height];
	
	for(int i = 0; i < width*height; i++) zBuffer[i] = std::numeric_limits<float>::min();

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
	
	if(!diffuseImage.read_tga_file("./obj/african_head_diffuse.tga"))
	{
		printf("Could not read diffuse image\n");
	}

	Vec3f lighDir(0, 0, -1);

	for(int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec3f screen_coords[3];
		Vec3f world_coord[3];
		for(int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			world_coord[j] = v0;
			v0.x = (v0.x+1.)*width/2.;
            v0.y = (v0.y+1.)*height/2.;
           	screen_coords[j] = Vec3f(v0.x, v0.y, v0.z);
		}
		Triangle t(screen_coords[0], screen_coords[1], screen_coords[2]);
		Vec3f triangleNormal = (world_coord[2] - world_coord[0]) ^ (world_coord[1] - world_coord[0]);
		triangleNormal.normalize();
		float intensity = triangleNormal * lighDir;
		if(intensity > 0)
		{
			t.BarycentricDrawFill(image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255), zBuffer, diffuseImage);
		}
	}
	
	image.flip_vertically();
	image.write_tga_file("output.tga");

	return 0;
}

