#include <math.h>
#include <vector.h>
#include <cstdarg>
#include <stdio.h>

vector::vector()
{
    cachlen = 0;
    lenmod = true;
    n = STD_VECTOR_DIMENSIONS;
    x = new float[STD_VECTOR_DIMENSIONS];
    for(int i = 0; i < STD_VECTOR_DIMENSIONS; i++)
        x[i] = 0.0;
}

vector::vector(Vertex2D vx, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];

    x[0] = vx.getX();
    x[1] = vx.getY();

    if(dim > 2)
    {
        for(int i = 2; i < dim; i++)
            x[i] = 0;
    }
}

vector::vector(Vertex2D *vx, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];

    x[0] = vx->getX();
    x[1] = vx->getY();

    if(dim > 2)
    {
        for(int i = 2; i < dim; i++)
            x[i] = 0;
    }
}

vector::vector(Vertex3D vx, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];

    x[0] = vx.getX();
    x[1] = vx.getY();
    x[2] = vx.getZ();

    if(dim > 3)
    {
        for(int i = 3; i < dim; i++)
            x[i] = 0;
    }
}

vector::vector(Vertex3D *vx, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];

    x[0] = vx->getX();
    x[1] = vx->getY();
    x[2] = vx->getZ();

    if(dim > 3)
    {
        for(int i = 3; i < dim; i++)
            x[i] = 0;
    }
}


vector::vector(float x0, float x1, float x2, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];

    x[0] = x0;
    x[1] = x1;
    x[2] = x2;

    if(dim > 3)
    {
        for(int i = 3; i < dim; i++)
            x[i] = 0;
    }
}

/*vector::vector(float *v,int args = 3, int dim)
{
    cachlen = 0;
    lenmod = false;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];
    int i;
    for(i = 0; i < args; i++)
        x[i] = v[i];

    if(dim > args)
    {
        for(; i < dim; i++)
            x[i] = 0;
    }
}*/


vector::vector(vector *v, int dim)
{
    cachlen = 0;
    lenmod = true;
    n = dim;
    dim = dim < STD_VECTOR_DIMENSIONS ? STD_VECTOR_DIMENSIONS : dim;
    x = new float[dim];
    int i;
    for(i = 0; i < dim && i < v->n; i++)
        x[i] = v->x[i];

    if(dim > v->n)
    {
        for(; i < dim; i++)
            x[i] = 0;
    }
}

void vector::null()
{
    cachlen = 0;
    lenmod = false;
    for(int i = 0; i < n; i++)
    {
        x[i] = 0;
    }

}

float vector::len()
{
    if(lenmod)
    {
        float temp = 0;
        for (int i = 0; i < n; i++)
            temp += x[i]*x[i];
        cachlen = sqrt(temp);
        lenmod = false;
    }
    return cachlen;
}

int vector::print()
{
    int num = 0;
    for(int i = 0; i < n; i++)
        num += printf("X%d:%f ",i,x[i]);
    printf("\n");
    return num;
}

void vector::setvalue(Vertex2D vx)
{
    x[0] = vx.getX();
    x[1] = vx.getY();
    lenmod = true;
}

void vector::setvalue(Vertex2D *vx)
{
    x[0] = vx->getX();
    x[1] = vx->getY();
    lenmod = true;
}

void vector::setvalue(Vertex3D vx)
{
    x[0] = vx.getX();
    x[1] = vx.getY();
    x[2] = vx.getZ();
    lenmod = true;
}

void vector::setvalue(Vertex3D *vx)
{
    x[0] = vx->getX();
    x[1] = vx->getY();
    x[2] = vx->getZ();
    lenmod = true;
}

void vector::setvalue(float x0)
{
    x[0] = x0;
    lenmod = true;
}

void vector::setvalue(float x0, float x1)
{
    x[0] = x0;
    x[1] = x1;
    lenmod = true;
}

void vector::setvalue(float x0, float x1, float x2)
{
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
    lenmod = true;
}

void vector::setvalue(float *v, int args)
{
    int i;
    for(i = 0; i < n && i < args; i++)
        x[i] = v[i];

    if(n > args)
    {
        for(; i < n; i++)
            x[i] = 0;
    }
    lenmod = true;
}

void vector::setvalue(vector v)
{
    delete x;
    cachlen = v.cachlen;
    lenmod = v.lenmod;
    n = v.n;
    x = new float[n];
    for(int i = 0; i < n; i++)
        x[i] = v.x[i];
}

void vector::setvalue(vector *v)
{
    delete x;
    cachlen = v->cachlen;
    lenmod = v->lenmod;
    n = v->n;
    x = new float[n];
    for(int i = 0; i < n; i++)
        x[i] = v->x[i];
}

void vector::unify()
{
    float len = this->len();
    for(int i = 0; i < n; i++)
        x[i] /= len;
    lenmod = false;
    cachlen = 1;
}

vector vector::unifyc()
{
    float len = this->len();
    for(int i = 0; i < n; i++)
        x[i] /= len;
    lenmod = false;
    cachlen = 1;
    return vector(this);
}

vector *vector::unifycp()
{
    float len = this->len();
    for(int i = 0; i < n; i++)
        x[i] /= len;
    lenmod = false;
    cachlen = 1;
    return new vector(this);
}

void vector::add(Vertex2D vx)
{
    x[0] += vx.getX();
    x[1] += vx.getY();
    lenmod = true;
}
void vector::add(Vertex2D *vx)
{
    x[0] += vx->getX();
    x[1] += vx->getY();
    lenmod = true;
}
void vector::add(Vertex3D vx)
{
    x[0] += vx.getX();
    x[1] += vx.getY();
    x[2] += vx.getZ();
    lenmod = true;
}
void vector::add(Vertex3D *vx)
{
    x[0] += vx->getX();
    x[1] += vx->getY();
    x[2] += vx->getZ();
    lenmod = true;
}

void vector::add(vector v)
{
    for(int i = 0; i < n && i < v.n; i++)
        x[i] += v.x[i];
    lenmod = true;
}

void vector::add(vector *v)
{
    for(int i = 0; i < n && i < v->n; i++)
        x[i] += v->x[i];
    lenmod = true;
}

void vector::add(vector v0, vector v1)
{
    for(int i = 0; i < n && i < v0.n && i < v1.n; i++)
        x[i] = v0.x[i] + v1.x[i];
    lenmod = true;
}

void vector::add(vector *v0, vector *v1)
{
    for(int i = 0; i < n && i < v0->n && i < v1->n; i++)
        x[i] = v0->x[i] + v1->x[i];
    lenmod = true;
}

void vector::add(vector  v0, Vertex2D vx){ this->add(vx,v0); }

void vector::add(Vertex2D vx,  vector  v0)
{
    x[0] = vx.getX() + v0.x[0];
    x[1] = vx.getY() + v0.x[1];
    for (int i = 2; i < n && i < v0.n; i++)
        x[i] = v0.x[i];
    lenmod = true;
}

void vector::add(vector  v0, Vertex2D *vx){ this->add(vx,v0); }

void vector::add(Vertex2D *vx,  vector  v0)
{
    x[0] = vx->getX() + v0.x[0];
    x[1] = vx->getY() + v0.x[1];
    for (int i = 2; i < n && i < v0.n; i++)
        x[i] = v0.x[i];
    lenmod = true;
}

void vector::add(vector  v0, Vertex3D vx){ this->add(vx,v0); }

void vector::add(Vertex3D vx,  vector  v0)
{
    x[0] = vx.getX() + v0.x[0];
    x[1] = vx.getY() + v0.x[1];
    x[2] = vx.getZ() + v0.x[2];
    for (int i = 3; i < n && i < v0.n; i++)
        x[i] = v0.x[i];
    lenmod = true;
}

void vector::add(vector  v0, Vertex3D *vx){ this->add(vx,v0); }

void vector::add(Vertex3D *vx,  vector  v0)
{
    x[0] = vx->getX() + v0.x[0];
    x[1] = vx->getY() + v0.x[1];
    x[2] = vx->getZ() + v0.x[2];
    for (int i = 3; i < n && i < v0.n; i++)
        x[i] = v0.x[i];
    lenmod = true;
}

void vector::add(vector  *v0, Vertex2D vx){ this->add(vx,v0); }

void vector::add(Vertex2D vx,  vector  *v0)
{
    x[0] = vx.getX() + v0->x[0];
    x[1] = vx.getY() + v0->x[1];
    for (int i = 2; i < n && i < v0->n; i++)
        x[i] = v0->x[i];
    lenmod = true;
}

void vector::add(vector  *v0, Vertex2D *vx){ this->add(vx,v0); }

void vector::add(Vertex2D *vx,  vector  *v0)
{
    x[0] = vx->getX() + v0->x[0];
    x[1] = vx->getY() + v0->x[1];
    for (int i = 2; i < n && i < v0->n; i++)
        x[i] = v0->x[i];
    lenmod = true;
}

void vector::add(vector  *v0, Vertex3D vx){ this->add(vx,v0); }

void vector::add(Vertex3D vx,  vector  *v0)
{
    x[0] = vx.getX() + v0->x[0];
    x[1] = vx.getY() + v0->x[1];
    x[2] = vx.getZ() + v0->x[2];
    for (int i = 3; i < n && i < v0->n; i++)
        x[i] = v0->x[i];
    lenmod = true;
}

void vector::add(vector  *v0, Vertex3D *vx){ this->add(vx,v0); }

void vector::add(Vertex3D *vx,  vector  *v0)
{
    x[0] = vx->getX() + v0->x[0];
    x[1] = vx->getY() + v0->x[1];
    x[2] = vx->getZ() + v0->x[2];
    for (int i = 3; i < n && i < v0->n; i++)
        x[i] = v0->x[i];
    lenmod = true;
}



void vector::add(Vertex3D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i].getX();
        x[1] += vx[i].getY();
        x[2] += vx[i].getZ();
    }
    lenmod = true;
}

void vector::add(Vertex3D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i]->getX();
        x[1] += vx[i]->getY();
        x[2] += vx[i]->getZ();
    }
    lenmod = true;
}

void vector::add(Vertex2D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i].getX();
        x[1] += vx[i].getY();
    }
    lenmod = true;
}

void vector::add(Vertex2D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i]->getX();
        x[1] += vx[i]->getY();
    }
    lenmod = true;
}

void vector::add(vector *v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < n && j < v[i].n; j++)
            x[j] += v[i].x[j];
    }
    lenmod = true;
}


void vector::add(vector **v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < n && j < v[i]->n; j++)
            x[j] += v[i]->x[j];
    }
    lenmod = true;
}

void vector::addvc(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
        {
            vector *temp = va_arg ( arguments, vector *);
            for(int j = 0; j < n && j < temp->n; j++)
                x[j] += temp->x[j];
        }
    va_end ( arguments );
    this->lenmod = true;
}

void vector::addvx2(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
        {
            Vertex2D *temp = va_arg ( arguments, Vertex2D *);
            x[0] += temp->getX();
            x[1] += temp->getY();
        }
    va_end ( arguments );
    this->lenmod = true;
}

void vector::addvx3(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
        {
            Vertex3D *temp = va_arg ( arguments, Vertex3D *);
            x[0] += temp->getX();
            x[1] += temp->getY();
            x[2] += temp->getZ();
        }
    va_end ( arguments );
    this->lenmod = true;
}

vector vector::addc(vector v)
{
    this->add(v);
    return vector(this);
}

vector *vector::addc(vector *v)
{
    this->add(v);
    return new vector(this);
}

vector vector::addc(Vertex3D v)
{
    this->add(v);
    return vector(this);
}

vector *vector::addc(Vertex3D *v)
{
    this->add(v);
    return new vector(this);
}

vector vector::addc(Vertex2D v)
{
    this->add(v);
    return vector(this);
}

vector *vector::addc(Vertex2D *v)
{
    this->add(v);
    return new vector(this);
}



vector vector::addc(vector v0, vector v1)
{
    this->add(v0,v1);
    return vector(this);
}

vector vector::addc(Vertex3D v0, vector v1)
{
    this->add(v0,v1);
    return vector(this);
}

vector vector::addc(vector v1, Vertex3D v0)
{
    this->add(v0,v1);
    return vector(this);
}

vector *vector::addc(vector *v0, vector *v1)
{
    this->add(v0,v1);
    return new vector(this);
}

vector *vector::addc(Vertex3D *v0, vector *v1)
{
    this->add(v0,v1);
    return new vector(this);
}

vector *vector::addc(vector *v1, Vertex3D *v0)
{
    this->add(v0,v1);
    return new vector(this);
}

vector *vector::addc(vector  *v, int args)
{
    this->add(v,args);
    return new vector(this);
}

vector *vector::addc(vector  **v, int args)
{
    this->add(v,args);
    return new vector(this);
}

vector *vector::addc(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
        {
            vector *temp = va_arg ( arguments, vector *);
            this->add(temp);

        }
    va_end ( arguments );
    lenmod = true;
    return new vector(this);
}


void vector::sub(vector v)
{
    for(int i = 0; i < n && i < v.n; i++)
        x[i] -= v.x[i];
    lenmod = true;
}

void vector::sub(vector *v)
{
    for(int i = 0; i < n && i < v->n; i++)
        x[i] -= v->x[i];
    lenmod = true;
}

void vector::sub(vector v0, vector v1)
{
    for(int i = 0; i < n && i < v0.n && i < v1.n; i++)
        x[i] = v0.x[i] - v1.x[i];
    lenmod = true;
}

void vector::sub(vector *v0, vector *v1)
{
    for(int i = 0; i < n && i < v0->n && i < v1->n; i++)
        x[i] = v0->x[i] - v1->x[i];
    lenmod = true;
}

vector vector::subc(vector v)
{
    this->sub(v);
    return vector(this);
}

vector *vector::subc(vector *v)
{
    this->sub(v);
    return new vector(this);
}

vector vector::subc(vector v0, vector v1)
{
    this->sub(v0, v1);
    return vector(this);
}

vector *vector::subc(vector *v0, vector *v1)
{
    this->sub(v0, v1);
    return new vector(this);
}

void vector::scale(float s)
{
    for(int i = 0; i < n; i++)
        x[i] *= s;
    lenmod = true;
}


void vector::scale(float s, vector v)
{
    v.scale(s);
    this->setvalue(v);
    lenmod = true;
}

void vector::scale(float s, vector *v)
{
    v->scale(s);
    this->setvalue(v);
    lenmod = true;
}

vector vector::scalec(float s)
{
    this->scale(s);
    return vector(this);
}

vector vector::scalec(float s, vector v)
{
    this->scale(s,v);
    return vector(this);
}

vector *vector::scalec(float s, vector *v)
{
    this->scale(s,v);
    return new vector(this);
}

vector *vector::scalecp(float s)
{
    this->scale(s);
    return new vector(this);
}

/*
void vector::cross(vector v0, vector v1)
{
     x = (v0.y*v1.z)-(v0.z*v1.y);
     y = (v0.z*v1.x)-(v0.x*v1.z);
     z = (v0.x*v1.y)-(v0.y*v1.x);
}

void vector::cross(vector *v0, vector *v1)
{
     x = (v0->y*v1->z)-(v0->z*v1->y);
     y = (v0->z*v1->x)-(v0->x*v1->z);
     z = (v0->x*v1->y)-(v0->y*v1->x);
}

void vector::cross(vector *v0, vector v1)
{
     x = (v0->y*v1.z)-(v0->z*v1.y);
     y = (v0->z*v1.x)-(v0->x*v1.z);
     z = (v0->x*v1.y)-(v0->y*v1.x);
}

void vector::cross(vector v0, vector *v1)
{
     x = (v0.y*v1->z)-(v0.z*v1->y);
     y = (v0.z*v1->x)-(v0.x*v1->z);
     z = (v0.x*v1->y)-(v0.y*v1->x);
}

vector vector::cross(vector v)
{
    return vector(this).cross(v);
}

vector *vector::cross(vector *v)
{
    return (new vector(this))->cross(v);
}

vector vector::crossc(vector v)
{
    setvalue(vector(this).cross(v));
    return vector(this);
}

vector *vector::crossc(vector *v)
{
    setvalue(vector(this).cross(v));
    return new vector(this);
}

vector vector::crossc(vector v0, vector v1)
{
    this->cross(v0,v1);
    return vector(this);
}

vector *vector::crossc(vector *v0, vector *v1)
{
    this->cross(v0,v1);
    return new vector(this);
}

vector *vector::crossc(vector *v0, vector v1)
{
    this->cross(v0,v1);
    return new vector(this);
}

vector *vector::crossc(vector v0, vector *v1)
{
    this->cross(v0,v1);
    return new vector(this);
}

*/
float len(vector v)
{
    return v.len();
}

vector unify(vector v)
{
    return v.unifyc();
}

vector *unify(vector *v)
{
    v->unifyc();
    return new vector(v);
}

int printv(vector v)
{
    return v.print();
}
int printv(vector *v)
{
    return v->print();
}


const vector operator + (vector const v0, vector const v1)
{
    vector vr = vector((vector *)&v0);
    vr.add(v1);
    return vr;
}

const vector operator + (vector const *v0, vector const v1)
{
    vector vr = vector((vector *)v0);
    vr.add(v1);
    return vr;
}

const vector operator + (vector const v1,vector const *v0)
{
    vector vr = vector((vector *)v0);
    vr.add(v1);
    return vr;
}



const vector operator - (vector const v0, vector const v1)
{
    vector vr = vector((vector *)&v0);
    vr.sub(v1);
    return vr;
}

const vector operator - (vector const *v0, vector const v1)
{
    vector vr = vector((vector *)v0);
    vr.sub(v1);
    return vr;
}

const vector operator - (vector const v1, vector const *v0)
{
    vector vr = vector((vector *)v0);
    vr.sub(v1);
    return vr;
}


/*
const vector operator ^ (vector const v0, vector const v1)
{
    return ((vector)v0).cross(((vector)v1));
}

const vector operator ^ (vector const *v0, vector const v1)
{
    return ((vector *)v0)->cross(((vector)v1));
}

const vector operator ^ (vector const v1,vector const *v0)
{
    return ((vector *)v0)->cross(((vector)v1));
}
*/


const vector operator * (vector const v0, const float s)
{
    vector vr = vector((vector*)&v0);
    vr.scale(s);
    return vr;
}

const vector operator * (const float s,vector const v0)
{
    vector vr = vector((vector*)&v0);
    vr.scale(s);
    return vr;
}



vector vector::operator += (vector const v0)
{
    this->add(v0);
    return *this;
}

vector vector::operator += (vector const *v0)
{
    this->add((vector *)v0);
    return *this;
}



vector vector::operator -= (vector const v0)
{
    this->sub(v0);
    return *this;
}

vector vector::operator -= (vector const *v0)
{
    this->sub((vector *)v0);
    return *this;
}


vector vector::operator *= (const float s)
{
    this->scale(s);
    return vector(this);
}

//TODO: clean the  quick and dirty implementation
std::ostream& operator << (std::ostream& stream, vector const v)
{
    stream<<"X:"<<v.x[0]<<" Y:"<<v.x[1]<<" Z:"<<v.x[2];
    return stream;
}

std::ostream& operator << (std::ostream& stream, vector const *v)
{
    stream<<"X:"<<v->x[0]<<" Y:"<<v->x[1]<<" Z:"<<v->x[2];
    return stream;
}

bool operator == (vector const v0,vector const v1)
{
    for(int i = 0; i < v0.n && v1.n ; i++)
    {
        if(v0.x[i] != v1.x[i])
            return false;
    }
    return true;
}

bool operator != (vector const v0,vector const v1)
{
    for(int i = 0; i < v0.n && v1.n ; i++)
    {
        if(v0.x[i] != v1.x[i])
            return true;
    }
    return false;
}

