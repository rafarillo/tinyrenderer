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

void Line::drawBest(TGAImage &image)
{
    bool steep = false;
    if(std::abs(xf - x0) < std::abs(yf - y0)) // if height > width 
    {
        std::swap(x0, y0);
        std::swap(xf, yf);
        steep = true;
    }

    if(x0 > xf)
    {
        std::swap(x0, xf);
    }

    int dx = xf - x0;
    int dy = yf - y0;

    // float dError = std::abs((float) dy/ (float) dx);
    // float error = 0;
    int dError = std::abs(dy)*2;
    int error = 0;
    int y = this->y0;

    for(int x = this->x0; x <= this->xf; x++)
    {

        steep? image.set(y, x, this->color) : image.set(x, y, this->color);
        error += dError;

        if(error > dx)
        {
            y += (this->yf > this->y0? 1 : -1);
            error -= 2*dx;
        }
    }

}
