#ifndef VECTOR_H
#define VECTOR_H


#include <GL/gl.h>



#define STD_VECTOR_DIMENSIONS 3




class vector
{
    public:

        float elements[3];


        vector();
        vector(float x);
        vector(float x, float y);
        vector(float x, float y, float z);
        vector(float *v, int args = 3);
        vector(vector *v);



        void null();
        float len();



        void setvalue(float x);
        void setvalue(float x, float y);
        void setvalue(float x, float y, float z);
        void setvalue(float *v, int args = 3);
        void setvalue(vector v);
        void setvalue(vector *v);



        void unify();
        vector  unifyc();
        vector *unifycp();




        void add(vector  v);
        void add(vector *v);

        void add(vector  v0, vector  v1);
        void add(vector *v0, vector *v1);

        void add(vector   *v, int args);
        void add(vector  **v, int args);

        void add(int args,...);//nur pointer

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
};
        const vector operator + (vector const v0, vector const v1);
        const vector operator + (vector const *v0, vector const v1);
        const vector operator - (vector const v0, vector const v1);
        const vector operator - (vector const *v0, vector const v1);
        const vector operator * (vector const v0, const float s);



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
