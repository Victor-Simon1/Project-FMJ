#ifndef SHAPE_H
#define SHAPE_H
#include "vector.h"
#include "../minwin/include/color.h"
using namespace minwin;
//using uint = unsigned int;
//using real = double;
//using Vec2i = Vector<int,2ul>;
//using Vec2r = Vector<real,3ul>;
template <class T>
class Vertex
{
public:
    T vert;
    real intensity;
    Vertex(){}
    Vertex(const T &c,real h)
    {
        vert = c;
        intensity = h;
    }
    Vertex(std::initializer_list<real> &c,real h)
    {
        vert = c;
        intensity = h;
    }
};

class Face
{
public:
    uint v0,v1,v2;
    Color color;
    Face(uint v0,uint v1,uint v2,const Color &color):v0(v0),v1(v1),v2(v2),color(color)
    {

    }

    Face(std::string v0,std::string v1,std::string v2,const Color &color):color(color)
    {
        this->v0 = std::stoi(v0);
        this->v1 = std::stoi(v1);
        this->v2 = std::stoi(v2);
    }
};

template <class T>
class Shape
{
public:
    std::string name;
    std::vector<Vertex<T>> vertices;
    std::vector<Face> faces;
    Shape( const std::string & pName, const std::vector<Vertex<T>> & pVertices, const std::vector<Face> & pFaces)
    {
        name = pName;
        vertices=pVertices;
        faces=pFaces;
    }
    Shape(){}
    std::string get_name()
    {
        return name;
    }
    std::vector<Vertex<T>> get_vertices() const
    {
        return vertices;
    }

    std::vector<Face> get_faces() const
    {
        return faces;
    }
};

#endif