#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "matrix.h"
#include "shape.h"
#include "object.h"
#include "camera.h"
#include "frustum.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>
#include "../minwin/include/window.h"
using namespace aline;
using namespace minwin;

//export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/victor/Bureau/Vector/minwin/bin

enum Mode{WIREFRAME,FILLED};
class Scene
{
public:

    Window window;
    uint Sh;//screen height
    uint Sw;//screen width
    std::vector<Shape> listShape;
    std::vector<Object> listObject;
    bool running;
    Mode mode = WIREFRAME;
    Scene():running(true){}
    ~Scene(){}

    void load_data(int argc,const char* argv)
    {
        for(int i =0;i<argc;i++)
        {
            load_obj_file(argv+i);
        }
    }
    void load_obj_file(const char* file_name)
    {
        std::ifstream f(file_name);
        if(!f)
        {
            std::cerr << "erreur fichier"<<std::endl;
            exit(0);
        }
        std::string line;
        std::string type;
        std::string v1,v2,v3;
        Shape sh;
        std::vector<Vertex> vertices;
        std::vector<Face> faces;
        while(getline(f,line))
        {
            std::stringstream X(line);
            getline(X,type,' ');
            if(type == "v" || type == "f")
            {
                if(type == "v")
                {    
                    getline(X,v1,' ');
                    getline(X,v2,' ');
                    getline(X,v3,' ');
                    Vec4r v { atof(v1.c_str()),atof(v2.c_str()),atof(v3.c_str()),1.0 };
                    vertices.push_back(Vertex(v,0.0));
                }
                else
                {
                    getline(X,v1,' ');
                    getline(X,v2,' ');
                    getline(X,v3,' ');
                   // std::cout << line <<std::endl;
                    faces.push_back(Face(v1,v2,v3,WHITE));
                }
            }
        }
        Object obj = Object(Shape(file_name,vertices,faces),{0,0,0},{0,0,0},{0.5,0.5,0.5});
        listObject.push_back(obj);
        f.clear();
    }
    void unload_data()
    {

    }
    void add_shape(const Shape &shape)
    {
        listShape.push_back(shape);
    }
    void add_object(const Object &obj)
    {
        listObject.push_back(obj);
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
        window.register_key_behavior( KEY_SPACE, new QuitModeBehavior( *this ) );

         // open window
        if( not window.open() )
        {
            std::cerr << "Couldn't open window.\n";
            return;
        }
    }

    void run()
    {   
        //load_obj_file("file/tetrahedron.obj");
        Camera cam = Camera(Sw/Sh);
        Frustum frust = Frustum(2.0,5.0);
        while( this->running )
        {
            // process keyboard inputs, etc.
            window.process_input();
            window.clear();
            window.set_draw_color( WHITE );
     
            Vertex v1,v2,v3;
            for(size_t i =0;i<listObject.size();i++)
            {
                Mat44r o_tt = cam.transform();
                Object o_clip = cam.cull(listObject[i]); 
                std::vector<Vertex> ver = listObject[i].get_vertices();
                for(size_t k = 0;k<ver.size();k++)
                {
                    Vec4r vect = listObject[i].transform() * Vec4r({ ver[k].vert[0],ver[k].vert[1],ver[k].vert[2], 1.0});
                    Vec2r proj = projection2(vect,1);
                    ver[k].vert[0] = proj[0];
                    ver[k].vert[1] = proj[1];
                }
                for(size_t j=0;j<listObject[i].get_faces().size();j++)
                {
                    v1 = ver[listObject[i].get_faces()[j].v0-1];
                    v2 = ver[listObject[i].get_faces()[j].v1-1];
                    v3 = ver[listObject[i].get_faces()[j].v2-1];
                    switch(mode)
                    {
                        case WIREFRAME:
                            draw_wireframe_triangle(v1.vert,v2.vert,v3.vert);
                            break;
                        case FILLED:
                            draw_filled_triangle(v1.vert,v2.vert,v3.vert);
                            break;
                    }
                }
            }
            // clear window
            window.display();
            //break;
        }
        shutdown();
    }
    void shutdown()
    {
        listShape.clear();
        //window.unregister_behaviors();
        window.close();
    }

    Vec2r viewport_to_canvas( const Vec4r & point ) 
    {
        Vec2r pointInCanvas;
        real Cw = Sw;
        real Ch = Sh;
        real Vw = 2;
        real Vh = (real)((real)Sh/(real)Sw) *Vw;

        pointInCanvas[0] = (point[0] * Cw) / Vw;
        pointInCanvas[1] = (point[1] * Ch) / Vh;
        
        return pointInCanvas;

    }
    Vec2r canvas_to_window( const Vec2r & point ) 
    {
        Vec2r pointInWindows;
        int Cw = Sw;
        int Ch = Sh;
        pointInWindows[0] =  (Cw  / (real)2 ) +  point[0];
        pointInWindows[1] = (Ch /(real)2) - point[1];

        return pointInWindows;
    }

    void draw_wireframe_triangle(  Vec4r &v0,Vec4r &v1,Vec4r &v2 ) 
    {   
        draw_line(v0[0],v0[1],v1[0],v1[1]);
        draw_line(v1[0],v1[1],v2[0],v2[1]);
        draw_line(v2[0],v2[1],v0[0],v0[1]);
    }
 
    void draw_filled_triangle(  Vec4r &v0,  Vec4r &v1,  Vec4r &v2 ) 
    {
        int x0=v0[0],y0=v0[1],x1=v1[0],y1=v1[1],x2=v2[0],y2=v2[1];
        if(y1<y0){std::swap(x0,x1);std::swap(y0,y1);}
        if(y2<y0){std::swap(x0,x2);std::swap(y0,y2);}
        if(y2<y1){std::swap(x2,x1);std::swap(y2,y1);}

        auto x02 = interpolate(y0,x0,y2,x2);
        auto x01 = interpolate(y0,x0,y1,x1);
        auto x12 = interpolate(y1,x1,y2,x2);

        x01.pop_back();
        auto x012 = x01;
        x012.insert(x012.end(),x12.begin(),x12.end());
        std::vector<real> x_left,x_right,h_left,h_right;
        auto m= floor(x012.size() / 2);
        if(x02[m] <x012[m])
        {
            x_left = x02;
            x_right = x012;
        }
        else
        {
            x_left = x012;
            x_right = x02;
        }

        for(int y = y0;y<= y2;y++)
        {
            for(int x = x_left[y-y0];x<=x_right[y-(int)y0];++x)
                window.put_pixel(x,y,RED);   
        }
        //shaded
        auto h01 = interpolate(y0,1.0,y1,1.0);
        auto h12 = interpolate(y1,1.0,y2,1.0);
        auto h02 = interpolate(y0,1.0,y2,1.0);
        h01.pop_back();
        auto h012 = h01;
         h012.insert(h012.end(),h12.begin(),h12.end());
        if(x02[m] < x012[m])
        {
            h_left = h02;
            h_right = h012;
        }
        else
        {
            h_left = h012;
            h_right = h02;
        }
        Color color = RED;
        for(int y = y0;y<=y2;++y)
        {
            auto x_l = x_left[y-y0];
            auto x_r = x_right[y - y0];
            auto h_segment = interpolate(x_l,h_left[y-y0],x_r,h_right[y-y0]);
            for(int x = x_left[y-y0];x<=x_right[y-y0];++x)
            {
                Color shaded_color = {(Uint8)(color.r * (Uint8)h_segment[x-x_l]),(Uint8)(color.g * (Uint8)h_segment[x-x_l]),(Uint8)(color.b * (Uint8)h_segment[x-x_l]),0};
                window.put_pixel(x,y,shaded_color);
            }
        }
    }

     Vec2r projection2(Vec4r &v,real d)
    {
        Vec2r v1 = viewport_to_canvas(v);
        if(v[2] != 0.0){
            v1[0] = (-d/ v[2]) * v1[0];
            v1[1] = (-d / v[2]) * v1[1];
        }
       return canvas_to_window(v1);
    }
    std::vector<real> interpolate(int i0,real d0,int i1,real d1)
    {
        std::vector<real> vec;
        if(i0 == i1) 
        {
            vec.push_back(d0);
            return vec;
        }
        real a = ((real)d0 - (real)d1) / ((real)i0 - (real)i1);
        real d = d0;
        
        for(int i =i0;i<=i1;++i )
        {
            vec.push_back((int)d);
            d = (real)d + (real)a;
        }
        return vec;
    }
    void draw_line( real x0,real y0, real x1,real y1 )
    {
        real a =0;
        real dx = (real)x1 - (real)x0;
        real dy = (real)y1 - (real)y0;
        if(std::abs(dx)>std::abs(dy))
        {
            if(dx == (real)0)
                a = (real)dy / (real)std::abs(dy);
            else{
                if(x1 < x0){
                    std::swap(x0,x1);
                    std::swap(y0,y1);
                }
            }
            a = (real)dy / (real)dx;
            real y = y0;
            for(int x =x0;x<=x1;x++)
            {
                window.put_pixel(x,y,WHITE);
                y =(real)y +(real)a;
            }
        }
        else
        {
            if(dy == (real)0)
            {
                a = (real)dx / (real)std::abs(dx);
            }
            else{
                if(y1 < y0){
                    std::swap(x0,x1);
                    std::swap(y0,y1);
                }
                
            }
            a = (real)dx / (real)dy;
            //std::cout <<"a:"  <<a << std::endl;
            real x = x0;
            for(int y =y0;y<=y1;y++)
            {
            
                //std::cout << x << " " << (v1[1] ) << " " << (v1[0]- v0[0]) << std::endl;
                window.put_pixel(x,y,WHITE);
                x =(real)x +(real)a;
                //std::cout <<"x :"<<x<<std::endl;
            }
        }
    
    }


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
  
class QuitModeBehavior : public minwin::IKeyBehavior
  {
    public:
      QuitModeBehavior( Scene & app ) : owner { app } {}
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
void Scene::QuitModeBehavior::on_press() const{
    std::cout << "Changement de mode" << std::endl;
    if(this->owner.mode==WIREFRAME)this->owner.mode = FILLED;
    else this->owner.mode = WIREFRAME;
}

void Scene::QuitModeBehavior::on_release() const {} // does nothing
void Scene::QuitKeyBehavior::on_press() const   { this->owner.running = false; }
void Scene::QuitKeyBehavior::on_release() const {} // does nothing


/*

*/
#endif