#include "tgaimage.h"
#include "model.hpp"
#include "geometry.hpp"
#include "triangle.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);

const int width  = 800;
const int height = 500;

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

int main(int argc, char** argv) {
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

	return 0;
}

