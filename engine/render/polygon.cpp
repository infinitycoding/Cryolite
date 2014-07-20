/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */
     
#include <polygon.h>



// The standart constructor.
// Just say how big the polygon should be.

Polygon::Polygon(int numOfVertices)
{
    if(numOfVertices >= 3)      // have you ever seen a polygon with less than three vertices?
    {
        vertexAmount = numOfVertices;   // i want to know the vertex amout late

        normVector = new vector*[numOfVertices];    // create the normal vector pointers
        objVertex = new vector*[numOfVertices];   // create the object vertex pointers
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

void Polygon::setObjVertex(int number, vector *value)
{
    objVertex[number] = value;
}


// the set-method of texture vertex.

void Polygon::setTexVertex(int number, vertex2D *value)
{
    texVertex[number] = value;
}


// the get-method of normal vector.

vector *Polygon::getNormVector(int number)
{
    return normVector[number];
}


// the get-method of object vertex.

vector *Polygon::getObjVertex(int number)
{
    return objVertex[number];
}


// the get-method of texture vertex.

vertex2D *Polygon::getTexVertex(int number)
{
    return texVertex[number];
}

