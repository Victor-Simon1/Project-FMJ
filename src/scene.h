#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "shape.h"
#include <vector>
#include <bits/stdc++.h>
#include "../minwin/include/window.h"
using namespace aline;
using namespace minwin;
//using uint = unsigned int;
//using real = double;
//using Vec2i = Vector<int,2ul>;
//using Vec2r = Vector<real,2ul>;
//export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/victor/Bureau/Vector/minwin/bin

class Scene
{
public:

    Window window;
    uint Sh;//screen height
    uint Sw;//screen width
    std::vector<Shape> listShape;
    bool running;
    Scene():running(true){}
    ~Scene(){}
    void add_shape(const Shape &shape)
    {
        listShape.push_back(shape);
    }

    void initialise()
    {
        window.set_title( "MinWin Test" );
        window.set_width( 600 );
        window.set_height( 600 );
        Sh = 600;
        Sw =600;
        window.register_quit_behavior( new QuitButtonBehavior( *this ) );
        window.register_key_behavior( KEY_X, new QuitKeyBehavior( *this ) );
        window.register_key_behavior( KEY_Q, new QuitKeyBehavior( *this ) );
        //window.register_key_behavior( minwin::KEY_SPACE, new ChangeColorBehavior( *this ) );
  
         // open window
        if( not window.open() )
        {
            std::cerr << "Couldn't open window.\n";
            return;
        }
        
        //Sh = window.get_height();
        //Sw = window.get_width();
    }

    void run()
    {   
        std::vector<Vertex> vertices;
        Vec2r v {-1.0,0.0};
        Vec2r v1 {-0.5,-0.75};
        Vec2r v2 {0.5,-0.75};
        Vec2r v3 {1.0,0.0};
        Vec2r v4 {0.5,0.75};
        Vec2r v5 {-0.5,0.75};
        vertices.push_back(Vertex(v,2.0));
        vertices.push_back(Vertex(v1,2.0));
        vertices.push_back(Vertex(v2,2.0));
        vertices.push_back(Vertex(v3,2.0));
        vertices.push_back(Vertex(v4,2.0));
        vertices.push_back(Vertex(v5,2.0));

        std::vector<Face> faces;
        faces.push_back(Face(0,1,5,WHITE));
        faces.push_back(Face(1,2,4,WHITE));
        faces.push_back(Face(1,4,5,WHITE));
        faces.push_back(Face(2,3,4,WHITE));
        Shape shape = Shape("name",vertices,faces);
        add_shape(shape);
        //std::cout << listShape[0].get_faces().size() << std::endl;
        while( this->running )
        {
            // process keyboard inputs, etc.
            window.process_input();
            window.clear();
            window.set_draw_color( WHITE );
            Vertex v1,v2,v3;
            for(int i =0;i<listShape.size();i++)
            {
                for(int j=0;j<listShape[i].get_faces().size();j++)
                {
                    v1 = listShape[i].get_vertices()[listShape[i].get_faces()[j].v0];
                    v2 = listShape[i].get_vertices()[listShape[i].get_faces()[j].v1];
                    v3 = listShape[i].get_vertices()[listShape[i].get_faces()[j].v2];
                    draw_wireframe_triangle(v1.vert,v2.vert,v3.vert);
                    //draw_line(viewport_to_canvas(v1.vert),viewport_to_canvas(v2.vert));
                    //draw_line(viewport_to_canvas(v1.vert),viewport_to_canvas(v3.vert));
                    //draw_line(viewport_to_canvas(v3.vert),viewport_to_canvas(v2.vert));
                }
               
            }
            // clear window
            
            window.display();
           // break;
        }
        shutdown();
    }
    void shutdown()
    {
        listShape.clear();
        window.close();
    }
Vec2r viewport_to_canvas( const Vec2r & point ) 
{
    Vec2r pointInCanvas;
    real Cw = Sw;
    real Ch = Sh;
    real Vw = 2;
    real Vh = (real)((real)Sh/(real)Sw) *Vw;
    pointInCanvas[0] = (point[0] * Cw) / Vw;
    pointInCanvas[1] = (point[1] * Ch) / Vh;
  //  std::cout << point[0] << " " << point[1]<< " : "; 
   // std::cout << pointInCanvas[0] << " " << pointInCanvas[1]<< " : "; 
    
    return pointInCanvas;

}
Vec2i canvas_to_window( const Vec2r & point ) 
{
    Vec2i pointInWindows;
    int Cw = Sw;
    int Ch = Sh;
    real Vw = 2;
    real Vh = (real)((real)Sh/(real)Sw) *Vw;
    pointInWindows[0] =  (Cw  << 1) +  point[0];
    pointInWindows[1] = (Ch <<1) - point[1];
   // std::cout << pointInWindows[0] << " " << pointInWindows[1]<< std::endl; 
    
    return pointInWindows;
}

 void draw_wireframe_triangle(  Vec2r &v0,Vec2r &v1,Vec2r &v2 ) 
{   
    //std::cout << viewport_to_canvas(v0)[1]<<" "<< v1[1]<< " "<< v2[1]<<std::endl;
    /*if(v1[1]<v0[1])std::swap(v1,v0);
    if(v2[1]<v0[1])std::swap(v2,v0);
    if(v2[1]<v1[1])std::swap(v2,v1);*/
   // std::cout << "clac"<<std::endl;
    Vec2i v0i = canvas_to_window(viewport_to_canvas(v0));
    Vec2i v1i = canvas_to_window(viewport_to_canvas(v1));
    Vec2i v2i = canvas_to_window(viewport_to_canvas(v2));
    //std::cout << "ciic"<<std::endl;
    draw_line(v0i,v1i);
    draw_line(v1i,v2i);
    draw_line(v2i,v0i);
}

void draw_line(  Vec2i & v0,  Vec2i & v1 )
{
    real a =0;
    real dx = (real)v1[0] - (real)v0[0];
    real dy = (real)v1[1] - (real)v0[1];
    //std::cout << dx << dy<<std::endl;
    if(std::abs(dx)>std::abs(dy))
    {
         if(v1[0] == v0[0])
            a = dy / std::abs(dy);
        else{
            if(v1[0] < v0[0]){
                std::swap(v0[0],v1[0]);
                std::swap(v0[1],v1[1]);
            }
            a = dy / dx;
        }
        int y = v0[1];
        for(int x =0;x<=v1[0];x++)
        {
        
            //std::cout << x << " " << (v1[1] ) << " " << (v1[0]- v0[0]) << std::endl;
            window.put_pixel(x,y,WHITE);
            y =(real)y +a;
        }
    }
    else
    {
        if(dy == 0)
        {
            a = dx / std::abs(dx);
        }
        else{
            if(v1[1] < v0[1]){
                std::cout << "avant :" << v0[0] << "/"<<v1[0]<<std::endl;
                std::swap(v0[0],v1[0]);
                std::swap(v0[1],v1[1]);
                std::cout << "apres :" << v0[0] << "/"<<v1[0]<<std::endl;
                //std::swap(v0,v1);
            }
            a = dx / dy;
        }
        //std::cout <<"a:"  <<a << std::endl;
        int x = v0[0];
        for(int y =0;y<=v1[1];y++)
        {
        
            //std::cout << x << " " << (v1[1] ) << " " << (v1[0]- v0[0]) << std::endl;
            window.put_pixel(x,y,WHITE);
            x =(real)x +a;
            //std::cout <<"x :"<<x<<std::endl;
        }
    }
   
}
/*
void draw_line( const Vec2i & v0, const Vec2i & v1 )
{
    //std::cout << (v1[0]- v0[0])<<std::endl;
    
    real a = (v1[1] - v0[1])/ (v1[0]+1- v0[0]);
    std::cout << (v1[0]- v0[0])<< " " << 1750-1500 <<std::endl;
    real b = v0[1]- v0[0] * a;
    int y = 0;
    for(int x =0;x<v1[0];x++)
    {
        y = a *x +b;
        //std::cout << x << " " << (v1[1] ) << " " << (v1[0]- v0[0]) << std::endl;
        window.put_pixel(x,y,WHITE);
    }

}*/
/*
void draw_line( const Vec2i & v0, const Vec2i & v1 )
{
    real dx = v1[0] - v0[0];
    real dy = v1[1] - v0[1];
    int ax = (int)dx <<1;
    int ay = (int)dy <<1;
    int d = 2*ay - ax;
    std::cout << "x"<< v0[0]<<" " << v1[0]<< std::endl;

    for(real x = v0[0],y =v0[1];x<=v1[0];++x)
    {
        window.put_pixel(x,y,WHITE);
        //std::cout << "put"<<std::endl;
        if(d>=0)
        {
            ++y;
            
            d = d - ax;
        }
        d = d + 2*ay;
    }
}*/
 class QuitButtonBehavior : public minwin::IButtonBehavior
  {
    public:
      QuitButtonBehavior( Scene & app ) : owner { app } {}
      void on_click() const override;
    private:
      Scene & owner;
  };
  
  class QuitKeyBehavior : public minwin::IKeyBehavior
  {
    public:
      QuitKeyBehavior( Scene & app ) : owner { app } {}
      void on_press() const override;
      void on_release() const override;
    private:
      Scene & owner;
  };
  

};
/*
void swap(const Vec2r &v0,const Vec2r &v1)
{
    Vec2r temp = v0;
    v0 = v1;
    v1 = temp;
}*/
void Scene::QuitButtonBehavior::on_click() const { this->owner.running = false; }

void Scene::QuitKeyBehavior::on_press() const   { this->owner.running = false; }
void Scene::QuitKeyBehavior::on_release() const {} // does nothing


/*
void draw_filled_triangle( const Vec2r & v0
, const Vec2r & v1
, const Vec2r & v2 ) const
{
    
}
*/
#endif