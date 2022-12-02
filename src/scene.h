#include "shape.h"


class Scene()
{
public:
    minwin::Window window;
    real Sh;//screen height
    real Sw;//screen width

    Scene();

    void add_shape(const Shape &shape)
    {

    }

    void initialise()
    {
        window.open();
        height = window.height();
        width = window.width();
    }

    void run()
    {

    }

    void shutdown()
    {
        window.close()
    }
}

Vec2r viewport_to_canvas( const Vec2r & point ) const
{
    Vec2r pointInCanvas;
    real Cw = Sw;
    real Ch = Sh;
    real Vw = 2;
    real Vh = (Sh/Sw) *Vw;
    pointInCanvas[0] = (point[0] * Cw) / Vw;
    pointInCanvas[1] = (point[1] * Ch) / Vh;

    return pointInCanvas;

}
Vec2i canvas_to_window( const Vec2r & point ) const
{
    Vec2r pointInWindows;
    real Cw = Sw;
    real Ch = Sh;
    real Vw = 2;
    real Vh = (Sh/Sw) *Vw;
    pointInWindows[0] =  Cw  / 2 +  point[0];
    pointInWindows[1] = Ch /2 - point[1];

    return pointInWindows;
}
void draw_line( const Vec2r & v0, const Vec2r & v1 ) const
{
    real dx = v1[0] - v0[0];
    real dy = v1[1] - v0[1];
    real ax = dx <<1;
    real ay = dy <<1;
    real d = ay - ax;

    for(real x = v0[0],y =v0[0];x<=v1[0],++x)
    {
        window.put_pixel(x,y);
        if(d>=0)
        {
            ++y;
            d = d - ax;
        }
        d = d + ay;
    }
}

