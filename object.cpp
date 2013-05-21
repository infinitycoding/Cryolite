#include "include/object.h"


Object::Object()
{
    vertices = ListCreate();
    triangles = ListCreate();
    squares = ListCreate();
}

Object::Object(const char *filename)
{
    vertices = ListCreate();
    triangles = ListCreate();
    squares = ListCreate();

    loadObjectFile(filename);
}

Object::~Object()
{
    ObjectMaterial.~Material();

    // TODO: integrate list destruction function when implemented
}

void Object::loadObjectFile(const char *objectFile)
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

void Object::addObjectVertex(struct vertex3D *new_vertex)
{
    numofSpots++;

    vertices = ListPushFront(vertices, new_vertex);
}

void Object::addTextureVertex(struct vertex2D *new_tex_vertex)
{
    numofTextureSpots++;

    texvertices = ListPushFront(texvertices, new_tex_vertex);
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
    ObjectMaterial = Material(file);
}
