#ifndef VECTOR_H
#define VECTOR_H

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

#include <iostream>
#include <GL/gl.h>

#include <vertex.h>
#include <util/List.h>





class vector
{
    public: 
        float x[3];

        vector();
        vector(vertex2D vx);
        vector(const vertex2D *vx);
        vector(float x0, float x1, float x2);
        vector(const float *v, int args);
        vector(vector *v);



        void null();
        float len() const;
        int print() const;


        void setvalue(vertex2D vx);
        void setvalue(const vertex2D *vx);
        void setvalue(float x0);
        void setvalue(float x0, float x1);
        void setvalue(float x0, float x2, float x3);
        void setvalue(float *v, int args = 3);
        void setvalue(vector v);
        void setvalue(vector *v);


        void unify();
        vector  unifyc();
        vector *unifycp();


        void add(vertex2D vx);
        void add(vertex2D *vx);

        void add(vector  v);
        void add(vector *v);

        void add(vector  v0, vector  v1);
        void add(vector *v0, vector *v1);


        void add(vertex2D vx,  vector  v0);
        void add(vertex2D *vx, vector  v0);

        void add(vertex2D vx,  vector  *v0);
        void add(vertex2D *vx, vector  *v0);


        void add(vector  v0, vertex2D vx );
        void add(vector  v0, vertex2D *vx);

        void add(vector  *v0, vertex2D vx );
        void add(vector  *v0, vertex2D *vx);




        void add(vertex2D   *v, int args);
        void add(vertex2D  **v, int args);
        void add(vector   *v, int args);
        void add(vector  **v, int args);

         /*
            will be done when list class is fixed
            vector add(List<Vertex3D> *vlist);
            vector add(List<Vertex2D> *vlist);
            vector add(List<vector> *vlist);
        */
        void addvc(int args,...);//vector pointer
        void addvx2(int args,...);//vertex pointer


        vector  addc(vector  v);
        vector *addc(vector *v);

        vector  addc(vertex2D  v);
        vector *addc(vertex2D *v);

        vector  addc(vector  v0, vector  v1);

        vector *addc(vector   *v0, vector  *v1);

        vector *addc(vector  *v, int args);
        vector *addc(vector **v, int args);

        vector *addc(int args, ...);//vector pointer




        void sub(vector  v);
        void sub(vector *v);

        void sub(vertex2D  v);
        void sub(vertex2D *v);

        void sub(vector  v0, vector  v1);
        void sub(vector *v0, vector *v1);

        vector  subc(vector  v);
        vector *subc(vector *v);
        vector  subc(vector  v0, vector  v1);
        vector *subc(vector *v0, vector *v1);


        void scale(float s);
        void scale(float s, vector *v);
        void scale(float s, vector  v);

        vector  scalec(float s);
        vector  scalec(float s, vector v);
        vector *scalec(float s, vector *v);
        vector *scalecp(float s);

        void mul(vector v);
        void mul(vector *v);
        float largest();
        float smalest();

        void  cross(vector  v0, vector  v1);
        void  cross(vector *v0, vector *v1);
        void  cross(vector *v0, vector  v1);
        void  cross(vector  v0, vector *v1);


        vector  cross(vector   v);
        vector *cross(vector  *v);
        vector  crossc(vector  v);
        vector *crossc(vector *v);

        vector  crossc(vector  v0, vector  v1);
        vector *crossc(vector *v0, vector *v1);
        vector *crossc(vector *v0, vector  v1);
        vector *crossc(vector  v0, vector *v1);

        vector operator += (vector const v0);
        vector operator += (vector const *v0);

        vector operator -= (vector const v0);
        vector operator -= (vector const *v0);

        vector operator *= (const float s);
};

// Standart Operators
    const vector operator + (vector const v0, vector const v1);
    const vector operator + (vector const *v0, vector const v1);
    const vector operator + (vector const v1, vector const *v0);

    const vector operator - (vector const v0, vector const v1);
    const vector operator - (vector const *v0, vector const v1);
    const vector operator - (vector const v1, vector const *v0);
/*
    const vector operator ^ (vector const v0, vector const v1);
    const vector operator ^ (vector const *v0, vector const v1);
    const vector operator ^ (vector const v1, vector const *v0);
*/
    const vector operator * (vector const v0, const float s);
    const vector operator * (const float s,vector const v0);

    std::ostream& operator << (std::ostream& stream, vector const  v);
    std::ostream& operator << (std::ostream& stream, vector const *v);

    bool operator == (vector const v0,vector const v1);
    bool operator != (vector const v0,vector const v1);



float len(vector v);
vector unify(vector v);
vector *unify(vector *v);
int printv(vector v);
int printv(vector *v);


#endif
