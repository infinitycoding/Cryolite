#ifndef POLYGONE_H_INCLUDED
#define POLYGONE_H_INCLUDED



/********************************************
 * Polygone-Module                          *
 * ---------------                          *
 *                                          *
 * Contains the polygone-class:             *
 * Able to create infinite sized polygones  *
 *                                          *
 * created by Peter Hösch                   *
 ********************************************/



#include <iostream>
#include <cstdlib>

#include <vector.h>
#include <vertex.h>


using namespace std;



class Polygone
{
    public:
        Polygone();                     // a backward compatibility constructor - don't use it
        Polygone(int numOfVertices);    // the constructor
        virtual ~Polygone();            // the destructor

        int getVertexAmount();  // The get-method of vertex amount

        vector   *getNormVector(int number);     // the get-method of normal vector
        vertex3D *getObjVertex(int number);      // the get-method of object vertex
        vertex2D *getTexVertex(int number);      // the get-method of texture vertex

        void setNormVector(int number, vector *value); // the set-method of normal vector
        void setObjVertex(int number, vertex3D *value);  // the set-method of object vertex
        void setTexVertex(int number, vertex2D *value);  // the set-method of texture vertex


    protected:
        int vertexAmount;           // of how many vertices the polygone consists
                                    // a polygone has...
        vector   **normVector;      // ... normal vectors (to simulate light reflection)
        vertex3D **objVertex;       // ... object vertices (makes sense, doesn't it?)
        vertex2D **texVertex;       // ... texture vertices (to know which part of the texture should be put where)
};



#endif
