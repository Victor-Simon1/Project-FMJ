#include "shape.h"
#include "matrix.h"
class Object
{

public:
    Shape<Vec3r> sh;
    Vec3r translation;
    Vec3r rot;
    Vec3r scale;

    Object(const Shape<Vec3r> &shape,const Vec3r &t,const Vec3r &r,const Vec3r &s)
    {
        sh = shape;
        translation = t;
        rot = r;
        scale = s;
    }

    aline::Matrix<real,4> transform()
    {

    }
};