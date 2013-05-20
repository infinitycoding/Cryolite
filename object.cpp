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
    // TODO: write this function
}

void Object::addVertices(struct vertex3D *new_vertex)
{
    numofSpots++;

    vertices = ListSetLast(vertices);
    vertices = ListInsertAfter(vertices, new_vertex);
}

void Object::addTriangle(struct triangle *new_triangle)
{
    numofTriangles++;

    triangles = ListSetLast(triangles);
    triangles = ListInsertAfter(triangles, new_triangle);
}

void Object::addSquare(struct square *new_square)
{
    numofSquares++;

    squares = ListSetLast(squares);
    squares = ListInsertAfter(squares, new_square);
}

void Object::loadMaterial(const char *file)
{
    ObjectMaterial = Material(file);
}
