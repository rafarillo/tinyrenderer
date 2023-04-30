#include "line.hpp"

Line::Line(int x0, int y0, int xf, int yf, TGAColor* color, float step)
{
    this->x0 = x0;
    this->y0 = y0;
    this->xf = xf;
    this->yf = yf;
    this->step = step;
    if(color)
        this->color = *color;
    else
        this->color = TGAColor(255, 255, 255, 255);
}

void Line::draw1(TGAImage &image)
{
    for(float t = 0.0; t < 1.0; t += this->step)
    {
        int x = this->x0 + (1-t)*this->xf;
        int y = this->y0 + (1-t)*this->yf;

        image.set(x, y, this->color);

    }
}

void Line::draw2(TGAImage &image)
{
    for(int x = this->x0; x <= this->xf; x++)
    {
        float t = (x - this->x0)/(float)(this->xf - this->x0);
        int y = (1.0-t)*this->y0 + t * this->yf;

        image.set(x, y, this->color);

    }
}
