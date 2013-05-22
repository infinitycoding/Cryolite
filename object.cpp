#include "include/object.h"


Object::Object(const char *objname)
{
    vertices = ListCreate();
    triangles = ListCreate();
    squares = ListCreate();
    texvertices = ListCreate();

    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    movement.x = 0;
    movement.y = 0;
    movement.z = 0;

    rotationAxis.x = 0;
    rotationAxis.y = 0;
    rotationAxis.z = 0;

    colorKey.red = 1.0f;
    colorKey.green = 1.0f;
    colorKey.blue = 1.0f;
    colorKey.transparency = 1.0f;

    rotationAngle = 0;

    velocity = 0;

    remaining_movement = 0;

    numofTextureSpots = 0;
    numofSpots = 0;
    numofTriangles = 0;
    numofSquares = 0;

    ObjectMaterial = Material();

    strncpy(objectname, objname, 20);
}

Object::Object(const char *filename, const char *objname)
{
    vertices = ListCreate();
    triangles = ListCreate();
    squares = ListCreate();
    texvertices = ListCreate();

    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    movement.x = 0;
    movement.y = 0;
    movement.z = 0;

    rotationAxis.x = 0;
    rotationAxis.y = 0;
    rotationAxis.z = 0;

    colorKey.red = 1.0f;
    colorKey.green = 1.0f;
    colorKey.blue = 1.0f;
    colorKey.transparency = 1.0f;

    rotationAngle = 0;

    velocity = 0;

    remaining_movement = 0;

    numofTextureSpots = 0;
    numofSpots = 0;
    numofTriangles = 0;
    numofSquares = 0;

    ObjectMaterial = Material();

    strncpy(objectname, objname, 20);

    loadObjectFile(filename, objname);
}

Object::~Object()
{
    ObjectMaterial.~Material();

    // TODO: integrate list destruction function when implemented
}

void Object::loadObjectFile(const char *objectFile, const char *objectName)
{
    FILE *f;

    f = fopen(objectFile, "r");
    if(f == NULL)
    {
        printf("Die Datei %s kann nicht geoeffnet werden.\n", objectFile);
        return;
    }



    fclose(f);
}

struct vertex3D *Object::addObjectVertex(struct vertex3D *new_vertex)
{
    numofSpots++;

    vertices = ListPushFront(vertices, new_vertex);
    return new_vertex;
}

struct vertex2D *Object::addTextureVertex(struct vertex2D *new_tex_vertex)
{
    numofTextureSpots++;

    texvertices = ListPushFront(texvertices, new_tex_vertex);
    return new_tex_vertex;
}

void Object::addTriangle(struct triangle *new_triangle)
{
    numofTriangles++;

    triangles = ListPushFront(triangles, new_triangle);
}

void Object::addSquare(struct square *new_square)
{
    numofSquares++;

    squares = ListPushFront(squares, new_square);
}

void Object::loadMaterial(const char *file)
{
    ObjectMaterial.loadTexture2D(file);
}


