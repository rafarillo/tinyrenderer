#include "tgaimage.h"
#include "model.hpp"
#include "geometry.hpp"
#include "triangle.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);

const int width  = 800;
const int height = 800;

int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);
	// Vec2<int> t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}, 
	// 	t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}, 
	// 	t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
	
	// Triangle tr0(t0[0], t0[1], t0[2]), tr1(t1[0], t1[1], t1[2]), tr2(t2[0], t2[1], t2[2]);
	// tr0.DrawEmpty(image, green);
	// tr1.DrawEmpty(image, red);
	// tr2.DrawEmpty(image, blue);
	// tr0.BarycentricDrawFill(image, white);
	// tr1.BarycentricDrawFill(image, white);
	// tr2.BarycentricDrawFill(image, white);

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

	Vec3f lighDir(0, 0, -1);

	for(int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		Vec3f world_coord[3];
		for(int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			world_coord[j] = v0;
			v0.x = (v0.x+1.)*width/2.;
            v0.y = (v0.y+1.)*height/2.;
           	screen_coords[j] = Vec2i(v0.x, v0.y);
		}
		Triangle t(screen_coords[0], screen_coords[1], screen_coords[2]);
		Vec3f triangleNormal = (world_coord[2] - world_coord[0]) ^ (world_coord[1] - world_coord[0]);
		triangleNormal.normalize();
		float intensity = triangleNormal * lighDir;
		if(intensity > 0)
		{
			t.BarycentricDrawFill(image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		}
	}
	
	image.flip_vertically();
	image.write_tga_file("output.tga");

	return 0;
}

