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


class ObjectType : public BasicParser
{
    public:
        ObjectType();
        ObjectType(const char *filename, const char *objname);
        ~ObjectType();

        void initObjectType();


        void loadObjectTypeFile(const char *objectFile, const char *objectName);

        struct vertexNumber countVertices(const char *filename, const char *objectname);
        usedVertices verticesInPolygon(char *line);



        char objectTypeName[20];

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
        Material *ObjectTypeMaterial;

        bool isPhysicalActor;
};

class ObjectTypeCache
{
    public:
        ObjectTypeCache();
        ~ObjectTypeCache();

        ObjectType *requestObjectType(const char *filename, const char *objtypename);
        ObjectType *searchObjectType(const char *objtypename);
        bool unloadObjectType(const char *objtypename);


    protected:
        List<ObjectType> *cachedObjectTypes;
};

class Object
{
    public:

        Object();
        Object(const char *filename, const char *objname);
        Object(const char *filename, const char *objname, vector pos);
        ~Object();

        void initObject();



        void moveObject(float a, vector D,float v = 0);
        void rotateObject(float angle,float v,float a,vector rotationAxis);



        ObjectType *objType;
        static ObjectTypeCache *ObjTypeCache;

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
};






#endif
