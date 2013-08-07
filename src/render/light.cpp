#include <light.h>

GLfloat defaultAmbience[]  = {0.0, 0.0, 0.0, 1.0};
GLfloat defaultDiffuse[]   = {1.0, 1.0, 1.0, 1.0};
GLfloat defaultSpecular[]  = {1.0, 1.0, 1.0, 1.0};
GLfloat defaultPosition[]  = {0.0, 0.0, 1.0, 0.0};
GLfloat defaultDirection[] = {0.0, 0.0, -1.0};
GLfloat defaultExponent    =  0.0;
GLfloat defaultCutof       =  180.0 ;


LightManager::LightManager()
{
    lightNums = new List<GLint>();
    numCounter = 0;
}

LightManager::~LightManager()
{
    for(int i = 0; i<numCounter; i++)
    {
        ListIterator<GLint> I = *ListIterator<GLint>(lightNums).SetFirst();
        while(!I.IsLast())
        {
            if(*I.GetCurrent() == i)
                break;
            I.Next();
        }

        if(*I.GetCurrent() != i)
            glDisable(GL_LIGHT0+i);
    }
    delete lightNums;
}

GLint LightManager::getLightNum()
{
    if(lightNums->IsEmpty())
    {
        if(numCounter <= GL_MAX_LIGHTS)
            return GL_LIGHT0+numCounter++;
        else
        {
            cerr << "Too many lights in the scene. This will overwrite Lamp 0"<<endl;
            return GL_LIGHT0;
        }
    }
    else
    {
        GLint *num = lightNums->PopFront();
        GLint r = *num;
        delete num;
        return r;
    }
}

void LightManager::returnLightNum(GLint n)
{
    if(numCounter-1 == n)
    {
        numCounter--;
        ListIterator<GLint> I = *ListIterator<GLint>(lightNums).SetFirst();
        while(!I.IsLast())
        {
            if(*I.GetCurrent() == numCounter-1)
            {
                numCounter--;
                I.Destroy();
                I.SetFirst();
            }
            else
            {
                I.Next();
            }

        }
        return;
    }
    else
    {
        GLint *v = new GLint;
        *v = n;
        lightNums->PushFront(v);
    }
}



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
    setStandart();
    modified = true;
    reg = false;
    activ = false;
}

Lamp::~Lamp()
{
    if(reg)
        glDisable(Lightnum);
}


Lamp::Lamp(Lamp *L)
{
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
        position[i]  = L->position[i];
        direction[i] = L->direction[i];
    }
    localPosition = L->localPosition;
    exponent = L->exponent;
    cutof = L->cutof;
    ConstAttenaution = L->ConstAttenaution;
    LinAttenaution = L->LinAttenaution;
    QuadAttenaution = L->QuadAttenaution;
    activ = L->activ;
    modified = true;
    reg = false;
    activ = L->activ;
    relativeToObject = L->relativeToObject;
    relativeToLamp = L->relativeToLamp;
    rel = L->rel;
}


Lamp::Lamp(Lamp *L, vector pos)
{
    for(int i = 0; i < 4; i++)
    {
        ambient[i]   = L->ambient[i];
        diffuse[i]   = L->diffuse[i];
        specular[i]  = L->specular[i];
        position[i]  = L->position[i];
        direction[i] = L->direction[i];
    }
    position[0] = pos.x;
    position[1] = pos.y;
    position[2] = pos.z;
    localPosition = pos;
    exponent = L->exponent;
    cutof = L->cutof;
    ConstAttenaution = L->ConstAttenaution;
    LinAttenaution = L->LinAttenaution;
    QuadAttenaution = L->QuadAttenaution;
    activ = L->activ;
    modified = true;
    reg = false;
    activ = L->activ;
    relativeToObject = L->relativeToObject;
    relativeToLamp = L->relativeToLamp;
    rel = L->rel;
}



void Lamp::setAmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = t;

    if(reg)
    {
        glLightfv(Lightnum, GL_AMBIENT,  ambient);
    }
    else
        modified = true;
}

void Lamp::setDiffuseLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = t;

    if(reg)
    {
        glLightfv(Lightnum, GL_DIFFUSE,  diffuse);
    }
    else
        modified = true;
}

void Lamp::setSpecularLight(GLfloat r, GLfloat g, GLfloat b, GLfloat t)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = t;

    if(reg)
    {
        glLightfv(Lightnum, GL_SPECULAR,  specular);
    }
    else
        modified = true;
}

void Lamp::setAmbientLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        ambient[i] = L[i];
    }

    if(reg)
    {
        glLightfv(Lightnum, GL_AMBIENT,  ambient);
    }
    else
        modified = true;
}

void Lamp::setDiffuseLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        diffuse[i] = L[i];
    }

    if(reg)
    {
        glLightfv(Lightnum, GL_DIFFUSE,  diffuse);
    }
    else
        modified = true;
}

void Lamp::setSpecularLight(GLfloat *L)
{
    for(int i = 0; i < 4 ; i++)
    {
        specular[i] = L[i];
    }

    if(reg)
    {
        glLightfv(Lightnum, GL_SPECULAR,  specular);
    }
    else
        modified = true;
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

    if(reg)
    {
        glLightfv(Lightnum, GL_SPOT_DIRECTION, direction);
    }
    else
        modified = true;
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

    if(reg)
    {
        glLightfv(Lightnum, GL_SPOT_DIRECTION, direction);
    }
    else
        modified = true;
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

    if(reg)
    {
        glLightfv(Lightnum, GL_SPOT_DIRECTION, direction);
    }
    else
        modified = true;
}


void Lamp::setPosition(vector p)
{
    localPosition.setvalue(p);

    position[0] = getPosition().x;
    position[1] = getPosition().y;
    position[2] = getPosition().z;

    if(reg)
    {
        glLightfv(Lightnum, GL_POSITION, position);
    }
    else
        modified = true;
}


void Lamp::setPosition(vector *p){setPosition(*p);}



void Lamp::setPosition(GLfloat *L)
{
    for(int i = 0; i< 3; i++)
    {
        position[i] = L[i];
    }

    if(reg)
    {
        glLightfv(Lightnum, GL_POSITION, position);
    }
    else
        modified = true;
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

    if(reg)
    {
        glLightfv(Lightnum, GL_SPOT_DIRECTION, direction);
    }
    else
        modified = true;
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
    ConstAttenaution = 1;
    LinAttenaution = 0;
    QuadAttenaution = 0;
    rel = none;
    relativeToObject = NULL;
    relativeToLamp = NULL;
    localPosition = vector();
    if(reg)
        refresh();
    else
        modified = true;
}

void Lamp::refresh()
{
    if(reg)
    {
        refreshPosition();
        glLightfv(Lightnum, GL_AMBIENT,  ambient);
        glLightfv(Lightnum, GL_DIFFUSE,  diffuse);
        glLightfv(Lightnum, GL_SPECULAR,  specular);
        glLightfv(Lightnum, GL_SPOT_DIRECTION, direction);
        glLightf(Lightnum, GL_SPOT_EXPONENT, exponent);
        glLightf(Lightnum, GL_SPOT_CUTOFF, cutof);
        glLightf(Lightnum, GL_CONSTANT_ATTENUATION, ConstAttenaution);
        glLightf(Lightnum, GL_LINEAR_ATTENUATION, LinAttenaution);
        glLightf(Lightnum, GL_QUADRATIC_ATTENUATION, QuadAttenaution);
        modified = false;
        if(activ)
            glEnable(Lightnum);
        else
            glDisable(Lightnum);

    }
    else
    {
        modified = true;
        cerr << "WARNING: LightRefresh called without registration" <<endl;
    }

}


void Lamp::setExponent(GLfloat e)
{
    exponent = e;
    if(reg)
        glLightf(Lightnum, GL_SPOT_EXPONENT, e);
    else
        modified = true;
}

void Lamp::setCutOf(GLfloat c)
{
    cutof = c;
    if(reg)
        glLightf(Lightnum, GL_SPOT_CUTOFF, c);
    else
        modified = true;
}

void Lamp::setConstAttenaution(GLfloat a)
{
    ConstAttenaution = a;
    if(reg)
        glLightf(Lightnum, GL_CONSTANT_ATTENUATION, a);
    else
        modified = true;
}

void Lamp::setLinAttenaution(GLfloat a)
{
    LinAttenaution = a;
    if(reg)
        glLightf(Lightnum, GL_LINEAR_ATTENUATION, a);
    else
        modified = true;
}

void Lamp::setQuadAttenaution(GLfloat a)
{
    QuadAttenaution = a;
    if(reg)
        glLightf(Lightnum, GL_QUADRATIC_ATTENUATION, a);
    else
        modified = true;
}

void Lamp::refreshPosition(void)
{
        position[0] = getPosition().x;
        position[1] = getPosition().y;
        position[2] = getPosition().z;

    if(reg)
        glLightfv(Lightnum, GL_POSITION, position);
    else
        modified = true;
}

void Lamp::activate()
{
    activ = true;
    if(reg)
        glEnable(Lightnum);
    else
        modified = true;
}

void Lamp::deactivate()
{
    activ = false;
    if(reg)
        glDisable(Lightnum);
    else
        modified = true;
}

vector Lamp::getPosition()
{
    switch(rel)
    {
        case none:
            return vector(localPosition);
        break;

        case lamp:
            return vector(relativeToLamp->getPosition()+vector(localPosition));
        break;

        case object:
            return vector(relativeToObject->getPosition()+vector(localPosition));
        break;
    };

    return vector();
}


relativt_t Lamp::getRelation()
{
    return rel;
}

void Lamp::setRelation(Object *o)
{
    rel = object;
    relativeToObject = o;
}

void Lamp::setRelation(Lamp *l)
{
    rel = lamp;
    relativeToLamp = l;
}
