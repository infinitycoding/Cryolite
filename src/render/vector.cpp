#include <math.h>

#include <vector.h>


float vlen(vector3D v)
{
    if(v.x<0)
        v.x *= -1;
    if(v.y<0)
        v.y *= -1;
    if(v.z<0)
        v.z *= -1;
    return sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
}

float vlen(vector2D v)
{
    if(v.x<0)
        v.x *= -1;
    if(v.y<0)
        v.y *= -1;
    return sqrt((v.x*v.x)+(v.y*v.y));
}

float vlen(vector3D *v)
{
    vector3D vp = *v;
    return vlen(vp);
}

float vlen(vector2D *v)
{
    vector2D vp = *v;
    return vlen(vp);
}

vector3D vunify(vector3D v)
{
    float len = vlen(v);
    v.x /= len;
    v.y /= len;
    v.z /= len;
    return v;
}

vector2D vunify(vector2D v)
{
    float len = vlen(v);
    v.x /= len;
    v.y /= len;
    return v;
}

vector3D *vunify(vector3D *v)
{
    vector3D *vu = new vector3D;
    *vu = vunify(*v);
    return vu;

}

vector2D *vunify(vector2D *v)
{
    vector2D *vu = new vector2D;
    *vu = vunify(*v);
    return vu;

}

vector3D vunifyc(vector3D *v)
{
    *v = vunify(*v);
    return *v;
}

vector2D vunifyc(vector2D *v)
{
    *v = vunify(*v);
    return *v;
}

vector3D vadd(vector3D a,vector3D b)
{
    vector3D r = {a.x+b.x,a.y+b.y,a.z+b.z};
    return r;
}

vector2D vadd(vector2D a,vector2D b)
{
    vector2D r = {a.x+b.x,a.y+b.y};
    return r;
}

vector3D *vadd(vector3D *a,vector3D *b)
{
    vector3D *vr = new vector3D;
    *vr = vadd(*a,*b);
    return vr;
}

vector2D *vadd(vector2D *a,vector2D *b)
{
    vector2D *vr = new vector2D;
    *vr = vadd(*a,*b);
    return vr;
}

vector3D vaddc(vector3D *dest,vector3D *b)
{
    *dest = vadd(*dest,*b);
    return *dest;
}

vector2D vaddc(vector2D *dest,vector2D *b)
{
    *dest = vadd(*dest,*b);
    return *dest;
}

vector3D vsub(vector3D a,vector3D b)
{
    vector3D r = {a.x-b.x,a.y-b.y,a.z-b.z};
    return r;
}

vector2D vsub(vector2D a,vector2D b)
{
    vector2D r = {a.x-b.x,a.y-b.y};
    return r;
}

vector3D *vsub(vector3D *a,vector3D *b)
{
    vector3D *vr = new vector3D;
    *vr = vsub(*a,*b);
    return vr;
}

vector2D *vsub(vector2D *a,vector2D *b)
{
    vector2D *vr = new vector2D;
    *vr = vsub(*a,*b);
    return vr;
}

vector3D vsubc(vector3D *dest,vector3D *b)
{
    *dest = vsub(*dest,*b);
    return *dest;
}

vector2D vsubc(vector2D *dest,vector2D *b)
{
    *dest = vsub(*dest,*b);
    return *dest;
}

vector3D vscale(float s,vector3D v)
{
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return v;
}

vector2D vscale(float s,vector2D v)
{
    v.x *= s;
    v.y *= s;
    return v;
}

vector3D *vscale(float s,vector3D *v)
{
    vector3D *vr = new vector3D;
    *vr = vscale(s,*v);
    return vr;
}

vector2D *vscale(float s,vector2D *v)
{
    vector2D *vr = new vector2D;
    *vr = vscale(s,*v);
    return vr;
}

vector3D vscalec(float s,vector3D *v)
{
    vector3D vr = {v->x*s,v->y*s,v->z*s};
    return vr;
}

vector2D vscalec(float s,vector2D *v)
{
    vector2D vr = {v->x*s,v->y*s};
    return vr;
}

vector2D vset(float x,float y)
{
    vector2D v = {x,y};
    return v;
}

vector3D vset(float x,float y,float z)
{
    vector3D v = {x,y,z};
    return v;
}

void vset(vector2D *v, float x, float y)
{
    v->x = x;
    v->y = y;
}

void vset(vector3D *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

vector3D vnull3D(void)
{
    vector3D v = NULLVECTOR3D;
    return v;
}

vector2D vnull2D(void)
{
    vector2D v = NULLVECTOR2D;
    return v;
}

void vnull(vector3D *v)
{
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

void vnull(vector2D *v)
{
    v->x = 0;
    v->y = 0;
}
