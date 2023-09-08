#include "triangle.hpp"

int Triangle::CalculateX(int y, Line l)
{
    Vec2 p0 = l.getP0(), 
        pf = l.getPf();
    float m = (pf.y - p0.y)/(float)(pf.x - p0.x);
    float x = (y - p0.y)/m + p0.x;
    return (int) x;
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
