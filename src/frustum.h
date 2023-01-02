
#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "vector.h" 
#include <vector>

class Frustum
{

public:
    real e = 2.0;
    real a = 1;
    Vec4r near_plane ;//= {0.0,0.0,-1.0,-n};
    Vec4r far_plane ;//= {0.0,0.0,1.0,f};
    Vec4r top_plane ;//= {e,0.0,,0.0};
    Vec4r bottom_plane;//={0.0,e,-a,0.0};
    Vec4r right_plane ;//= {-e,0.0,-1.0,0.0};
    Vec4r left_plane ;//= {e,0.0,-a,0};

    real near_dist,far_dist;
    Frustum(real near_dist,real far_dist):near_dist(near_dist),far_dist(far_dist)
    {
        near_plane = {0.0,0.0,-1.0,-near_dist};
        far_plane = {0.0,0.0,1.0,far_dist};
        top_plane = {e,0.0,-a,0.0};
        bottom_plane={0.0,e,-a,0.0};
        right_plane = {-e,0.0,-1.0,0.0};
        left_plane = {e,0.0,-a,0};
    }

    void update(real a,real e,real n)
    {

    }
    Object clip(const Object &obj)
    {
        Object o;
      //  std::cout << "face" << std::endl;
        Shape sh = Shape("",std::vector<Vertex>(),std::vector<Face>());
       // std::cout << "face" << std::endl;
        for(Face f : obj.get_faces())
        {/*
            real d01 = norm(obj.get_vertices()[f.v0].vert - obj.get_vertices()[f.v1].vert);
            real d02= norm(obj.get_vertices()[f.v0].vert - obj.get_vertices()[f.v2].vert);
            real d12 = norm(obj.get_vertices()[f.v1].vert - obj.get_vertices()[f.v2].vert); 
            Vec4r far,v1;
            if( d01 > d02)
            {
                if(d01 < d12)
                {
                    far = obj.get_vertices()[f.v1].vert + obj.get_vertices()[f.v2].vert;
                }
                else
                {
                    far = obj.get_vertices()[f.v1].vert + obj.get_vertices()[f.v0].vert;    
                }
                v1 =  obj.get_vertices()[f.v1].vert;
            }
            else
            {
                if(d02 < d12)
                {
                    far = obj.get_vertices()[f.v1].vert + obj.get_vertices()[f.v2].vert;
                }
                else
                {
                    far = obj.get_vertices()[f.v0].vert + obj.get_vertices()[f.v2].vert;
                }
                v1 =  obj.get_vertices()[f.v2].vert;
            }
                   
            far = far * 0.5;
            real r = norm(v1 - far);
*/          
            std::cout << "neear plane" << std::endl;
            //near_plane
        //    std::cout << near_plane << std::endl;
       //     std::cout <<f.v0 << std::endl;
        //    std::cout <<obj.get_vertices()[f.v0-1].vert << std::endl;
            real s0 = dot(Vec3r({near_plane[0],near_plane[1],near_plane[2]}),Vec3r({obj.get_vertices()[f.v0-1].vert[0],obj.get_vertices()[f.v0-1].vert[1],obj.get_vertices()[f.v0-1].vert[2]})) + near_plane[3];
          //  std::cout << s0 << std::endl;
            real s1 = dot(Vec3r({near_plane[0],near_plane[1],near_plane[2]}),Vec3r({obj.get_vertices()[f.v1-1].vert[0],obj.get_vertices()[f.v1-1].vert[1],obj.get_vertices()[f.v1-1].vert[2]})) + near_plane[3];
          //   std::cout << s1 << std::endl;
            real s2 = dot(Vec3r({near_plane[0],near_plane[1],near_plane[2]}),Vec3r({obj.get_vertices()[f.v2-1].vert[0],obj.get_vertices()[f.v2-1].vert[1],obj.get_vertices()[f.v2-1].vert[2]})) + near_plane[3];
           
          
         //  std::cout << s2 << std::endl;
            Vertex v0 = obj.get_vertices()[f.v0-1];
            Vertex v1 = obj.get_vertices()[f.v1-1];
            Vertex v2 = obj.get_vertices()[f.v2-1];
          //  std::cout << s0 << " : "<< s1 << " : " << s2 << std::endl;
            if(s0 >=0 && s1 >=0 && s2 >=0)//accepted
            {
                std::cout << "3" << std::endl;
                sh.get_vertices().push_back(v0);
                sh.get_vertices().push_back(v1);
                sh.get_vertices().push_back(v2);
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if(s0 >=0 && s1 >=0 && s2 <0)
            {
                std::cout << "2" << std::endl;
                sh.get_vertices().push_back(v0);
                sh.get_vertices().push_back(v1);
                real t = -dot(near_plane, v0.vert) / dot(near_plane,v2.vert-v0.vert);
                Vec4r p = v0.vert + t * (v2.vert - v0.vert);
                real t1 = -dot(near_plane, v1.vert) / dot(near_plane,v2.vert-v1.vert);
                Vec4r p1 = v1.vert + t1 * (v2.vert - v1.vert);

            //    sh.get_vertices().push_back(v0);
            //    sh.get_vertices().push_back(v1);
               
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-3,size-2,size,f.color));
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if(s0 >=0 && s2 >=0 && s1 <0)
            { std::cout << "2" << std::endl;
                sh.get_vertices().push_back(v0);
                sh.get_vertices().push_back(v2);
                
                real t = -dot(near_plane, v0.vert) / dot(near_plane,v1.vert-v0.vert);
                Vec4r p = v0.vert + t * (v1.vert - v0.vert);
                real t1 = -dot(near_plane, v1.vert) / dot(near_plane,v1.vert-v2.vert);
                Vec4r p1 = v2.vert + t1 * (v1.vert - v2.vert);

             //   sh.get_vertices().push_back(v0);
            //    sh.get_vertices().push_back(v1);
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-3,size-2,size,f.color));
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if(s1 >=0 && s2 >=0 && s0 <0)
            { std::cout << "2" << std::endl;
                sh.get_vertices().push_back(v1);
                sh.get_vertices().push_back(v2);
                real t = -dot(near_plane, v1.vert) / dot(near_plane,v1.vert-v0.vert);
                Vec4r p = v1.vert + t * (v0.vert - v1.vert);
                real t1 = -dot(near_plane, v2.vert) / dot(near_plane,v0.vert-v2.vert);
                Vec4r p1 = v2.vert + t1 * (v0.vert - v2.vert);

             //   sh.get_vertices().push_back(v0);
            //    sh.get_vertices().push_back(v1);
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-3,size-2,size,f.color));
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if (s0>= 0 && s1 <0 && s2<0)
            {
                std::cout << "1" << std::endl;
                sh.get_vertices().push_back(v0);
                real t = -dot(near_plane, v0.vert) / dot(near_plane,v1.vert-v0.vert);
                Vec4r p = v0.vert + t * (v1.vert - v0.vert);
                real t1 = -dot(near_plane, v0.vert) / dot(near_plane,v2.vert-v0.vert);
                Vec4r p1 = v0.vert + t1 * (v2.vert - v0.vert);
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if (s1>= 0 && s0 <0 && s2<0)
            {std::cout << "1" << std::endl;
                sh.get_vertices().push_back(v1);
                real t = -dot(near_plane, v1.vert) / dot(near_plane,v0.vert-v1.vert);
                Vec4r p = v1.vert + t * (v0.vert - v1.vert);
                real t1 = -dot(near_plane, v2.vert) / dot(near_plane,v2.vert-v1.vert);
                Vec4r p1 = v1.vert + t1 * (v2.vert - v1.vert);
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }
            else if (s2>= 0 && s1 <0 && s0<0)
            {std::cout << "1" << std::endl;
                sh.get_vertices().push_back(v2);
                real t = -dot(near_plane, v2.vert) / dot(near_plane,v1.vert-v2.vert);
                Vec4r p = v2.vert + t * (v1.vert - v2.vert);
                real t1 = -dot(near_plane, v2.vert) / dot(near_plane,v0.vert-v2.vert);
                Vec4r p1 = v2.vert + t1 * (v0.vert - v2.vert);
                sh.get_vertices().push_back(Vertex({p[0],p[1],p[2]},1.0));
                sh.get_vertices().push_back(Vertex({p1[0],p1[1],p1[2]},1.0));
                int size = sh.get_vertices().size();
                sh.get_faces().push_back(Face(size-2,size-1,size,f.color));
            }   
           
        }
        return Object(sh,obj.translation,obj.rot,obj.scale);
    }
};



#endif 