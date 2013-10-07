#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED



/********************************************
 * Polygon-Module                          *
 * ---------------                          *
 *                                          *
 * Contains the polygon-class:             *
 * Able to create infinite sized polygons  *
 *                                          *
 * created by Peter Hösch                   *
 ********************************************/



#include <iostream>
#include <cstdlib>

#include <vector.h>
#include <vertex.h>


using namespace std;



class Polygon
{
    public:
        Polygon(int numOfVertices);    // the constructor
        virtual ~Polygon();            // the destructor

        int getVertexAmount();  // The get-method of vertex amount

        vector   *getNormVector(int number);     // the get-method of normal vector
        Vertex3D *getObjVertex(int number);      // the get-method of object vertex
        Vertex2D *getTexVertex(int number);      // the get-method of texture vertex

        void setNormVector(int number, vector *value); // the set-method of normal vector
        void setObjVertex(int number, Vertex3D *value);  // the set-method of object vertex
        void setTexVertex(int number, Vertex2D *value);  // the set-method of texture vertex


    protected:
        int vertexAmount;           // of how many vertices the polygon consists
                                    // a polygon has...
        vector   **normVector;      // ... normal vectors (to simulate light reflection)
        Vertex3D **objVertex;       // ... object vertices (makes sense, doesn't it?)
        Vertex2D **texVertex;       // ... texture vertices (to know which part of the texture should be put where)
};



#endif
