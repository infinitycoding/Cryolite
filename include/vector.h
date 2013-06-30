#ifndef VECTOR_H
#define VECTOR_H


#include <GL/gl.h>
#include <types.h>
#include <iostream>
#include <ostream>
#include <List.h>


#define STD_VECTOR_DIMENSIONS 3




class vector
{
    public:

        float elements[3];


        vector();
        vector(vertex2D vx);
        vector(vertex3D vx);
        vector(vertex2D *vx);
        vector(vertex3D *vx);
        vector(float x);
        vector(float x, float y);
        vector(float x, float y, float z);
        vector(float *v, int args = 3);
        vector(vector *v);



        void null();
        float len();
        int print();


        void setvalue(vertex2D vx);
        void setvalue(vertex3D vx);
        void setvalue(vertex2D *vx);
        void setvalue(vertex3D *vx);
        void setvalue(float x);
        void setvalue(float x, float y);
        void setvalue(float x, float y, float z);
        void setvalue(float *v, int args = 3);
        void setvalue(vector v);
        void setvalue(vector *v);


        void unify();
        vector  unifyc();
        vector *unifycp();


        void add(vertex2D vx);
        void add(vertex2D *vx);
        void add(vertex3D vx);
        void add(vertex3D *vx);

        void add(vector  v);
        void add(vector *v);

        void add(vector  v0, vector  v1);
        void add(vector *v0, vector *v1);


        void add(vertex2D vx,  vector  v0);
        void add(vertex2D *vx, vector  v0);
        void add(vertex3D vx,  vector  v0);
        void add(vertex3D *vx, vector  v0);

        void add(vertex2D vx,  vector  *v0);
        void add(vertex2D *vx, vector  *v0);
        void add(vertex3D vx,  vector  *v0);
        void add(vertex3D *vx, vector  *v0);


        void add(vector  v0, vertex2D vx );
        void add(vector  v0, vertex2D *vx);
        void add(vector  v0, vertex3D vx );
        void add(vector  v0, vertex3D *vx);

        void add(vector  *v0, vertex2D vx );
        void add(vector  *v0, vertex2D *vx);
        void add(vector  *v0, vertex3D vx );
        void add(vector  *v0, vertex3D *vx);
        //done until here



        void add(vertex3D   *v, int args);
        void add(vertex3D  **v, int args);
        void add(vertex2D   *v, int args);
        void add(vertex2D  **v, int args);
        void add(vector   *v, int args);
        void add(vector  **v, int args);

        vector add(List<vertex3D> *vlist);
        vector add(List<vertex2D> *vlist);

        void addvc(int args,...);//vector pointer
        void addvx2(int args,...);//vertex pointer
        void addvx3(int args,...);//vertex pointer




        vector  addc(vertex3D  v);
        vector *addc(vertex3D *v);

        vector  addc(vertex2D  v);
        vector *addc(vertex2D *v);

        vector  addc(vector  v);
        vector *addc(vector *v);

        vector  addc(vector  v0, vector  v1);
        vector *addc(vector *v0, vector *v1);

        vector *addc(vector  *v, int args);
        vector *addc(vector **v, int args);

        vector *addc(int args, ...);//nur pointer




        void sub(vector  v);
        void sub(vector *v);

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


    const vector operator * (vector const v0, const float s);
    const vector operator * (const float s,vector const v0);

    std::ostream& operator << (std::ostream& stream, vector const  v);
    std::ostream& operator << (std::ostream& stream, vector const *v);



float len(vector v);
vector unify(vector v);
vector *unify(vector *v);
int printv(vector v);
int printv(vector *v);

class vectorN
{
    public:

        float *elements;
        int dim;


        vectorN();
        vectorN(float x);
        vectorN(float x, float y);
        vectorN(float x, float y, float z);
        vectorN(int args,...); //only floats
        vectorN(float *v, int args);
        vectorN(vectorN *v);

        ~vectorN();


        void null();
        float len();

    //tdodo
        void addDim(int dim);
        void remDim(int dim);
        void maxDim(int dim);
    // todoend


        void setvalue(float x);
        void setvalue(float x, float y);
        void setvalue(float x, float y, float z);
        void setvalue(int args, ...);
        void setvalue(int args, float *v);
        void setvalue(vectorN v);
        void setvalue(vectorN *v);



        void unify();
        vectorN *unifycp();
        vectorN  unifyc();

        void add(vectorN  v);
        void add(vectorN *v);

        void add(vectorN  v0, vectorN  v1);
        void add(vectorN *v0, vectorN *v1);

        void add(int args, vectorN   *v);
        void add(int args, vectorN **v);

        void add(int args, ...);//nur pointer

        vectorN  addc(vectorN  v);
        vectorN *addc(vectorN *v);

        vectorN  addc(vectorN  v0, vectorN  v1);
        vectorN *addc(vectorN *v0, vectorN *v1);

        vectorN *addc(int args, vectorN  *v);
        vectorN *addc(int args, vectorN **v);

        vectorN *addc(int args, ...);//nur pinter



        void sub(vectorN  v);
        void sub(vectorN *v);

        void sub(vectorN  v0, vectorN  v1);
        void sub(vectorN *v0, vectorN *v1);

        vectorN  subc(vectorN  v);
        vectorN *subc(vectorN *v);
        vectorN  subc(vectorN  v0, vectorN  v1);
        vectorN *subc(vectorN *v0, vectorN *v1);




        void scale(float s);
        void scale(float s, vectorN *v);
        void scale(float s, vectorN  v);

        vectorN  scalec(float s);
        vectorN  scalec(float s, vectorN v);
        vectorN *scalec(float s, vectorN *v);

        vectorN *scalecp(float s);


        static vectorN *unifysp();
        static vectorN  unifys();

        static vectorN  adds(vectorN  v);
        static vectorN *adds(vectorN *v);

        static vectorN  adds(vectorN  v0, vectorN  v1);
        static vectorN *adds(vectorN *v0, vectorN *v1);

        static vectorN *adds(int args, vectorN   *v);
        static vectorN *adds(int args, vectorN **v1);

        static vectorN *adds(int args, ...);// nur pointer


        static vectorN  subs(vectorN  v);
        static vectorN *subs(vectorN *v);
        static vectorN  subs(vectorN  v0, vectorN  v1);
        static vectorN *subs(vectorN *v0, vectorN *v1);

        static vectorN  scales(float s);
        static vectorN  scales(float s, vectorN v);
        static vectorN *scales(float s, vectorN *v);

        static vectorN *scalesp(float s);

        private:
            bool lenmod;
            float cachlen;
};

#endif
