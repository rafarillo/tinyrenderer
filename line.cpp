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

void Line::draw3(TGAImage &image, TGAColor color)
{
    int dx = std::abs(this->x0 - this->xf);
    int dy = std::abs(this->y0 - this->yf);
    bool swap = false;
    if(dx < dy)
    {
        std::swap(this->x0, this->y0);
        std::swap(this->xf, this->yf);
        swap = true;
    }

    if(this->x0 > this->xf)
    {
        std::swap(this->x0, this->xf);
        std::swap(this->y0, this->yf);
    }

    float den = this->xf - this->x0;
    for(int x = this->x0; x < this->xf; x++)
    {
        float t = (x - this->x0)/den;
        float y = this->y0 * (1.0 - t) + this->yf * t;
        if(swap)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
    }

}

void Line::draw4(TGAImage &image, TGAColor color)
{
    int dx = std::abs(this->x0 - this->xf);
    int dy = std::abs(this->y0 - this->yf);
    bool swap = false;
    if(dx < dy)
    {
        std::swap(this->x0, this->y0);
        std::swap(this->xf, this->yf);
        swap = true;
    }

    if(this->x0 > this->xf)
    {
        std::swap(this->x0, this->xf);
        std::swap(this->y0, this->yf);
    }

    dx = this->xf - this->x0;
    dy = this->yf - this->y0;
    float m = (float) dy / (float) dx;
    float err = 0;
    int y = y0;
    for(int x = this->x0; x < this->xf; x++)
    {
        if(swap)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
        err += m;
        if(err > 0.5)
        {
            y = (this->yf > this->y0)? 1:-1;
            err -= 1.0;
        }
    }

}

void Line::draw5(TGAImage &image, TGAColor color)
{
    int dx = std::abs(this->x0 - this->xf);
    int dy = std::abs(this->y0 - this->yf);
    bool swap = false;
    if(dx < dy)
    {
        std::swap(this->x0, this->y0);
        std::swap(this->xf, this->yf);
        swap = true;
    }

    if(this->x0 > this->xf)
    {
        std::swap(this->x0, this->xf);
        std::swap(this->y0, this->yf);
    }

    dx = this->xf - this->x0;
    int m = dy*2;
    int err = 0;
    int y = y0;

    for(int x = this->x0; x < this->xf; x++)
    {
        if(swap)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }

        err += m;
        if(err > dx)
        {
            y = (this->yf > this->y0)? 1:-1;
            err -= 2*dx;
        }
    }
}
