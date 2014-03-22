#ifndef OBJECT_H
#define OBJECT_H



/****************************************
 *                                      *
 *  Object-Module                       *
 *  -------------                       *
 *                                      *
 *  Author: Peter Hösch                 *
 *                                      *
 ****************************************/


// own headers
#include <material.h>       // objects have materials, don't they?
#include <polygon.h>        // objects have polygone, don't they?
#include <sound.h>          // objects have sound, don't they?
#include <physics/boundobjects.h>   // objects have bound objects, don't they?
#include <physics/PhysicsEngine.h>  // objects have physics, don't  they?



enum usedVertices       // enumberation which says if a vertex has a texture coordinate and/or a normal vector too
{
    nothingUsed, textureUsed, normalsUsed, allUsed
};


struct vertexNumber     // a struct which shows the number of object vertices, texture vertices and normal vectors in an object
{
    int objectVertices;
    int textureVertices;
    int normalVectors;
};


struct rotation
{
    GLfloat Angle;
    vector rotationAxis;
};



class ObjectType : public ExtParser   // The object type class
{
    public:
        ObjectType();                                               // zero constructor (better than nothing)
        ObjectType(const char *filename, const char *objname);    // standart constructor
        ~ObjectType();                                              // destructor

        void initObjectType();                                      // init functions, so i don't have to write the things in every constructor


        void loadObjectTypeFile(const char *objectFile, const char *objectName);       // the wavefront parser function

        vertexNumber countVertices(const char *filename, const char *objectname);       // function which counts the vertices, texvertices and normvectors in an object (used by loadObjectTypeFile)
        usedVertices verticesInPolygon(char *line);                                       // function which loooks which types of vertices are in a polygon (used by loadObjectTypeFile)



        char objectTypeName[20];                // the name of the object type

        List<Vertex3D> *vertices;               // the list of vertices of the object type
        List<vector> *normvectors;              // the list of normvectors of the object type
        List<Vertex2D> *texvertices;            // the list of texture vertices of the object type

        List<Polygon> *polygones;               // the list of polygones of the object type

        // Bounds object lists
        List<boundBox> *boundBoxes;             // the list of bound boxes of the object type
        List<boundSphere> *boundSpheres;        // the list of bound spheres of the object type
        List<boundPlane> *boundPlanes;          // the list of bound planes of the object type

        static MaterialCache *MatCache;         // the static material cache (you know what a cache is, don't you?)
        Material *ObjectTypeMaterial;            // the material of this object type

        bool isPhysicalActor;                   // says if there are physical reactions on this object type
};



class ObjectTypeCache       // the cache for object types
{
    public:
        ObjectTypeCache();  // constructor
        ~ObjectTypeCache(); // destructor

        ObjectType *requestObjectType(const char *filename, const char *objtypename);   // the request function to get a object type from cache
        ObjectType *searchObjectType(const char *objtypename);                            // intern function which finds an object type in the list
        bool unloadObjectType(const char *objtypename);                                  // function to unload an object type


    protected:
        List<ObjectType> *cachedObjectTypes;    // the list of cached object types
};



class Object                // the main object
{
    public:

        Object();                                                           // zero-constructor, don't use!
        Object(const char *filename, const char *objname);               // don't know why somebody should want to do this, but he can!
        Object(const char *filename, const char *objname, vector pos);   // standart constructor
        ~Object();                                                          // destructor

        vector getPosition();


        ObjectType *objType;                         // the object type
        static ObjectTypeCache *ObjTypeCache;       // the static object type cache (you know what a cache is, don't you?)

        vector scale;                               // the scale of the object (if you need an overdimensional cup of tea)

        rotation rot;

        Object *relativeToObject;
        vector localPosition;                    // the position

        List<Sound> *sounds;                    // the list of sounds connected to this object


        PhysicalObject *physObj;

        float approximationSphere;

    protected:
        void initObject();       // init functions, so i don't have to write the things in every constructor
};






#endif
