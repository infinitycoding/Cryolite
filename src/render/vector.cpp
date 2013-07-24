#include <math.h>
#include <vector.h>
#include <cstdarg>
#include <stdio.h>

vector::vector()
{
    x = 0;
    y = 0;
    z = 0;
    this->cachlen = 0;
    this->lenmod = false;
}

vector::vector(Vertex2D vx)
{

    this->x = vx.getX();
    this->y = vx.getY();
    this->z = 0;
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(Vertex2D *vx)
{

    this->x = vx->getX();
    this->y = vx->getY();
    this->z = 0;
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(Vertex3D vx)
{

    this->x = vx.getX();
    this->y = vx.getY();
    this->z = vx.getZ();
    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(Vertex3D *vx)
{

    this->x = vx->getX();
    this->y = vx->getY();
    this->z = vx->getZ();
    this->cachlen = 0;
    this->lenmod = true;
}


vector::vector(float x)
{
    this->x = x;
    y = 0;
    z = 0;
    this->cachlen = x;
    this->lenmod = false;
}

vector::vector(float x, float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;

    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->cachlen = 0;
    this->lenmod = true;
}

vector::vector(float *v,int args)
{
    switch(args)
    {
        case 0:
            x = 0;
            y = 0;
            z = 0;
        break;

        case 1:
            x = *v;
            y = 0;
            z = 0;
        break;

        case 2:
            x = v[0];
            y = v[1];
            z = 0;
        break;

        case 3:
            x = v[0];
            y = v[1];
            z = v[2];
        break;

        default:
            if(args < 0)
            {
                x = 0;
                y = 0;
                z = 0;
            }
            else if(args > 3)
            {
                x = v[0];
                y = v[1];
                z = v[2];
            }
        break;

    }


    this->cachlen = 0;
    this->lenmod = true;
}


vector::vector(vector *v)
{
    x = v->x;
    y = v->y;
    z = v->z;
    this->cachlen = v->cachlen;
    this->lenmod = v->lenmod;
}

void vector::null()
{
    x = 0;
    y = 0;
    z = 0;
}

float vector::len()
{
    if(lenmod)
    {
        this->cachlen = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        this->lenmod = false;
    }
    return cachlen;
}

int vector::print()
{
    return printf("X:%f Y:%f Z:%f\n",this->x,this->y,this->z);
}

void vector::setvalue(Vertex2D vx)
{
    this->x = vx.getX();
    this->y = vx.getY();
    this->lenmod = true;
}

void vector::setvalue(Vertex2D *vx)
{
    this->x = vx->getX();
    this->y = vx->getY();
    this->lenmod = true;
}

void vector::setvalue(Vertex3D vx)
{
    this->x = vx.getX();
    this->y = vx.getY();
    this->z = vx.getZ();
    this->lenmod = true;
}

void vector::setvalue(Vertex3D *vx)
{
    this->x = vx->getX();
    this->y = vx->getY();
    this->z = vx->getZ();
    this->lenmod = true;
}

void vector::setvalue(float x)
{
    this->x = x;
    this->lenmod = true;
}

void vector::setvalue(float x, float y)
{
    this->x = x;
    this->y = y;
    this->lenmod = true;
}

void vector::setvalue(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->lenmod = true;
}

void vector::setvalue(float *v, int args){

    switch(args)
    {
        case 0:
            x = 0;
            y = 0;
            z = 0;
        break;

        case 1:
            x = *v;
            y = 0;
            z = 0;
        break;

        case 2:
            x = v[0];
            y = v[1];
            z = 0;
        break;

        case 3:
            x = v[0];
            y = v[1];
            z = v[2];
        break;

        default:
            if(args < 0)
            {
                x = 0;
                y = 0;
                z = 0;
            }
            else if(args > 3)
            {
                x = v[0];
                y = v[1];
                z = v[2];
            }
        break;

    }
    lenmod = true;
}

void vector::setvalue(vector v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    this->cachlen = v.cachlen;
    this->lenmod = v.lenmod;
}

void vector::setvalue(vector *v)
{
    x = v->x;
    y = v->y;
    z = v->z;
    this->cachlen = v->cachlen;
    this->lenmod = v->lenmod;
}

void vector::unify()
{
    float len = this->len();
    x /= len;
    y /= len;
    z /= len;
    this->lenmod = false;
    this->cachlen = 1;
}

vector vector::unifyc()
{
    float len = this->len();
    x /= len;
    y /= len;
    z /= len;
    this->lenmod = false;
    this->cachlen = 1;
    return vector(this);
}

vector *vector::unifycp()
{
    float len = this->len();
    x /= len;
    y /= len;
    z /= len;
    this->lenmod = false;
    this->cachlen = 1;
    return new vector(this);
}

void vector::add(Vertex2D vx)
{
    this->x += vx.getX();
    this->y += vx.getY();
    this->lenmod = true;
}
void vector::add(Vertex2D *vx)
{
    this->x += vx->getX();
    this->y += vx->getY();
    this->lenmod = true;
}
void vector::add(Vertex3D vx)
{
    this->x += vx.getX();
    this->y += vx.getY();
    this->z += vx.getZ();
    this->lenmod = true;
}
void vector::add(Vertex3D *vx)
{
    this->x += vx->getX();
    this->y += vx->getY();
    this->z += vx->getZ();
    this->lenmod = true;
}

void vector::add(vector v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    this->lenmod = true;
}

void vector::add(vector *v)
{
    x += v->x;
    y += v->y;
    z += v->z;
    this->lenmod = true;
}

void vector::add(vector v0, vector v1)
{
    x = v0.x+v1.x;
    y = v0.y+v1.y;
    z = v0.z+v1.z;
    this->lenmod = true;
}

void vector::add(vector *v0, vector *v1)
{
    x = v0->x+v1->x;
    y = v0->y+v1->y;
    z = v0->z+v1->z;
    this->lenmod = true;
}

void vector::add(vector  v0, Vertex2D vx){ this->add(vx,v0); }

void vector::add(Vertex2D vx,  vector  v0)
{
    this->x = vx.getX() + v0.x;
    this->y = vx.getY() + v0.y;
    this->z = v0.z;
}

void vector::add(vector  v0, Vertex2D *vx){ this->add(vx,v0); }

void vector::add(Vertex2D *vx,  vector  v0)
{
    this->x = vx->getX() + v0.x;
    this->y = vx->getY() + v0.y;
    this->z = v0.z;
}

void vector::add(vector  v0, Vertex3D vx){ this->add(vx,v0); }

void vector::add(Vertex3D vx,  vector  v0)
{
    this->x = vx.getX() + v0.x;
    this->y = vx.getY() + v0.y;
    this->z = vx.getZ() + v0.z;
}

void vector::add(vector  v0, Vertex3D *vx){ this->add(vx,v0); }

void vector::add(Vertex3D *vx,  vector  v0)
{
    this->x = vx->getX() + v0.x;
    this->y = vx->getY() + v0.y;
    this->z = vx->getZ() + v0.z;
}

void vector::add(vector  *v0, Vertex2D vx){ this->add(vx,v0); }

void vector::add(Vertex2D vx,  vector  *v0)
{
    this->x = vx.getX() + v0->x;
    this->y = vx.getY() + v0->y;
    this->z = v0->z;
}

void vector::add(vector  *v0, Vertex2D *vx){ this->add(vx,v0); }

void vector::add(Vertex2D *vx,  vector  *v0)
{
    this->x = vx->getX() + v0->x;
    this->y = vx->getY() + v0->y;
    this->z = v0->z;
}

void vector::add(vector  *v0, Vertex3D vx){ this->add(vx,v0); }

void vector::add(Vertex3D vx,  vector  *v0)
{
    this->x = vx.getX() + v0->x;
    this->y = vx.getY() + v0->y;
    this->z = vx.getZ() + v0->z;
}

void vector::add(vector  *v0, Vertex3D *vx){ this->add(vx,v0); }

void vector::add(Vertex3D *vx,  vector  *v0)
{
    this->x = vx->getX() + v0->x;
    this->y = vx->getY() + v0->y;
    this->z = vx->getZ() + v0->z;
}



void vector::add(Vertex3D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += vx[i].getX();
        y += vx[i].getY();
        z += vx[i].getZ();
    }
    this->lenmod = true;
}

void vector::add(Vertex3D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += vx[i]->getX();
        y += vx[i]->getY();
        z += vx[i]->getZ();
    }
    this->lenmod = true;
}

void vector::add(Vertex2D *vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += vx[i].getX();
        y += vx[i].getY();
    }
    this->lenmod = true;
}

void vector::add(Vertex2D **vx, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += vx[i]->getX();
        y += vx[i]->getY();
    }
    this->lenmod = true;
}

void vector::add(vector *v, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += v[i].x;
        y += v[i].y;
        z += v[i].z;
    }
    this->lenmod = true;
}


void vector::add(vector **v, int args)
{
    for(int i = 0; i < args; i++)
    {
        x += v[i]->x;
        y += v[i]->y;
        z += v[i]->z;
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
            x += temp->x;
            y += temp->y;
            z += temp->z;
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
            x += temp->getX();
            y += temp->getY();
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
            x += temp->getX();
            y += temp->getY();
            z += temp->getZ();
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
            x += temp->x;
            y += temp->y;
            z += temp->z;

        }
    va_end ( arguments );
    this->lenmod = true;
    return new vector(this);
}


void vector::sub(vector v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    this->lenmod = true;
}

void vector::sub(vector *v)
{
    x -= v->x;
    y -= v->y;
    z -= v->z;
    this->lenmod = true;
}

void vector::sub(vector v0, vector v1)
{
    x = v0.x - v1.x;
    y = v0.y - v1.y;
    z = v0.z - v1.z;
    this->lenmod = true;
}

void vector::sub(vector *v0, vector *v1)
{
    x = v0->x - v1->x;
    y = v0->y - v1->y;
    z = v0->z - v1->z;
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
    x *= s;
    y *= s;
    z *= s;
    this->lenmod = true;
}


void vector::scale(float s, vector v)
{
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.lenmod = true;
    this->setvalue(v);
}

void vector::scale(float s, vector *v)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
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
    return printf("X:%f Y:%f Z:%f\n",v.x,v.y,v.z);
}
int printv(vector *v)
{
    return printf("X:%f Y:%f Z:%f\n",v->x,v->y,v->z);
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

std::ostream& operator << (std::ostream& stream, vector const v)
{
    stream<<"X:"<<v.x<<" Y:"<<v.y<<" Z:"<<v.z;
    return stream;
}

std::ostream& operator << (std::ostream& stream, vector const *v)
{
    stream<<"X:"<<v->x<<" Y:"<<v->y<<" Z:"<<v->z;
    return stream;
}

