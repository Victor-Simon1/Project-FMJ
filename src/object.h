#include "shape.h"
#include "matrix.h"

using namespace aline;
class Object
{

public:
    Shape sh;
    Vec3r translation;
    Vec3r rot;
    Vec3r scale;

    Object(const Shape &shape,const Vec3r &t,const Vec3r &r,const Vec3r &s)
    {
        sh = shape;
        translation = t;
        rot = r;
        scale = s;
    }

    Matrix<real,4,4> transform()
    {
        Matrix<real,4,4> trans { {1.0,0.0,0.0,translation[0]},{0.0,1.0,0.0,translation[1]},{0.0,0.0,1.0,translation[3]},{0.0,0.0,0.0,1.0} };
        Matrix<real,4,4> sc { {scale[0],0.0,0.0,0.0},{0.0,scale[1],0.0,0.0},{0.0,0.0,scale[2],0.0},{0.0,0.0,0.0,1.0} };
        //Matrix<real,4,4> rot {{1,0,0,translation[0]},{0,1,0,translation[1]},{0,0,1,translation[3]},{0,0,0,1}};


        return trans * sc;
    }
};