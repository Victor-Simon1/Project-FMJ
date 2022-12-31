
#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "vector.h" 

class Frustum
{

public:
     real e = 0.5;
     real a = 1;
    Vec4r near_plane = {0.0,0.0,-1.0,-n};
    Vec4r far_plane = {0.0,0.0,1.0,f};
    Vec4r top_plane = {e,0.0,,0.0};
    Vec4r bottom_plane={0.0,e,-a,0.0};
    Vec4r right_plane = {-e,0.0,-1.0,0.0};
    Vec4r left_plane = {e,0.0,-a,0};

    real near_dist,far_dist;
    Frustum(real near_dist,real far_dist):near_dist(near_dist),far_dist(far_dist)
    {
        
    }

    void update(real a,real e,real n)
    {

    }
    Object clip(const Object &obj)
    {
        Object o = obj;

        for(Face f : obj.get_faces())
        {
            real d01 = f.v0 - f.v1;
            real d02= f.v0 - f.v2;
            real d12 = f.v1 - f.v1; 
            Vec4r far;
            if( d01 < d02)
            {
                if(d01 < d12)
                {
                    far
                }
            }
            if(obj.get_vertices()[f.v0])

            if(obj.get_vertices()[f.v1])
            if(obj.get_vertices()[f.v2])
        }
    }
};



#endif 