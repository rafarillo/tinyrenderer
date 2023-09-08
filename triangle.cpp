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
    Vec3<float> a(this->p1.x - this->p0.x, this->p2.x - this->p0.x, this->p0.x - p.x);
    Vec3<float> b(this->p1.y - this->p0.y, this->p2.y - this->p0.y, this->p0.y - p.y);
    Vec3<float> cros = a ^ b;
    return Vec3f(1 - (cros.x + cros.y)/cros.z, cros.x/cros.z, cros.y/cros.z);
}

Triangle::Triangle(Vec2<int> p0, Vec2<int> p1, Vec2<int> p2)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
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

void Triangle::BarycentricDrawFill(TGAImage &image, TGAColor color)
{
    Vec2i pMax, pMin = pMax = this->p0;

    pMin.x = std::min(this->p0.x, std::min(this->p1.x, this->p2.x));
    pMin.y = std::min(this->p0.y, std::min(this->p1.y, this->p2.y));

    pMax.x = std::max(this->p0.x, std::max(this->p1.x, this->p2.x));
    pMax.y = std::max(this->p0.y, std::max(this->p1.y, this->p2.y));
    
    for(int x = pMin.x; x < pMax.x; x++)
    {
        for(int y = pMin.y; y < pMax.y; y++)
        {
            Vec3f baricentric = CaculateBarycentric(Vec2i(x, y));
            // printf("x = %d y = %d\n", x, y);
            // printf("barX = %.2f barY = %.2f barZ = %.2f\n", baricentric.x, baricentric.y, baricentric.z);
            if(baricentric.x > 0.0f && baricentric.y > 0.0f && baricentric.z > 0.0f)
            {
                image.set(x, y, color);
            }
        }
    }

}
