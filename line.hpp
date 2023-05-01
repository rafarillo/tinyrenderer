#ifndef __LINE_H__
#define __LINE_H__
#include "tgaimage.h"
#include "geometry.hpp"

class Line
{
    private:
        // int x0, y0, xf, yf; 
        Vec2i p0, pf;
        TGAColor color;
    public:
        Line(Vec2i p0, Vec2i pf, const TGAColor* color=NULL);
        void draw(TGAImage &image);
};

#endif