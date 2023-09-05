#include "line.hpp"

Line::Line(int x0, int y0, int xf, int yf)
{
    this->x0 = x0;
    this->xf = xf;
    this->y0 = y0;
    this->yf = yf;
}

void Line::draw1(TGAImage &image, TGAColor color)
{
    for(float t = 0.0; t <= 1.0; t += 0.01)
    {
        float x = (float)this->x0 + (this->xf - this->x0) * t;
        float y = (float)this->y0 + (this->yf - this->y0) * t;
        image.set(x, y, color);
    }
}

void Line::draw2(TGAImage &image, TGAColor color)
{
    float den = this->xf - this->x0;
    for(int x = this->x0; x < this->xf; x++)
    {
        float t = (float)(x - this->x0)/den;
        float y = this->y0 * (1.0 - t) + this->yf * t;
        image.set(x, y, color);
    }
}
