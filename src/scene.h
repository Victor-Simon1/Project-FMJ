#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "shape.h"
#include "object.h"
#include <vector>
#include <algorithm>
#include <fstream>
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
    std::vector<Shape<Vec2r>> listShape;
    std::vector<Object> listObject;
    bool running;
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
        std::vector<std::string> value;
        Shape sh;
        std::vector<Vertex<Vec3r>> vertices;
        std::vector<Face> faces;
        while(getline(f,line))
        {
            char* ptr = strtok(line.c_str()," ");//v ou f
            type = ptr;
            while(ptr != nullptr)
            {
                ptr = strtok(nullptr," ");
                value.push_back(ptr);
            }
             if(type == "v")
            {
                vertices.push_back(Vertex({value[0],value[1],value[2]},0));
            }
            else
            {
                face.push_back(Face({value[0],value[1],value[2]},0))
            }
        }
       
        Object obj = Object(Shape<Vec3r>("",vertices,faces),{0,0,0},{0,0,0},{0,0,0});
        listObject.push_back(obj);
        f.clear();
    }
    void unload_data()
    {

    }
    void add_shape(const Shape<Vec2r> &shape)
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
        std::vector<Vertex<Vec2r> vertices;
        Vec2r v {-1.0,0.0};
        Vec2r v1 {-0.5,-0.75};
        Vec2r v2 {0.5,-0.75};
        Vec2r v3 {1.0,0.0};
        Vec2r v4 {0.5,0.75};
        Vec2r v5 {-0.5,0.75};
        vertices.push_back(Vertex<Vec2r>(v,2.0));
        vertices.push_back(Vertex<Vec2r>(v1,2.0));
        vertices.push_back(Vertex<Vec2r>(v2,2.0));
        vertices.push_back(Vertex<Vec2r>(v3,2.0));
        vertices.push_back(Vertex<Vec2r>(v4,2.0));
        vertices.push_back(Vertex<Vec2r>(v5,2.0));

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
                    //draw_filled_triangle(v1.vert,v2.vert,v3.vert);
                    //draw_line(viewport_to_canvas(v1.vert),viewport_to_canvas(v2.vert));
                    //draw_line(viewport_to_canvas(v1.vert),viewport_to_canvas(v3.vert));
                    //draw_line(viewport_to_canvas(v3.vert),viewport_to_canvas(v2.vert));
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
        //std::cout << point[0] << " " << point[1]<< " : "; 
        //std::cout << pointInCanvas[0] << " " << pointInCanvas[1]<< " : "; 
        
        return pointInCanvas;

    }
    Vec2i canvas_to_window( const Vec2r & point ) 
    {
        Vec2i pointInWindows;
        int Cw = Sw;
        int Ch = Sh;
        real Vw = 2;
        real Vh = (real)((real)Sh/(real)Sw) *Vw;
        pointInWindows[0] =  (Cw  / (real)2 ) +  point[0];
        pointInWindows[1] = (Ch /(real)2) - point[1];
        //std::cout << pointInWindows[0] << " " << pointInWindows[1]<< std::endl; 
        
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
    std::vector<int> concat(std::vector<int> &v0,std::vector<int> &v1)
    {
        std::vector<int> v2 = v0;
        for(int i = 0;i<v1.size();i++)
        {
            if(!(std::find(v2.begin(),v2.end(),v1[i])!=v2.end()))
                v2.push_back(v1[i]);
        }

        return v2;
    }
    void draw_filled_triangle(  Vec2r &v0,  Vec2r &v1,  Vec2r &v2 ) 
    {
        Vec2i v0i = canvas_to_window(viewport_to_canvas(v0));
        Vec2i v1i = canvas_to_window(viewport_to_canvas(v1));
        Vec2i v2i = canvas_to_window(viewport_to_canvas(v2));
        int x0=v0i[0],y0=v0i[1],x1=v1i[0],y1=v1i[1],x2=v2i[0],y2=v2i[1];
        if(v1i[1]<v0i[1]){std::swap(x0,x1);std::swap(y0,y1);}
        if(v2i[1]<v0i[1]){std::swap(x0,x2);std::swap(y0,y2);}
        if(v2i[1]<v1i[1]){std::swap(x2,x1);std::swap(y2,y1);}
        std::cout << "Jai swap"<<std::endl;
        auto x02 = interpolate(y0,x0,y2,x2);
        auto x01 = interpolate(y0,x0,y1,y0);
        auto x12 = interpolate(y1,x1,y2,x2);
        std::cout << "Jai interpolé"<<std::endl;
    // x01.pop_back();
        auto x012 = concat(x01,x12);
        std::vector<int> x_left,x_right,h_left,h_right;
        auto m= floor(x012.size() / 2);
        std::cout << "Jai concat "<< x02.size() << std::endl;
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
        std::cout << "J'ai xleft"<< std::endl;
        for(int y = v0i[1];y<= v2i[1];y++)
        {
            //std::cout << "y : "<<y-v0i[1] <<std::endl;
            //std::cout << "y : "<<y << " " <<v1i[1]<< " "<<y - (int)v1i[1] <<std::endl;
            if(y-(int)v1i[1]>0)
            {
                for(int x = x_left[y-y0];x<=x_right[y-(int)y0];++x)
                window.put_pixel(x,y,WHITE);
            }
            
        }
        //shaded
        std::cout << "Jai put"<< std::endl;
        //x01 = interpolate(y0,x0,y1,x1);
        auto h01 = interpolate(y0,1,y1,1);

        //x12 = interpolate(y1,x1,y2,x2);
        auto h12 = interpolate(y1,1,y2,1);

        //x02 = interpolate(y0,x0,y2,x2);
        auto h02 = interpolate(y0,1,y2,1);

        //x01.pop_back();
       // x012 = concat(x01,x12);

    // h01.pop_back();
        auto h012 = concat(h01,h12);

       // m = floor(x012.size() /2 );
        if(x02[m] < x012[m])
        {
           // x_left = x02;
            h_left = h02;

            //x_right = x012;
            h_right = h012;
        }
        else
        {
          //  x_left = x012;
            h_left = h012;

           // x_right = x02;
            h_right = h02;
        }
        auto color = 2;
        for(int y = y0;y<=y2;++y)
        {
            auto x_l = x_left[y-y0];
            auto x_r = x_right[y - y0];
            //std::cout << y - y0 << std::endl;
           // auto h_segment = interpolate(x_l,h_left[y-y0],x_r,h_right[y-y0]);
            for(int x = x_left[y-y0];x<=x_right[y-y0];++x)
            {
               // auto shaded_color = color * h_segment[x-x_l];
                window.put_pixel(x,y,RED);
            }
        }
    }

    std::vector<int> interpolate(int i0,int d0,int i1,int d1)
    {
        std::vector<int> vec;
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
    void draw_line(  Vec2i & v0,  Vec2i & v1 )
    {
        real a =0;
        int x0= v0[0],x1=v1[0],y0=v0[1],y1=v1[1];
        real dx = (real)x1 - (real)x0;
        real dy = (real)y1 - (real)y0;
        //std::cout << dx << dy<<std::endl;
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
            
                //std::cout << x << " " << (v1[1] ) << " " << (v1[0]- v0[0]) << std::endl;
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
                    //std::cout << "avant :" << v0[0] << "/"<<v1[0]<<std::endl;
                    std::swap(x0,x1);
                    std::swap(y0,y1);
                    //std::cout << "apres :" << v0[0] << "/"<<v1[0]<<std::endl;
                    //std::swap(v0,v1);
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

/*
void draw_line( const Vec2i & v0, const Vec2i & v1 )
{
    real dx = v1[0] - v0[0];
    real dy = v1[1] - v0[1];
    int ax = (int)dx <<1;
    int ay = (int)dy <<1;
    int d = 2*ay - ax;
    std::cout << "x"<< v0[0]<<" " << v1[0]<< std::endl;
    real y = (real)v0[1];
    for(int x = v0[0];x<=v1[0];++x)
    {
        window.put_pixel(x,y,WHITE);
        //std::cout << "put"<<std::endl;
        if(d>=0)
        {
            y = (real)y + (real)1;
            
            d = (real)d - (real)ax;
        }
        d = (real)d + (real)2*(real)ay;
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

*/
#endif