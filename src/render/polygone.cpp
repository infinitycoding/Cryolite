#include <polygone.h>



Polygone::Polygone()
{
    vertexAmount = 4;   // i want to know the vertex amout late

    normVector = new vector*[4];    // create the normal vector pointers
    objVertex = new vertex3D*[4];   // create the object vertex pointers
    texVertex = new vertex2D*[4];   // create the texture vertex pointers

    for(int i = 0; i < 4; i++)      // initialize the pointers (so you can see if it it valid or not)
    {
        normVector[i] = NULL;
        objVertex[i] = NULL;
        texVertex[i] = NULL;
    }
}


// The standart constructor.
// Just say how big the polygone should be.

Polygone::Polygone(int numOfVertices)
{
    if(numOfVertices >= 3)      // have you ever seen a polygone with less than three vertices?
    {
        vertexAmount = numOfVertices;   // i want to know the vertex amout late

        normVector = new vector*[numOfVertices];    // create the normal vector pointers
        objVertex = new vertex3D*[numOfVertices];   // create the object vertex pointers
        texVertex = new vertex2D*[numOfVertices];   // create the texture vertex pointers

        for(int i = 0; i < numOfVertices; i++)      // initialize the pointers (so you can see if it it valid or not)
        {
            normVector[i] = NULL;
            objVertex[i] = NULL;
            texVertex[i] = NULL;
        }
    }
    else
    {
        cerr << "Error: Tryed to create a polygone with " << numOfVertices << " vertices." << endl;
        exit(-1);
    }
}


// The destructor.
// Deletes the vertex and vector pointers.

Polygone::~Polygone()
{
    delete[] normVector;
    delete[] objVertex;
    delete[] texVertex;
}


// The get-method of vertex amount.

int Polygone::getVertexAmount()
{
    return vertexAmount;
}


// the set-method of normal vector.

void Polygone::setNormVector(int number, vector *value)
{
    normVector[number] = value;
}


// the set-method of object vertex.

void Polygone::setObjVertex(int number, vertex3D *value)
{
    objVertex[number] = value;
}


// the set-method of texture vertex.

void Polygone::setTexVertex(int number, vertex2D *value)
{
    texVertex[number] = value;
}


// the get-method of normal vector.

vector *Polygone::getNormVector(int number)
{
    return normVector[number];
}


// the get-method of object vertex.

vertex3D *Polygone::getObjVertex(int number)
{
    return objVertex[number];
}


// the get-method of texture vertex.

vertex2D *Polygone::getTexVertex(int number)
{
    return texVertex[number];
}

