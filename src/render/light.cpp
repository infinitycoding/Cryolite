#include <light.h>

GLfloat defaultAmbience[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat defaultDiffuse[]   = {1.0, 1.0, 1.0, 1.0};
GLfloat defaultSpecular[]  = {1.0, 1.0, 1.0, 1.0};
GLfloat defaultPosition[]  = {0.0, 0.0, 1.0, 0.0};
GLfloat defaultDirection[] = {0.0, 0.0, -1.0};
GLfloat defaultExponent    =  0.0;
GLfloat defaultCutof       =  180.0 ;

GlobalLight::GlobalLight()
{
    ambient[0] = 1.0;
    ambient[1] = 1.0;
    ambient[2] = 1.0;
    ambient[3] = 1.0;

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}


GlobalLight::GlobalLight(GLfloat ambientRed, GLfloat ambientGreen, GLfloat ambientBlue, GLfloat ambientTransparency )
{
    ambient[0] = ambientRed;
    ambient[1] = ambientGreen;
    ambient[2] = ambientBlue;
    ambient[3] = ambientTransparency;

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}

void GlobalLight::activateLight()
{
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
}

GlobalLight::~GlobalLight()
{
    glDisable(GL_LIGHTING);
}

Lamp::Lamp()
{
    //get Lamp number
    setStandart();
}

Lamp::~Lamp()
{
    // remove lamp from Lamplist
    // disable it
}


Lamp::Lamp(Lamp *L)
{
    //get lamp number
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
        position[i]  = L->position[i];
        direction[i] = L->direction[i];
    }

    exponent = L->exponent;
    cutof = L->cutof;
    attType = L->attType;
    attenaution = L->attenaution;
    activ = L->activ;
}


Lamp::Lamp(Lamp *L, vector pos)
{
    //get lamp number
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
        direction[i] = L->direction[i];
    }

    position[0]  = pos.x;
    position[1]  = pos.y;
    position[2]  = pos.z;

    exponent = L->exponent;
    cutof = L->cutof;
    attType = L->attType;
    attenaution = L->attenaution;
    activ = L->activ;
}


Lamp::Lamp(Lamp *L, vector *pos)
{
    //get lamp number
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
        direction[i] = L->direction[i];
    }

    position[0]  = pos->x;
    position[1]  = pos->y;
    position[2]  = pos->z;

    exponent = L->exponent;
    cutof = L->cutof;
    attType = L->attType;
    attenaution = L->attenaution;
    activ = L->activ;
}

Lamp::Lamp(Lamp *L, vector pos, vector dir)
{
    //get lamp number
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
    }

    position[0]  = pos.x;
    position[1]  = pos.y;
    position[2]  = pos.z;
    position[3]  = 0;

    direction[0]  = dir.x;
    direction[1]  = dir.y;
    direction[2]  = dir.z;

    exponent = L->exponent;
    cutof = L->cutof;
    attType = L->attType;
    attenaution = L->attenaution;
    activ = L->activ;
}

Lamp::Lamp(Lamp *L, vector *pos, vector *dir)
{
    //get lamp number
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
    }

    position[0]  = pos->x;
    position[1]  = pos->y;
    position[2]  = pos->z;
    position[3]  = 0;

    direction[0]  = dir->x;
    direction[1]  = dir->y;
    direction[2]  = dir->z;

    exponent = L->exponent;
    cutof = L->cutof;
    attType = L->attType;
    attenaution = L->attenaution;
    activ = L->activ;
}


void Lamp::setAmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = t;
}

void Lamp::setDiffuseLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = t;
}

void Lamp::setSpecularLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = t;
}

void Lamp::setAmbientLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        ambient[i] = L[i];
    }
}

void Lamp::setDiffuseLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        diffuse[i] = L[i];
    }
}

void Lamp::setSpecularLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        specular[i] = L[i];
    }
}

void Lamp::setDirection(vector d)
{

    if(d.x || d.y || d.z)
        position[3] = 1;
    else
        position[3] = 0;

    direction[0] = d.x;
    direction[1] = d.y;
    direction[2] = d.z;
}

void Lamp::setDirection(vector *d)
{
    if(d->x || d->y || d->z)
        position[3] = 1;
    else
        position[3] = 0;

    direction[0] = d->x;
    direction[1] = d->y;
    direction[2] = d->z;
}

void Lamp::setDirection(GLfloat *L)
{
    if(L[0] || L[1] || L[2])
        position[3] = 1;
    else
        position[3] = 0;

    for(int i = 0; i< 3; i++)
    {
        direction[i] = L[i];
    }
}


void Lamp::setPosition(vector p)
{
    position[0] = p.x;
    position[1] = p.y;
    position[2] = p.z;
}


void Lamp::setPosition(vector *p)
{
    position[0] = p->x;
    position[1] = p->y;
    position[2] = p->z;
}
void Lamp::setPosition(GLfloat *L)
{
    for(int i = 0; i< 3; i++)
    {
        position[i] = L[i];
    }
}

void Lamp::directed(bool b)
{
    if(b)
    {
        direction[3] = 0;
    }
    else
    {
        direction[3] = 1;
    }
}

bool Lamp::isDirected(void)
{
    if(direction[3])
        return false;
    return true;
}


void Lamp::setStandart()
{
    setAmbientLight(defaultAmbience);
    setDiffuseLight(defaultDiffuse);
    setSpecularLight(defaultSpecular);
    setDirection(defaultDirection);
    setPosition(defaultPosition);
    exponent = defaultExponent;
    cutof = defaultCutof;
}
