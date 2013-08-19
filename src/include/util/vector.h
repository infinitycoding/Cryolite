#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

#include <GL/gl.h>

#include <vertex.h>
#include <List.h>


#define STD_VECTOR_DIMENSIONS 3




class vector
{
    public:

        float x;
        float y;
        float z;


        vector();
        vector(Vertex2D vx);
        vector(Vertex3D vx);
        vector(Vertex2D *vx);
        vector(Vertex3D *vx);
        vector(float x);
        vector(float x, float y);
        vector(float x, float y, float z);
        vector(float *v, int args = 3);
        vector(vector *v);



        void null();
        float len();
        int print();


        void setvalue(Vertex2D vx);
        void setvalue(Vertex3D vx);
        void setvalue(Vertex2D *vx);
        void setvalue(Vertex3D *vx);
        void setvalue(float x);
        void setvalue(float x, float y);
        void setvalue(float x, float y, float z);
        void setvalue(float *v, int args = 3);
        void setvalue(vector v);
        void setvalue(vector *v);


        void unify();
        vector  unifyc();
        vector *unifycp();


        void add(Vertex2D vx);
        void add(Vertex2D *vx);
        void add(Vertex3D vx);
        void add(Vertex3D *vx);

        void add(vector  v);
        void add(vector *v);

        void add(vector  v0, vector  v1);
        void add(vector *v0, vector *v1);


        void add(Vertex2D vx,  vector  v0);
        void add(Vertex2D *vx, vector  v0);
        void add(Vertex3D vx,  vector  v0);
        void add(Vertex3D *vx, vector  v0);

        void add(Vertex2D vx,  vector  *v0);
        void add(Vertex2D *vx, vector  *v0);
        void add(Vertex3D vx,  vector  *v0);
        void add(Vertex3D *vx, vector  *v0);


        void add(vector  v0, Vertex2D vx );
        void add(vector  v0, Vertex2D *vx);
        void add(vector  v0, Vertex3D vx );
        void add(vector  v0, Vertex3D *vx);

        void add(vector  *v0, Vertex2D vx );
        void add(vector  *v0, Vertex2D *vx);
        void add(vector  *v0, Vertex3D vx );
        void add(vector  *v0, Vertex3D *vx);




        void add(Vertex3D   *v, int args);
        void add(Vertex3D  **v, int args);
        void add(Vertex2D   *v, int args);
        void add(Vertex2D  **v, int args);
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
        void addvx3(int args,...);//vertex pointer


        vector  addc(vector  v);
        vector *addc(vector *v);

        vector  addc(Vertex3D  v);
        vector *addc(Vertex3D *v);

        vector  addc(Vertex2D  v);
        vector *addc(Vertex2D *v);

        vector  addc(vector  v0, vector  v1);

        vector  addc(Vertex3D  v0, vector  v1);
        vector  addc(vector  v1, Vertex3D  v0);

        vector *addc(vector   *v0, vector  *v1);
        vector *addc(Vertex3D  *v0, vector  *v1);

        vector *addc(vector   *v1, Vertex3D *v0);

        vector *addc(vector  *v, int args);
        vector *addc(vector **v, int args);

        vector *addc(int args, ...);//vector pointer




        void sub(vector  v);
        void sub(vector *v);

        void sub(Vertex2D  v);
        void sub(Vertex2D *v);

        void sub(Vertex3D  v);
        void sub(Vertex3D *v);

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


        bool lenmod;
        float cachlen;

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

    const vector operator ^ (vector const v0, vector const v1);
    const vector operator ^ (vector const *v0, vector const v1);
    const vector operator ^ (vector const v1, vector const *v0);

    const vector operator * (vector const v0, const float s);
    const vector operator * (const float s,vector const v0);

    std::ostream& operator << (std::ostream& stream, vector const  v);
    std::ostream& operator << (std::ostream& stream, vector const *v);



float len(vector v);
vector unify(vector v);
vector *unify(vector *v);
int printv(vector v);
int printv(vector *v);


#endif
