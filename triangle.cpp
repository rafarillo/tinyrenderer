#include "triangle.hpp"

int Triangle::CalculateX(int y, Line l)
{
    Vec2 p0 = l.getP0(), 
        pf = l.getPf();
    float m = (pf.y - p0.y)/(float)(pf.x - p0.x);
    float x = (y - p0.y)/m + p0.x;
    return (int) x;
}

Vec3<float> Triangle::CaculateBarycentric(Vec2<int> p)
{
    if(this->isRenderWithDepth)
    {
        Vec3<float> a(this->pf1.x - this->pf0.x, this->pf2.x - this->pf0.x, this->pf0.x - p.x);
        Vec3<float> b(this->pf1.y - this->pf0.y, this->pf2.y - this->pf0.y, this->pf0.y - p.y);
        Vec3<float> cros = a ^ b;
        if(std::abs(cros.z) < 1) return Vec3f(-1, 1, 1);
        return Vec3f(1.0f - (cros.x + cros.y)/cros.z, cros.x/cros.z, cros.y/cros.z);
    }
    
    Vec3<float> a(this->p1.x - this->p0.x, this->p2.x - this->p0.x, this->p0.x - p.x);
    Vec3<float> b(this->p1.y - this->p0.y, this->p2.y - this->p0.y, this->p0.y - p.y);
    Vec3<float> cros = a ^ b;
    if(std::abs(cros.z) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.0f - (cros.x + cros.y)/cros.z, cros.x/cros.z, cros.y/cros.z);
}

Triangle::Triangle(Vec2<int> p0, Vec2<int> p1, Vec2<int> p2)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
}

Triangle::Triangle(Vec3f pf0, Vec3f pf1, Vec3f pf2)
{
    this->pf0 = pf0;
    this->pf1 = pf1;
    this->pf2 = pf2;

    this->isRenderWithDepth = true;
}

void Triangle::DrawEmpty(TGAImage &image, TGAColor color)
{
    Line l1(this->p0.x, this->p0.y, this->p1.x, this->p1.y), 
    l2(this->p1.x, this->p1.y, this->p2.x, this->p2.y), 
    l3(this->p2.x, this->p2.y, this->p0.x, this->p0.y);

    l1.draw5(image, color);
    l2.draw5(image, color);
    l3.draw5(image, color);
}

void Triangle::SweepDrawFill(TGAImage &image, TGAColor color)
{
    if(this->p0.y > this->p1.y)
    {
        std::swap(this->p0, this->p1);
    }
    if(this->p0.y > this->p2.y)
    {
        std::swap(this->p0, this->p2);
    }
    if(this->p1.y > this->p2.y)
    {
        std::swap(this->p1, this->p2);
    }

    Line leftSide, rightSide;
    bool isP1Left;
    if(this->p1.x < this->p2.x)
    {
        leftSide = Line(this->p0, this->p1);
        rightSide = Line(this->p0, this->p2);
        isP1Left = true;
    }
    else
    {
        leftSide = Line(this->p0, this->p2);
        rightSide = Line(this->p0, this->p1);
        isP1Left = false;
    }


    for(int y0 = this->p0.y; y0 < this->p2.y; y0++)
    {
        if(y0 >= leftSide.getPf().y)
        {
            leftSide = isP1Left? Line(this->p1, this->p2) : Line(this->p2, this->p1);
        }

        if(y0 >= rightSide.getPf().y)
        {
            rightSide = !isP1Left? Line(this->p2, this->p1) : Line(this->p1, this->p2);
        }

        int xLeft = CalculateX(y0, leftSide);
        int xRight = CalculateX(y0, rightSide);

        Line h(xLeft, y0, xRight, y0);
        h.draw5(image, color);
    }
}

void Triangle::BarycentricDrawFill(TGAImage &image, TGAColor color, float * zBuffer, TGAImage &diffuseImage)
{
    Vec3f pMax, pMin = pMax = this->pf0;
    int width = image.get_width();
    pMin.x = std::min(this->pf0.x, std::min(this->pf1.x, this->pf2.x));
    pMin.y = std::min(this->pf0.y, std::min(this->pf1.y, this->pf2.y));

    pMax.x = std::max(this->pf0.x, std::max(this->pf1.x, this->pf2.x));
    pMax.y = std::max(this->pf0.y, std::max(this->pf1.y, this->pf2.y));
    if(this->isRenderWithDepth)
    {
        for(int x = pMin.x; x <= pMax.x; x++)
        {
            for(int y = pMin.y; y <= pMax.y; y++)
            {
                Vec3f baricentric = CaculateBarycentric(Vec2i(x, y));
                TGAColor diffColor = diffuseImage.get(x, y);
                // printf("x = %d y = %d\n", x, y);
                // printf("barX = %.2f barY = %.2f barZ = %.2f\n", baricentric.x, baricentric.y, baricentric.z);
                if(baricentric.x >= 0.0f && baricentric.y >= 0.0f && baricentric.z >= 0.0f)
                {
                    float z = 0;
                    z = this->pf0.z * baricentric.x + this->pf1.z * baricentric.y + this->pf2.z * baricentric.z;
                    if(zBuffer[x + y*width] < z)
                    {
                        zBuffer[x + y*width] = z;
                        image.set(x, y, color);
                    }
                    // printf("z = %f, z[%d] = %f\n", z, x + y*width, zBuffer[x + y*width]);
                }
            }
        }
        return;
    }
    
    for(int x = pMin.x; x <= pMax.x; x++)
    {
        for(int y = pMin.y; y <= pMax.y; y++)
        {
            Vec3f baricentric = CaculateBarycentric(Vec2i(x, y));
            // printf("x = %d y = %d\n", x, y);
            // printf("barX = %.2f barY = %.2f barZ = %.2f\n", baricentric.x, baricentric.y, baricentric.z);
            if(baricentric.x >= 0.0f && baricentric.y >= 0.0f && baricentric.z >= 0.0f)
            {
                image.set(x, y, color);
            }
        }
    }

}
