#include "tgaimage.h"
#include "line.hpp"

class Triangle
{
    private:
    Vec2<int> p0, p1, p2;
    int CalculateX(int y, Line l);
    Vec3<float> CaculateBarycentric(Vec2<int> p);

    public:
    Triangle(Vec2<int> p0, Vec2<int> p1, Vec2<int> p2);
    void DrawEmpty(TGAImage &image, TGAColor color);
    void SweepDrawFill(TGAImage &image, TGAColor color);
    void BarycentricDrawFill(TGAImage &image, TGAColor color);
};