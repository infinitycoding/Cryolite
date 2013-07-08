#include <polygon.h>



Polygon::Polygon()
{
    vertexAmount = 4;   // i want to know the vertex amout late

    normVector = new vector*[4];    // create the normal vector pointers
    objVertex = new Vertex3D*[4];   // create the object vertex pointers
    texVertex = new Vertex2D*[4];   // create the texture vertex pointers

    for(int i = 0; i < 4; i++)      // initialize the pointers (so you can see if it it valid or not)
    {
        normVector[i] = NULL;
        objVertex[i] = NULL;
        texVertex[i] = NULL;
    }
}


// The standart constructor.
// Just say how big the polygon should be.

Polygon::Polygon(int numOfVertices)
{
    if(numOfVertices >= 3)      // have you ever seen a polygon with less than three vertices?
    {
        vertexAmount = numOfVertices;   // i want to know the vertex amout late

        normVector = new vector*[numOfVertices];    // create the normal vector pointers
        objVertex = new Vertex3D*[numOfVertices];   // create the object vertex pointers
        texVertex = new Vertex2D*[numOfVertices];   // create the texture vertex pointers

        for(int i = 0; i < numOfVertices; i++)      // initialize the pointers (so you can see if it it valid or not)
        {
            normVector[i] = NULL;
            objVertex[i] = NULL;
            texVertex[i] = NULL;
        }
    }
    else
    {
        cerr << "Error: Tryed to create a polygon with " << numOfVertices << " vertices." << endl;
        exit(-1);
    }
}


// The destructor.
// Deletes the vertex and vector pointers.

Polygon::~Polygon()
{
    delete[] normVector;
    delete[] objVertex;
    delete[] texVertex;
}


// The get-method of vertex amount.

int Polygon::getVertexAmount()
{
    return vertexAmount;
}


// the set-method of normal vector.

void Polygon::setNormVector(int number, vector *value)
{
    normVector[number] = value;
}


// the set-method of object vertex.

void Polygon::setObjVertex(int number, Vertex3D *value)
{
    objVertex[number] = value;
}


// the set-method of texture vertex.

void Polygon::setTexVertex(int number, Vertex2D *value)
{
    texVertex[number] = value;
}


// the get-method of normal vector.

vector *Polygon::getNormVector(int number)
{
    return normVector[number];
}


// the get-method of object vertex.

Vertex3D *Polygon::getObjVertex(int number)
{
    return objVertex[number];
}


// the get-method of texture vertex.

Vertex2D *Polygon::getTexVertex(int number)
{
    return texVertex[number];
}

