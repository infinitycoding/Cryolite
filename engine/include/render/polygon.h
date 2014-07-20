#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED
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

#include <util/vector.h>


using namespace std;



class Polygon
{
    public:
        Polygon(int numOfVertices);    // the constructor
        virtual ~Polygon();            // the destructor

        int getVertexAmount();  // The get-method of vertex amount

        vector   *getNormVector(int number);     // the get-method of normal vector
        vector *getObjVertex(int number);      // the get-method of object vertex
        vertex2D *getTexVertex(int number);      // the get-method of texture vertex

        void setNormVector(int number, vector *value); // the set-method of normal vector
        void setObjVertex(int number, vector *value);  // the set-method of object vertex
        void setTexVertex(int number, vertex2D *value);  // the set-method of texture vertex


    protected:
        int vertexAmount;           // of how many vertices the polygon consists
                                    // a polygon has...
        vector   **normVector;      // ... normal vectors (to simulate light reflection)
        vector **objVertex;       // ... object vertices (makes sense, doesn't it?)
        vertex2D **texVertex;       // ... texture vertices (to know which part of the texture should be put where)
};



#endif
