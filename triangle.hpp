#include "tgaimage.h"
#include "line.hpp"

class Triangle
{
    private:
    Vec2<int> p0, p1, p2;
    Vec3f pf0, pf1, pf2;
    bool isRenderWithDepth = false;
    int CalculateX(int y, Line l);
    Vec3<float> CaculateBarycentric(Vec2<int> p);

    public:
    Triangle(Vec2<int> p0, Vec2<int> p1, Vec2<int> p2);
    Triangle(Vec3f pf0, Vec3f pf1, Vec3f pf2);
    void DrawEmpty(TGAImage &image, TGAColor color);
    void SweepDrawFill(TGAImage &image, TGAColor color);
    void BarycentricDrawFill(TGAImage &image, TGAImage &diffuseImage, Vec3f* uvCoord, float intensity, float *zBuffer=NULL);
};