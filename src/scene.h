#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "shape.h"
#include "object.h"
#include <vector>
#include <sstream>
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
        std::string v1,v2,v3;
        Shape<Vec3r> sh;
        std::vector<Vertex<Vec3r>> vertices;
        std::vector<Face> faces;
        while(getline(f,line))
        {
            std::stringstream X(line);
            getline(X,type,' ');
            if(type == "v" || type == "f")
            {
                std::cout << type << std::endl;
                if(type == "v")
                {
                    
                    getline(X,v1,' ');
                    getline(X,v2,' ');
                    getline(X,v3,' ');
                   // std::cout <<"slt";//atof(value[0].c_str())<<std::endl;
                    Vec3r v {atof(v1.c_str()),atof(v2.c_str()),atof(v3.c_str())};
                    //std::cout << v << std::endl;
                    vertices.push_back(Vertex<Vec3r>(v,0.0));
                    
                }
                else
                {
                    getline(X,v1,' ');
                    getline(X,v2,' ');
                    getline(X,v3,' ');
                    std::cout << line <<std::endl;
                    faces.push_back(Face(v1,v2,v3,WHITE));
                }
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
        load_obj_file("file/tetrahedron.obj");

        while( this->running )
        {
            // process keyboard inputs, etc.
            window.process_input();
            window.clear();
            window.set_draw_color( WHITE );
            Vertex<Vec3r> v1,v2,v3;
            for(int i =0;i<listObject.size();i++)
            {
                for(int j=0;j<listObject[i].sh.get_faces().size();j++)
                {
                    v1 = listObject[i].sh.get_vertices()[listObject[i].sh.get_faces()[j].v0-1];
                    v2 = listObject[i].sh.get_vertices()[listObject[i].sh.get_faces()[j].v1-1];
                    v3 = listObject[i].sh.get_vertices()[listObject[i].sh.get_faces()[j].v2-1];
                   // std::cout <<" jai mis dans les var"<< std::endl;
                    draw_wireframe_triangle(v1.vert,v2.vert,v3.vert);
                    //draw_filled_triangle(3Dto2d(v1.vert,v2.vert,v3.vert);

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

    void draw_wireframe_triangle(  Vec3r &v0,Vec3r &v1,Vec3r &v2 ) 
    {   
        //std::cout << viewport_to_canvas(v0)[1]<<" "<< v1[1]<< " "<< v2[1]<<std::endl;
        /*if(v1[1]<v0[1])std::swap(v1,v0);
        if(v2[1]<v0[1])std::swap(v2,v0);
        if(v2[1]<v1[1])std::swap(v2,v1);*/
    // std::cout << "clac"<<std::endl;
        real d = 0.5;
        Vec2i v0i = canvas_to_window(/*viewport_to_canvas(*/projection2(v0,d))/*)*/;
        Vec2i v1i = canvas_to_window(/*viewport_to_canvas(*/projection2(v1,d))/*)*/;
        Vec2i v2i = canvas_to_window(/*viewport_to_canvas(*/projection2(v2,d))/*)*/;
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
        if(y1<y0){std::swap(x0,x1);std::swap(y0,y1);}
        if(y2<y0){std::swap(x0,x2);std::swap(y0,y2);}
        if(y2<y1){std::swap(x2,x1);std::swap(y2,y1);}
        //std::cout << "Jai swap"<<std::endl;
        auto x02 = interpolate(y0,x0,y2,x2);
        auto x01 = interpolate(y0,x0,y1,x1);
        auto x12 = interpolate(y1,x1,y2,x2);
        //std::cout << "Jai interpolé"<<std::endl;
        x01.pop_back();
        auto x012 = x01;//concat(x01,x12);
        x012.insert(x012.end(),x12.begin(),x12.end());
        std::vector<real> x_left,x_right,h_left,h_right;
        auto m= floor(x012.size() / 2);
        //std::cout << "Jai concat "<< x02.size() << std::endl;
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
       // std::cout << "J'ai xleft"<< std::endl;
        for(int y = v0i[1];y<= v2i[1];y++)
        {
            //std::cout << "y : "<<y-v0i[1] <<std::endl;
            //std::cout << "y : "<<y << " " <<v1i[1]<< " "<<y - (int)v1i[1] <<std::endl;
            //if(y-(int)v1i[1]>0)
           // {
                for(int x = x_left[y-y0];x<=x_right[y-(int)y0];++x)
                    window.put_pixel(x,y,RED);
          //  }
            
        }
        //shaded
        //x01 = interpolate(y0,x0,y1,x1);
        auto h01 = interpolate(y0,1.0,y1,1.0);
        //x12 = interpolate(y1,x1,y2,x2);
        auto h12 = interpolate(y1,1.0,y2,1.0);
        //x02 = interpolate(y0,x0,y2,x2);
        auto h02 = interpolate(y0,1.0,y2,1.0);
       // x012 = concat(x01,x12);
        h01.pop_back();
        auto h012 = h01;//concat(h01,h12);
         h012.insert(h012.end(),h12.begin(),h12.end());
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
        Color color = RED;
        for(int y = y0;y<=y2;++y)
        {
            auto x_l = x_left[y-y0];
            auto x_r = x_right[y - y0];
            //std::cout << y - y0 << std::endl;
            auto h_segment = interpolate(x_l,h_left[y-y0],x_r,h_right[y-y0]);
            for(int x = x_left[y-y0];x<=x_right[y-y0];++x)
            {
                //{ 255,255,255, 0 }
                Color shaded_color = {color.r * h_segment[x-x_l],color.g * h_segment[x-x_l],color.b * h_segment[x-x_l],0};
                //std::cout << "shaded"<< to_string(shaded_color) << std::endl;
                window.put_pixel(x,y,shaded_color);
            }
        }
    }
    Vec2r projection(Vec3r &v)
    {
        Vec2r v1;
        if(v[2] != 0.0){
        v1[0] = (-0.5/ v[2]) * v[0];
        v1[1] = (-0.5 / v[2]) * v[1];
        }
        else
        {
            v1[0] = v[0];
            v1[1] =  v[1];
        }
        std::cout << v << std::endl;
        std::cout << v1 << std::endl;
        return v1;


    }
     Vec2r projection2(Vec3r &v,real d)
    {
        real Vw = 2.0;
        real Vh = (Sh/(real)Sw) *Vw;
        Vector<real,4> v1 {v[0],v[1],v[2],1.0};
        Matrix<real,4,4> m  { {(real)Sw/Vw, 0.0, 0.0,0.0}, {0.0, (real)Sh/Vh, 0.0,0.0}, {0.0,0.0, 1.0, 0.0} ,{0.0,0.0,0.0,1.0}};
        Matrix<real,4,4> m1  { {d, 0.0, 0.0,0.0}, {0.0,d, 0.0,0.0}, {0.0,0.0, 1.0, 0.0} ,{0.0,0.0,0.0,1.0}};
       
       Vector<real,4> v2 = m*m1*v1;
       std::cout << v << std::endl;
      
       /* if(v[2] != 0.0){
        v1[0] = (-0.5/ v[2]) * v[0];
        v1[1] = (-0.5 / v[2]) * v[1];
        }
        else
        {
            v1[0] = v[0];
            v1[1] =  v[1];
        }
        std::cout << v << std::endl;
        std::cout << v1 << std::endl;*/
        Vec2r v3 {v2[0],v2[1]};
         std::cout << v3 << std::endl;
        return v3;


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