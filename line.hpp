#ifndef __LINE_H__
#define __LINE_H__
#include "tgaimage.h"

class Line
{
    private:
        int x0, y0, xf, yf; 
        float step;
        TGAColor color;
    public:
        Line(int x0, int y0, int xf, int yf, TGAColor* color=NULL, float step=0.01);
        void draw1(TGAImage &image);
        void draw2(TGAImage &image);
        void drawBest(TGAImage &image);
};

#endif