#include "tgaimage.h"

class Line
{
    private:
    int x0, y0, xf, yf;

    public:
    Line(int x0, int y0, int xf, int yf);
    void draw1(TGAImage &image, TGAColor color);
    void draw2(TGAImage &image, TGAColor color);

};