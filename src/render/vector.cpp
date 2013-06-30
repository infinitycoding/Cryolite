#include <math.h>
#include <vector.h>
#include <cstdarg>
#include <stdio.h>

vector::vector()
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = 0;
    this->cachlen = 0;
    this->lenmod = false;
}

vector::vector(vertex2D vx)
{

    this->elements[0] = vx.x;
    this->elements[1] = vx.y;
    this->elements[2] = 0;
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(vertex2D *vx)
{

    this->elements[0] = vx->x;
    this->elements[1] = vx->y;
    this->elements[2] = 0;
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(vertex3D vx)
{

    this->elements[0] = vx.x;
    this->elements[1] = vx.y;
    this->elements[2] = vx.z;
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(vertex3D *vx)
{

    this->elements[0] = vx->x;
    this->elements[1] = vx->y;
    this->elements[2] = vx->z;
    this->cachlen = 0;
    this->lenmod = true;
}


vector::vector(float x)
{
    this->elements[0] = x;
    for(int i = 1; i < 3; i++)
        this->elements[i] = 0;
    this->cachlen = x;
    this->lenmod = false;
}

vector::vector(float x, float y)
{
    this->elements[0] = x;
    this->elements[1] = y;
    this->elements[2] = 0;

    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(float x, float y, float z)
{
    this->elements[0] = x;
    this->elements[1] = y;
    this->elements[2] = z;

    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(float *v,int args)
{
    for(int i = 0; i < args && i < 3; i++)
        this->elements[i] = v[i];

    for(int i = args; i < 3; i++)
        this->elements[i] = 0;

    this->cachlen = 0;
    this->lenmod = true;
}


vector::vector(vector *v)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = v->elements[i];
    this->cachlen = v->cachlen;
    this->lenmod = v->lenmod;
}

void vector::null()
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = 0;
}

float vector::len()
{
    if(lenmod)
    {
        float sum = 0;
        for(int i = 0; i < 3; i++)
            sum += pow(this->elements[i],2);
        this->cachlen = sqrt(sum);
        this->lenmod = false;
    }
    return cachlen;
}

int vector::print()
{
    return printf("X:%f Y:%f Z:%f\n",this->elements[0],this->elements[1],this->elements[2]);
}

void vector::setvalue(vertex2D vx)
{
    this->elements[0] = vx.x;
    this->elements[1] = vx.y;
    this->lenmod = true;
}

void vector::setvalue(vertex2D *vx)
{
    this->elements[0] = vx->x;
    this->elements[1] = vx->y;
    this->lenmod = true;
}

void vector::setvalue(vertex3D vx)
{
    this->elements[0] = vx.x;
    this->elements[1] = vx.y;
    this->elements[2] = vx.z;
    this->lenmod = true;
}

void vector::setvalue(vertex3D *vx)
{
    this->elements[0] = vx->x;
    this->elements[1] = vx->y;
    this->elements[2] = vx->z;
    this->lenmod = true;
}

void vector::setvalue(float x)
{
    this->elements[0] = x;
    this->lenmod = true;
}

void vector::setvalue(float x, float y)
{
    this->elements[0] = x;
    this->elements[1] = y;
    this->lenmod = true;
}

void vector::setvalue(float x, float y, float z)
{
    this->elements[0] = x;
    this->elements[1] = y;
    this->elements[2] = z;
    this->lenmod = true;
}

void vector::setvalue(float *v, int args){
    for(int i = 0; i < args && i < 3; i++)
        this->elements[i] = v[i];
    for(int i = args; i < 3; i++)
        this->elements[i] = 0;
}

void vector::setvalue(vector v)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = v.elements[i];
    this->cachlen = v.cachlen;
    this->lenmod = v.lenmod;
}

void vector::setvalue(vector *v)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = v->elements[i];
    this->cachlen = v->cachlen;
    this->lenmod = v->lenmod;
}

void vector::unify()
{
    float len = this->len();
    for(int i = 0; i < 3; i++)
        this->elements[i] /=len;
    this->lenmod = false;
    this->cachlen = 1;
}

vector vector::unifyc()
{
    float len = this->len();
    for(int i = 0; i < 3; i++)
        this->elements[i] /=len;
    this->lenmod = false;
    this->cachlen = 1;
    return vector(this);
}

vector *vector::unifycp()
{
    float len = this->len();
    for(int i = 0; i < 3; i++)
        this->elements[i] /=len;
    this->lenmod = false;
    this->cachlen = 1;
    return new vector(this);
}

void vector::add(vertex2D vx)
{
    this->elements[0] += vx.x;
    this->elements[1] += vx.y;
    this->lenmod = true;
}
void vector::add(vertex2D *vx)
{
    this->elements[0] += vx->x;
    this->elements[1] += vx->y;
    this->lenmod = true;
}
void vector::add(vertex3D vx)
{
    this->elements[0] += vx.x;
    this->elements[1] += vx.y;
    this->elements[2] += vx.z;
    this->lenmod = true;
}
void vector::add(vertex3D *vx)
{
    this->elements[0] += vx->x;
    this->elements[1] += vx->y;
    this->elements[2] += vx->z;
    this->lenmod = true;
}

void vector::add(vector  v0, vertex2D vx){ this->add(vx,v0); }

void vector::add(vertex2D vx,  vector  v0)
{
    this->elements[0] = vx.x + v0.elements[0];
    this->elements[1] = vx.y + v0.elements[1];
    this->elements[2] = v0.elements[2];
}

void vector::add(vector  v0, vertex2D *vx){ this->add(vx,v0); }

void vector::add(vertex2D *vx,  vector  v0)
{
    this->elements[0] = vx->x + v0.elements[0];
    this->elements[1] = vx->y + v0.elements[1];
    this->elements[2] = v0.elements[2];
}

void vector::add(vector  v0, vertex3D vx){ this->add(vx,v0); }

void vector::add(vertex3D vx,  vector  v0)
{
    this->elements[0] = vx.x + v0.elements[0];
    this->elements[1] = vx.y + v0.elements[1];
    this->elements[2] = vx.z + v0.elements[2];
}

void vector::add(vector  v0, vertex3D *vx){ this->add(vx,v0); }

void vector::add(vertex3D *vx,  vector  v0)
{
    this->elements[0] = vx->x + v0.elements[0];
    this->elements[1] = vx->y + v0.elements[1];
    this->elements[2] = vx->z + v0.elements[2];
}

void vector::add(vector  *v0, vertex2D vx){ this->add(vx,v0); }

void vector::add(vertex2D vx,  vector  *v0)
{
    this->elements[0] = vx.x + v0->elements[0];
    this->elements[1] = vx.y + v0->elements[1];
    this->elements[2] = v0->elements[2];
}

void vector::add(vector  *v0, vertex2D *vx){ this->add(vx,v0); }

void vector::add(vertex2D *vx,  vector  *v0)
{
    this->elements[0] = vx->x + v0->elements[0];
    this->elements[1] = vx->y + v0->elements[1];
    this->elements[2] = v0->elements[2];
}

void vector::add(vector  *v0, vertex3D vx){ this->add(vx,v0); }

void vector::add(vertex3D vx,  vector  *v0)
{
    this->elements[0] = vx.x + v0->elements[0];
    this->elements[1] = vx.y + v0->elements[1];
    this->elements[2] = vx.z + v0->elements[2];
}

void vector::add(vector  *v0, vertex3D *vx){ this->add(vx,v0); }

void vector::add(vertex3D *vx,  vector  *v0)
{
    this->elements[0] = vx->x + v0->elements[0];
    this->elements[1] = vx->y + v0->elements[1];
    this->elements[2] = vx->z + v0->elements[2];
}


void vector::add(vector v)
{
    for(int i = 0; i < 3 ; i++)
        this->elements[i] += v.elements[i];
    this->lenmod = true;
}

void vector::add(vector *v)
{
    for(int i = 0; i < 3 ; i++)
        this->elements[i] += v->elements[i];
    this->lenmod = true;
}

void vector::add(vector v0, vector v1)
{
    for(int i = 0; i < 3 ; i++)
        this->elements[i] = v0.elements[i]+v1.elements[i];
    this->lenmod = true;
}

void vector::add(vector *v0, vector *v1)
{
    for(int i = 0; i < 3 ; i++)
        this->elements[i] = v0->elements[i]+v1->elements[i];
    this->lenmod = true;
}

void vector::add(vector *v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            this->elements[j] += v[i].elements[j];
        }
    }
    this->lenmod = true;
}


void vector::add(vector **v, int args)
{
    for(int i = 0; i < args; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            this->elements[j] += v[i]->elements[j];
        }
    }
    this->lenmod = true;
}

void vector::addvc(int args, ...)
{
    va_list arguments;
    va_start ( arguments, args );
        for(int i = 0; i < args; i++)
        {
            vector *temp = va_arg ( arguments, vector *);
            for(int j = 0; j < 3 ; j++)
            {
                this->elements[j] += temp->elements[j];
            }

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

vector vector::addc(vector v0, vector v1)
{
    this->add(v0,v1);
    return vector(this);
}

vector *vector::addc(vector *v0, vector *v1)
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
            for(int j = 0; j < 3 ; j++)
            {
                this->elements[j] += temp->elements[j];
            }

        }
    va_end ( arguments );
    this->lenmod = true;
    return new vector(this);
}


void vector::sub(vector v)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] -= v.elements[i];
    this->lenmod = true;
}

void vector::sub(vector *v)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] -= v->elements[i];
    this->lenmod = true;
}

void vector::sub(vector v0, vector v1)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = v0.elements[i]-v1.elements[i];
    this->lenmod = true;
}

void vector::sub(vector *v0, vector *v1)
{
    for(int i = 0; i < 3; i++)
        this->elements[i] = v0->elements[i]-v1->elements[i];
    this->lenmod = true;
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
        this->elements[i] *= s;
    this->lenmod = true;
}


void vector::scale(float s, vector v)
{
    for(int i = 0; i < 3; i++)
        v.elements[i] *= s;
    v.lenmod = true;
    this->setvalue(v);
}

void vector::scale(float s, vector *v)
{
    for(int i = 0; i < 3; i++)
        v->elements[i] *= s;
    v->lenmod = true;
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
    return printf("X:%f Y:%f Z:%f\n",v.elements[0],v.elements[1],v.elements[2]);
}
int printv(vector *v)
{
    return printf("X:%f Y:%f Z:%f\n",v->elements[0],v->elements[1],v->elements[2]);
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

std::ostream& operator << (std::ostream& stream, vector const v)
{
    stream<<"X:"<<v.elements[0]<<" Y:"<<v.elements[1]<<" Z:"<<v.elements[2];
    return stream;
}

std::ostream& operator << (std::ostream& stream, vector const *v)
{
    stream<<"X:"<<v->elements[0]<<" Y:"<<v->elements[1]<<" Z:"<<v->elements[2];
    return stream;
}

