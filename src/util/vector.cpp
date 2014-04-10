#include <math.h>
#include <vector.h>
#include <cstdarg>
#include <stdio.h>

vector::vector()
{
    for(int i = 0; i < 3; i++)
        x[i] = 0;
}

vector::vector(vertex2D vx)
{
    x[0] = vx.x;
    x[1] = vx.y;
    x[2] = 0;
}

vector::vector(const vertex2D *vx)
{
    x[0] = vx->x;
    x[1] = vx->y;
    x[2] = 0;
}

vector::vector(vertex3D vx)
{
    x[0] = vx.x;
    x[1] = vx.y;
    x[2] = vx.z;
}

vector::vector(const vertex3D *vx)
{
    x[0] = vx->x;
    x[1] = vx->y;
    x[2] = vx->z;
}


vector::vector(float x0,float x1,float x2)
{
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
}

vector::vector(const float *v,int args = 3)
{
    int i;
    for(i = 0; i < args && i < 3; i++)
        x[i] = v[i];

    if(args > 3)
    {
        for(; i < 3; i++)
            x[i] = 0;
    }
}


vector::vector(vector *v)
{
    for(int i = 0; i < 3; i++)
        x[i] = v->x[i];
}

void vector::null()
{
    for(int i = 0; i < 3; i++)
        x[i] = 0;
}

float vector::len() const
{
    float temp = 0;
    for (int i = 0; i < 3; i++)
        temp += x[i]*x[i];
    return sqrt(temp);
}

int vector::print() const
{
    int num = 0;
    for(int i = 0; i < 3; i++)
        num += printf("X%d:%f ",i,x[i]);
    printf("\n");
    return num;
}

void vector::setvalue(vertex2D vx)
{
    x[0] = vx.x;
    x[1] = vx.y;
}

void vector::setvalue(const vertex2D *vx)
{
    x[0] = vx->x;
    x[1] = vx->y;
}

void vector::setvalue(vertex3D vx)
{
    x[0] = vx.x;
    x[1] = vx.y;
    x[2] = vx.z;
}

void vector::setvalue(const vertex3D *vx)
{
    x[0] = vx->x;
    x[1] = vx->y;
    x[2] = vx->z;
}

void vector::setvalue(float x0)
{
    x[0] = x0;
}

void vector::setvalue(float x0, float x1)
{
    x[0] = x0;
    x[1] = x1;
}

void vector::setvalue(float x0, float x1, float x2)
{
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
}

void vector::setvalue(float *v, int args)
{
    int i;
    for(i = 0; i < 3 && i < args; i++)
        x[i] = v[i];

    if(args < 3)
    {
        for(; i < 3; i++)
            x[i] = 0;
    }
}

void vector::setvalue(vector v)
{
    for(int i = 0; i < 3; i++)
        x[i] = v.x[i];
}

void vector::setvalue(vector *v)
{
    for(int i = 0; i < 3; i++)
        x[i] = v->x[i];
}

void vector::unify()
{
    float len = this->len();
    for(int i = 0; i < 3; i++)
        x[i] /= len;
}

vector vector::unifyc()
{
    this->unify();
    return vector(this);
}

vector *vector::unifycp()
{
    this->unify();
    return new vector(this);
}

void vector::add(vertex2D vx)
{
    x[0] += vx.x;
    x[1] += vx.y;
}
void vector::add(vertex2D *vx)
{
    x[0] += vx->x;
    x[1] += vx->y;
}
void vector::add(vertex3D vx)
{
    x[0] += vx.x;
    x[1] += vx.y;
    x[2] += vx.z;
}
void vector::add(vertex3D *vx)
{
    x[0] += vx->x;
    x[1] += vx->y;
    x[2] += vx->z;
}

void vector::add(vector v)
{
    for(int i = 0; i < 3; i++)
        x[i] += v.x[i];
}

void vector::add(vector *v)
{
    for(int i = 0; i < 3; i++)
        x[i] += v->x[i];
}

void vector::add(vector v0, vector v1)
{
    for(int i = 0; i < 3; i++)
        x[i] = v0.x[i] + v1.x[i];
}

void vector::add(vector *v0, vector *v1)
{
    for(int i = 0; i < 3; i++)
        x[i] = v0->x[i] + v1->x[i];
}

void vector::add(vector  v0, vertex2D vx){ this->add(vx,v0); }

void vector::add(vertex2D vx,  vector  v0)
{
    x[0] = vx.x + v0.x[0];
    x[1] = vx.y + v0.x[1];
    x[2] = v0.x[2];
}

void vector::add(vector  v0, vertex2D *vx){ this->add(vx,v0); }

void vector::add(vertex2D *vx,  vector  v0)
{
    x[0] = vx->x + v0.x[0];
    x[1] = vx->y + v0.x[1];
    x[2] = v0.x[2];
}

void vector::add(vector  v0, vertex3D vx){ this->add(vx,v0); }

void vector::add(vertex3D vx,  vector  v0)
{
    x[0] = vx.x + v0.x[0];
    x[1] = vx.y + v0.x[1];
    x[2] = vx.z + v0.x[2];
}

void vector::add(vector  v0, vertex3D *vx){ this->add(vx,v0); }

void vector::add(vertex3D *vx,  vector  v0)
{
    x[0] = vx->x + v0.x[0];
    x[1] = vx->y + v0.x[1];
    x[2] = vx->z + v0.x[2];
}

void vector::add(vector  *v0, vertex2D vx){ this->add(vx,v0); }

void vector::add(vertex2D vx,  vector  *v0)
{
    x[0] = vx.x + v0->x[0];
    x[1] = vx.y + v0->x[1];
    x[2] = v0->x[2];
}

void vector::add(vector  *v0, vertex2D *vx){ this->add(vx,v0); }

void vector::add(vertex2D *vx,  vector  *v0)
{
    x[0] = vx->x + v0->x[0];
    x[1] = vx->y + v0->x[1];
    x[2] = v0->x[2];
}

void vector::add(vector  *v0, vertex3D vx){ this->add(vx,v0); }

void vector::add(vertex3D vx,  vector  *v0)
{
    x[0] = vx.x + v0->x[0];
    x[1] = vx.y + v0->x[1];
    x[2] = vx.z + v0->x[2];
}

void vector::add(vector  *v0, vertex3D *vx){ this->add(vx,v0); }

void vector::add(vertex3D *vx,  vector  *v0)
{
    x[0] = vx->x + v0->x[0];
    x[1] = vx->y + v0->x[1];
    x[2] = vx->z + v0->x[2];
}



void vector::add(vertex3D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i].x;
        x[1] += vx[i].y;
        x[2] += vx[i].z;
    }
}

void vector::add(vertex3D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i]->x;
        x[1] += vx[i]->y;
        x[2] += vx[i]->z;
    }
}

void vector::add(vertex2D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i].x;
        x[1] += vx[i].y;
    }
}

void vector::add(vertex2D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x[0] += vx[i]->x;
        x[1] += vx[i]->y;
    }
}

void vector::add(vector *v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < 3; j++)
            x[j] += v[i].x[j];
    }
}


void vector::add(vector **v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < 3; j++)
            x[j] += v[i]->x[j];
    }
}

void vector::addvc(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
            this->add(va_arg ( arguments, vector *));
    va_end ( arguments );
}

void vector::addvx2(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
            this->add(va_arg( arguments, vertex2D *));
    va_end ( arguments );
}

void vector::addvx3(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
            this->add(va_arg( arguments, vertex3D *));
    va_end ( arguments );
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

vector vector::addc(vertex3D v)
{
    this->add(v);
    return vector(this);
}

vector *vector::addc(vertex3D *v)
{
    this->add(v);
    return new vector(this);
}

vector vector::addc(vertex2D v)
{
    this->add(v);
    return vector(this);
}

vector *vector::addc(vertex2D *v)
{
    this->add(v);
    return new vector(this);
}



vector vector::addc(vector v0, vector v1)
{
    this->add(v0,v1);
    return vector(this);
}

vector vector::addc(vertex3D v0, vector v1)
{
    this->add(v0,v1);
    return vector(this);
}

vector vector::addc(vector v1, vertex3D v0)
{
    this->add(v0,v1);
    return vector(this);
}

vector *vector::addc(vector *v0, vector *v1)
{
    this->add(v0,v1);
    return new vector(this);
}

vector *vector::addc(vertex3D *v0, vector *v1)
{
    this->add(v0,v1);
    return new vector(this);
}

vector *vector::addc(vector *v1, vertex3D *v0)
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
    return new vector(this);
}


void vector::sub(vector v)
{
    for(int i = 0; i < 3; i++)
        x[i] -= v.x[i];
}

void vector::sub(vector *v)
{
    for(int i = 0; i < 3; i++)
        x[i] -= v->x[i];
}

void vector::sub(vector v0, vector v1)
{
    for(int i = 0; i < 3; i++)
        x[i] = v0.x[i] - v1.x[i];
}

void vector::sub(vector *v0, vector *v1)
{
    for(int i = 0; i < 3; i++)
        x[i] = v0->x[i] - v1->x[i];
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
    for(int i = 0; i < 3; i++)
        x[i] *= s;
}


void vector::scale(float s, vector v)
{
    v.scale(s);
    this->setvalue(v);
}

void vector::scale(float s, vector *v)
{
    v->scale(s);
    this->setvalue(v);
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

void vector::mul(vector v)
{
    for(int i = 0; i < 3; i++)
        x[i] *= v.x[i];
}

void vector::mul(vector *v)
{
    for(int i = 0; i < 3; i++)
        x[i] *= v->x[i];
}

float vector::largest()
{
    float l = 0;
    for(int i = 0; i < 3; i++)
    {
        if(x[i]>l)
            l = x[i];
    }
    return l;
}

float vector::smalest()
{
    float l = ~0;
    for(int i = 0; i < 3; i++)
    {
        if(x[i]<l)
            l = x[i];
    }
    return l;
}


void vector::cross(vector v0, vector v1)
{
     x[0] = (v0.x[1]*v1.x[2])-(v0.x[2]*v1.x[1]);
     x[1] = (v0.x[2]*v1.x[0])-(v0.x[0]*v1.x[2]);
     x[2] = (v0.x[0]*v1.x[1])-(v0.x[1]*v1.x[0]);
}

void vector::cross(vector *v0, vector *v1)
{
     x[0] = (v0->x[1]*v1->x[2])-(v0->x[2]*v1->x[1]);
     x[1] = (v0->x[2]*v1->x[0])-(v0->x[0]*v1->x[2]);
     x[2] = (v0->x[0]*v1->x[1])-(v0->x[1]*v1->x[0]);
}

void vector::cross(vector *v0, vector v1)
{
     x[0] = (v0->x[1]*v1.x[2])-(v0->x[2]*v1.x[1]);
     x[1] = (v0->x[2]*v1.x[0])-(v0->x[0]*v1.x[2]);
     x[2] = (v0->x[0]*v1.x[1])-(v0->x[1]*v1.x[0]);
}

void vector::cross(vector v0, vector *v1)
{
     x[0] = (v0.x[1]*v1->x[2])-(v0.x[2]*v1->x[1]);
     x[1] = (v0.x[2]*v1->x[0])-(v0.x[0]*v1->x[2]);
     x[2] = (v0.x[0]*v1->x[1])-(v0.x[1]*v1->x[0]);
}

vector vector::cross(vector v)
{
    vector r;
    r.x[0] = (x[1]*v.x[2])-(x[2]*v.x[1]);
    r.x[1] = (x[2]*v.x[0])-(x[0]*v.x[2]);
    r.x[2] = (x[0]*v.x[1])-(x[1]*v.x[0]);
    return r;
}

vector *vector::cross(vector *v)
{
    return new vector(this->cross(v));
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
    for(int i = 0; i < 3; i++)
    {
        if(v0.x[i] != v1.x[i])
            return false;
    }
    return true;
}

bool operator != (vector const v0,vector const v1)
{
    for(int i = 0; i < 3; i++)
    {
        if(v0.x[i] != v1.x[i])
            return true;
    }
    return false;
}

