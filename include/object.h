#ifndef OBJECT_H
#define OBJECT_H


#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include <types.h>
#include <material.h>
#include <List.h>
#include <vector.h>



enum usedVertices
{
    nothing_used, texture_used, normals_used, all_used
};

struct triangle
{
    vertex3D *objVertex[3];
    vertex3D *normVertex[3];
    vertex2D *texVertex[3];
};

struct square
{
    vertex3D *objVertex[4];
    vertex3D *normVertex[4];
    vertex2D *texVertex[4];
};

struct numofvertices
{
    int objectVertices;
    int textureVertices;
    int normalVertices;
};

class Object
{
    public:

        Object(const char *objname);
        Object(const char *filename, const char *objname);
        ~Object();


        vertex3D *addObjectVertex(vertex3D *new_vertex);
        vertex3D *addNormalVertex(vertex3D *new_norm_vertex);
        vertex2D *addTextureVertex(vertex2D *new_tex_vertex);
        void addTriangle(struct triangle *new_triangle);
        void addSquare(struct square *new_square);

        void loadMaterial(const char *file);
        void loadObjectFile(const char *objectFile, const char *objectName);

        void moveObject(float v,float a , float l, dvector3D D);
        void rotateObject(float angle,float v,float a,dvector3D rotationAxis);


        char objectname[20];

        vertex3D scale;
        vector3D position;

        vector3D rotationAxis;
        GLfloat Angle;
        GLfloat remeaningAngle;
        GLfloat destAngle;
        float rotationVelocity;
        float rotationAcceleration;
        int startRotationTime;
        int remAngleSing;


        vector3D Dm; // Direction Motion
        vector3D Pmd; // Position motion destination
        float Lmr; // Distance Motion Remeaning
        float Vm; // Velocity Motion
        float Am; // Acceleration Motion
        int Tms; //Time Motion Start

        List<vertex3D> *vertices;
        List<vertex3D> *normvertices;
        List<vertex2D> *texvertices;
        List<struct triangle> *triangles;
        List<struct square> *squares;
        Material *ObjectMaterial;

        bool isPhysicalActor;
        bool automatical_texturing;

    private:

        void initObject();
        struct numofvertices countVertices(const char *filename, const char *objectname);
        usedVertices vertices_in_polygone(char *line);
};






#endif
