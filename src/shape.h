#include "vector.h"
#include "color.h"

using uint = unsigned int;
using real = double;
using Vec2i = Vector<int,2ul>;
using Vec2r = Vector<real,3ul>;
class Vertex
{
public:
    Vec2r vert;
    real intensity;
    Vertex(const Vec2r &c,real h)
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
    Face(uint v0,uint v1,uint v2;const Color &color):v0(v0),v1(v1),v2(v2),color(color)
    {

    }
};

class Shape
{
public:
    std::string name;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    Shape( const std::string & name, const std::vector<Vertex> & vertices, const std::vector<Face> & faces)
    {
        name = name;
        vertices=vertices;
        faces=faces;
    }

    std::string get_name()
    {
        return name;
    }
    std::vector<Vertex> get_vertices() const
    {
        return vertices;
    }

    std::vector<Face> get_faces() const
    {
        return faces;
    }
};