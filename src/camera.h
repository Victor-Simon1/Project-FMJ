#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "matrix.h"
#include <cmath>
class Camera
{

public:

    real aspect_ratio;
    real focal_dist=2.0;
    Vec4r position {0.0,0.0,0.0,1.0};
    Vec3r orientation  {0.0,0.0,0.0};
    Vec4r move_vec {0.0,0.0,0.0,0.0};
    Vec3r rot_vec {0.0,0.0,0.0};
    real move_speed = 0.125;
    real rot_speed = 0.25;
    real zoom_speed = 0.0625;
    bool is_moving = false;
    bool is_rotating = false;
    Camera(real aspect_ratio,
            real focal_dist=2.0,
            Vec4r position ={0.0,0.0,0.0,1.0},
            Vec3r orientation = {0.0,0.0,0.0},
            real move_speed = 0.125,
            real rot_speed = 0.25,
            real zoom_speed = 0.0625)
    {
        aspect_ratio = aspect_ratio;
        focal_dist=focal_dist;
        position = position;
        orientation = orientation;
        move_speed = move_speed;
        rot_speed = rot_speed;
        zoom_speed = zoom_speed;
    }

    void move_forward(uint axis)
    {
        if(axis == 0) move_vec = Vec4r({1.0,0.0,0.0,0.0});
        else if(axis == 1)move_vec = Vec4r({0.0,1.0,0.0,0.0});
        else move_vec = Vec4r({0.0,0.0,1.0,0.0});


       // position = position + move_speed * (orientation * a * unit_vector(orientation));
    }
    void move_backward(uint axis)
    {
        if(axis == 0) move_vec = Vec4r({-1.0,0.0,0.0,0.0});
        else if(axis == 1)move_vec = Vec4r({0.0,-1.0,0.0,0.0});
        else move_vec = Vec4r({0.0,0.0,-1.0,0.0});
       // position = position  - move_speed * (orientation * a * unit_vector(orientation));
    }
    void rotate_cw(uint axis)
    {
        if(axis == 0) rot_vec = Vec3r({1.0,0.0,0.0});
        else if(axis == 1)rot_vec = Vec3r({0.0,1.0,0.0});
        else rot_vec = Vec3r({0.0,0.0,1.0});
        //orientation = orientation * rot_speed *(cos(0.5) + a *sin(0.5));
    }
    void rotate_acw(uint axis)
    {
        if(axis == 0) rot_vec = Vec3r({1.0,0.0,0.0});
        else if(axis == 1)rot_vec = Vec3r({0.0,1.0,0.0});
        else rot_vec = Vec3r({0.0,0.0,1.0});
        //orientation = orientation * (-rot_speed) *(cos(0.5) + a *sin(0.5));
    }
    void zoom_in(uint axis)
    {

    }
    void zoom_out(uint axis)
    {

    }
    void stop_movement()
    {
        move_vec = Vec4r({0,0,0,0});
        is_moving = false;
    }
    void stop_rotation()
    {
        rot_vec = Vec3r({0,0,0});
        is_rotating = true;
    }
    void stop_zoom()
    {

    }
    Mat44r transform() const
    {
        
        //Mat44r qMat { {orientation[0],-orientation[1],-orientation[2],-orientation[3]},{orientation[1],orientation[0],-orientation[3],orientation[2]},
        //            {orientation[2],orientation[3],orientation[0],-orientation[1]},{orientation[3],orientation[0],orientation[0],orientation[0]}};
        
        Vec3r qInv  {-orientation[0],-orientation[1],-orientation[2]};
        qInv = qInv * (1/(pow(orientation[0],2)+pow(orientation[1],2)+pow(orientation[2],2) + pow(cos(0.5),2)));
        real w = cos(0.5);
        Mat44r qMat {
                    {1 - 2*pow(qInv[1],2)-2*pow(qInv[2],2),2*qInv[0]*qInv[1]-2*w*qInv[2],2*qInv[0]*qInv[2]+2*w*qInv[1],0},
                    {2*qInv[0]*qInv[1]+2*w*qInv[2],1 - 2*pow(qInv[0],2)-2*pow(qInv[2],2),2*qInv[2]*qInv[1]-2*w*qInv[0],0},
                    {2*qInv[0]*qInv[2]-2*w*qInv[2],2*qInv[0]*qInv[1]-2*w*qInv[2],1 - 2*pow(qInv[0],2)-2*pow(qInv[1],2),0},
                    {0,0,0,1}
        };
        Mat44r pMat { {1,0,0,0},{0,1,0,0},{0,0,1,0},{-position[0],-position[1],position[2],1}};


        return pMat * qMat;
    }

    bool sees(const Vertex &v0, const Vertex &v1,const Vertex &v2) const
    {
            Vec4r e01 = v1.vert - v0.vert;
            Vec4r e02 = v2.vert - v0.vert;
            Vec4r e12 = v2.vert - v1.vert;

            Vec4r n = (e01 * e02) / (e01-e02); 
            Vec4r center = (v0.vert + v1.vert + v2.vert) / 3.0;
            if(dot(center,n) <0 )return true;
            return false;
        
    }

    Object cull(const Object &obj) const
    {
        Shape sh;
        sh.vertices = obj.get_vertices();
        for(Face f : obj.get_faces())
        {
            if(sees(obj.get_vertices()[f.v0],obj.get_vertices()[f.v1],obj.get_vertices()[f.v2]))
            {
                sh.faces.push_back(f);
            }
        }
        
        return Object(sh,obj.translation,obj.rot,obj.scale);
    }
    void update()
    {
        orientation = orientation * rot_speed *( rot_vec *sin(0.5));
        Vec3r qInv  {-orientation[0],-orientation[1],-orientation[2]};
        qInv = qInv * (1/(pow(orientation[0],2)+pow(orientation[1],2)+pow(orientation[2],2) + pow(cos(0.5),2)));
        position = position + move_speed * (Vec4r({orientation[0],orientation[1],orientation[2],0}) * move_vec *Vec4r({qInv[0],qInv[1],qInv[2],0.0}) );

    }
};





#endif