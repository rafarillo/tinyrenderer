#include "line.hpp"

Line::Line(Vec2i p0, Vec2i pf, const TGAColor* color)
{
    this->p0 = p0;
    this->pf = pf;
    if(color)
        this->color = *color;
    else
        this->color = TGAColor(255, 255, 255, 255);
}

void Line::draw(TGAImage &image)
{
    int x0 = p0.x;
    int y0 = p0.y;

    int xf = pf.x;
    int yf = pf.y;

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
        std::swap(y0, yf);

    }

    int dx = xf - x0;
    int dy = yf - y0;

    // float dError = std::abs((float) dy/ (float) dx);
    // float error = 0;
    
    int dError = std::abs(dy)*2;
    int error = 0;
    int y = y0;

    for(int x = x0; x <= xf; x++)
    {

        steep? image.set(y, x, this->color) : image.set(x, y, this->color);
        error += dError;

        if(error > dx)
        {
            y += (yf > y0? 1 : -1);
            error -= 2*dx;
        }
    }

}
