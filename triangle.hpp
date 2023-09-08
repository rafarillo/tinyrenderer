#include "tgaimage.h"
#include "line.hpp"

class Triangle
{
    private:
    Vec2<int> p0, p1, p2;
    Line l0, l1, l2;
    int CalculateX(int y, Line l);

    public:
    Triangle(Vec2<int> p0, Vec2<int> p1, Vec2<int> p2);
    void DrawEmpty(TGAImage &image, TGAColor color);
    void SweepDrawFill(TGAImage &image, TGAColor color);
};