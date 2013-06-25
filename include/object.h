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
    unsigned int smoothingGroup;
};

struct square
{
    vertex3D *objVertex[4];
    vertex3D *normVertex[4];
    vertex2D *texVertex[4];
    unsigned int smoothingGroup;
};

struct numofvertices
{
    int objectVertices;
    int textureVertices;
    int normalVertices;
};

struct boundBox
{
    vertex3D base;
    vector height;
    vector widht;
    vector length;
};

struct boundSphere
{
    vertex3D center;
    GLfloat radian;
};

struct boundPlane
{
    vertex3D base;
    vector widht;
    vector length;
};

struct boundTriangel
{
    vertex3D vert0;
    vertex3D vert1;
    vertex3D vert2;
};

struct boundCylinder
{
    vertex3D center;
    GLfloat radian;
    GLfloat height;
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

        void moveObject(float a, vector D,float v = 0);
        void rotateObject(float angle,float v,float a,vector rotationAxis);




        char objectname[20];

        vector scale;
        vector position;

        vector rotationAxis;
        GLfloat Angle;
        GLfloat remeaningAngle;
        GLfloat destAngle;
        float rotationVelocity;
        float rotationAcceleration;
        int startRotationTime;
        int remAngleSing;


        vector Dm; // Direction Motion
        float V0m; // Velocity Motion
        float Am; // Acceleration Motion
        int Tms; //Time Motion Start

        List<vertex3D> *vertices;
        List<vertex3D> *normvertices;
        List<vertex2D> *texvertices;
        List<struct triangle> *triangles;
        List<struct square> *squares;

        // Bounds
        List<struct boundBox> *boundBoxes;
        List<struct boundSphere> *boundSpheres;
        List<struct boundPlane> *boundPlanes;
        List<struct boundCylinder> *boundCylinders;
        List<struct boundTriangel> *boundTriangles;

        Material *ObjectMaterial;

        bool isPhysicalActor;
        bool automatical_texturing;

    private:

        void initObject();
        struct numofvertices countVertices(const char *filename, const char *objectname);
        usedVertices vertices_in_polygone(char *line);
};






#endif
