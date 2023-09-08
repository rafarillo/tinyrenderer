#include "tgaimage.h"
#include "geometry.hpp"
class Line
{
    private:
    int x0, y0, xf, yf;

    public:
    Line();
    Line(int x0, int y0, int xf, int yf);
    Line(Vec2<int> p0, Vec2<int> p1);
    void draw1(TGAImage &image, TGAColor color);
    void draw2(TGAImage &image, TGAColor color);
    void draw3(TGAImage &image, TGAColor color);
    void draw4(TGAImage &image, TGAColor color);
    void draw5(TGAImage &image, TGAColor color);
    Vec2<int> getP0();
    Vec2<int> getPf();
};