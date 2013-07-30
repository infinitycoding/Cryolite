#ifndef OBJECT_H
#define OBJECT_H



#include <material.h>   // own headers
#include <vector.h>
#include <polygon.h>
#include <parser.h>



enum usedVertices       // enumberation which says if a vertex has a texture coordinate and/or a normal vector too
{
    nothingUsed = 0, textureUsed = 1, normalsUsed = 2, allUsed = 3
};

struct vertexNumber     // a struct which shows the number of object vertices, texture vertices and normal vectors in an object
{
    int objectVertices;
    int textureVertices;
    int normalVectors;
};

struct boundBox         // many structs are following here, all defining bound objects
{
    Vertex3D base;
    vector height;
    vector widht;
    vector length;
};

struct boundSphere
{
    Vertex3D center;
    GLfloat radian;
};

struct boundPlane
{
    Vertex3D base;
    vector widht;
    vector length;
};

struct boundTriangel
{
    Vertex3D vert0;
    Vertex3D vert1;
    Vertex3D vert2;
};

struct boundCylinder
{
    Vertex3D center;
    GLfloat radian;
    GLfloat height;
};

class Object : public BasicParser
{
    public:

        Object();                                                                  // zero-constructor. for self-created objects.
        Object(const char *filename, const char *objname);                      // template-constructor. for templates.
        Object(const char *filename, const char *objname, vector pos);          // direct-constrocter. for unique objects.
        ~Object();

        void initObject();


        Vertex3D *addObjectVertex(Vertex3D *newVertex);         // functions to add new members to the lists
        vector *addNormalVector(vector *newNormVector);
        Vertex2D *addTextureVertex(Vertex2D *newTexVertex);
        Polygon *addPolygon(Polygon *newPolygon);

        void loadMaterial(const char *file, const char *matname);
        void loadObjectFile(const char *objectFile, const char *objectName);

        struct vertexNumber countVertices(const char *filename, const char *objectname);
        usedVertices verticesInPolygon(char *line);

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

        List<Vertex3D> *vertices;
        List<vector> *normvectors;
        List<Vertex2D> *texvertices;
        List<Polygon> *polygones;

        // Bounds
        List<struct boundBox> *boundBoxes;
        List<struct boundSphere> *boundSpheres;
        List<struct boundPlane> *boundPlanes;
        List<struct boundCylinder> *boundCylinders;
        List<struct boundTriangel> *boundTriangles;

        static MaterialCache *MatCache;
        Material *ObjectMaterial;

        bool isPhysicalActor;
};






#endif
