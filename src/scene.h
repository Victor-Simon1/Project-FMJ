#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "shape.h"

#include <bits/stdc++.h>
#include "../minwin/include/window.h"
using namespace aline;
using namespace minwin;
//using uint = unsigned int;
//using real = double;
//using Vec2i = Vector<int,2ul>;
//using Vec2r = Vector<real,2ul>;

class Scene
{
public:

    Window window;
   /*static uint Sh;//screen height
    static uint Sw;//screen width
    std::vector<Shape> listShape;*/
    Scene(){}
    ~Scene(){}
   /* void add_shape(const Shape &shape)
    {
        listShape.push_back(shape);
    }

    void initialise()
    {
        window.open();
        Sh = window.get_height();
        Sw = window.get_width();
    }

    void run()
    {
        int c;
        while(true)
        {
            for(int i =0;i<listShape.size();i++)
            {

            }

            //
            c = getchar();
            if(c == 'x') break;
        }
        
    }

    void shutdown()
    {
        listShape.clear();
        window.close();
    }
    Vec2r viewport_to_canvas( const Vec2r & point ) 
{
    Vec2r pointInCanvas;
    real Cw = Scene::Sw;
    real Ch = Scene::Sh;
    real Vw = 2;
    real Vh = (Scene::Sh/Scene::Sw) *Vw;
    pointInCanvas[0] = (point[0] * Cw) / Vw;
    pointInCanvas[1] = (point[1] * Ch) / Vh;

    return pointInCanvas;

}
Vec2i canvas_to_window( const Vec2r & point ) 
{
    Vec2i pointInWindows;
    real Cw = Scene::Sw;
    real Ch = Scene::Sh;
    real Vw = 2;
    real Vh = (Scene::Sh/Scene::Sw) *Vw;
    pointInWindows[0] =  Cw  / 2 +  point[0];
    pointInWindows[1] = Ch /2 - point[1];

    return pointInWindows;
}
void draw_line( const Vec2r & v0, const Vec2r & v1 )
{
    real dx = v1[0] - v0[0];
    real dy = v1[1] - v0[1];
    int ax = (int)dx <<1;
    int ay = (int)dy <<1;
    int d = ay - ax;

    for(real x = v0[0],y =v0[0];x<=v1[0];++x)
    {
        window.put_pixel(x,y);
        if(d>=0)
        {
            ++y;
            d = d - ax;
        }
        d = d + ay;
    }
}*/
};


/*
 void draw_wireframe_triangle( const Vec2r & v0
, const Vec2r & v1
, const Vec2r & v2 ) const
{

}

void draw_filled_triangle( const Vec2r & v0
, const Vec2r & v1
, const Vec2r & v2 ) const
{
    
}
*/
#endif