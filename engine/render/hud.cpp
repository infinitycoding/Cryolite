

#include <hud.h>


HUD_Element::HUD_Element()
{
    position.x = 0;
    position.y = 0;
    size.x = 0;
    size.y = 0;
    glcontent = NULL;
}


HUD_Element::HUD_Element(vertex2D pos, float w, float h, Texture *tex)
{
    position = pos;
    size.x = w;
    size.y = h;
    glcontent = tex;
}


HUD_Element::HUD_Element(vertex2D pos, float w, float h, const char *texname)
{
    position = pos;
    size.x = w;
    size.y = h;
    glcontent = Material::TexCache->requestTexture(texname);
}


HUD_Element::HUD_Element(float x, float y, float w, float h, Texture *tex)
{
    position.x = x;
    position.y = y;
    size.x = w;
    size.y = h;
    glcontent = tex;
}


HUD_Element::HUD_Element(float x, float y, float w, float h, const char *texname)
{
    position.x = x;
    position.y = y;
    size.x = w;
    size.y = h;
    glcontent = Material::TexCache->requestTexture(texname);
}


HUD_Element::HUD_Element(vertex2D pos, vertex2D s, Texture *tex)
{
    position = pos;
    size = s;
    glcontent = tex;
}


HUD_Element::HUD_Element(vertex2D pos, vertex2D s, const char *texname)
{
    position = pos;
    size = s;
    glcontent = Material::TexCache->requestTexture(texname);
}


HUD_Element::HUD_Element(float x, float y, vertex2D s, Texture *tex)
{
    position.x = x;
    position.y = y;
    size = s;
    glcontent = tex;
}


HUD_Element::HUD_Element(float x, float y, vertex2D s, const char *texname)
{
    position.x = x;
    position.y = y;
    size = s;
    glcontent = Material::TexCache->requestTexture(texname);
}


HUD_Element::HUD_Element(HUD_Element *templateElement)
{
    this->position = templateElement->position;
    this->size = templateElement->size;
    this->glcontent = templateElement->glcontent;
}


HUD_Element::~HUD_Element()
{

}


success HUD_Element::renderElement()
{
    if(glcontent == NULL)
        return failture;

    GLuint tex = glcontent->nr;

    glBindTexture( GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);

        glTexCoord2i( 1,  0);
        glVertex2f(position.x, position.y);
        glTexCoord2i( 1,  1);
        glVertex2f(position.x, position.y + size.y);
        glTexCoord2i( 0,  1);
        glVertex2f(position.x + size.x, position.y + size.y);
        glTexCoord2i( 0,  0);
        glVertex2f(position.x + size.x, position.y);

    glEnd();

    return successful;
}

vertex2D HUD_Element::moveTo(vertex2D newPosition)
{
    return (position = newPosition);
}


vertex2D HUD_Element::getPosition()
{
    return position;
}


vertex2D HUD_Element::changeSize(vertex2D newSize)
{
    return (size = newSize);
}


vertex2D HUD_Element::getSize()
{
    return size;
}


Texture *HUD_Element::changeContent(Texture *tex)
{
    return (glcontent = tex);
}


Texture *HUD_Element::changeContent(const char *texname)
{
    return (glcontent = Material::TexCache->requestTexture(texname));
}


Texture *HUD_Element::getContent()
{
    return glcontent;
}


HUD::HUD()
{
    genScript = NULL;
    elements = new List<HUD_Element>;
}


HUD::HUD(const char *script, float w, float h)
{
    genScript = NULL;
    elements = new List<HUD_Element>;

    vertex2D res;
    res.x = w;
    res.y = h;

    loadHUD(script, res);
}


HUD::HUD(const char *script, vertex2D res)
{
    genScript = NULL;
    elements = new List<HUD_Element>;

    loadHUD(script, res);
}


HUD::HUD(HUD *templateHUD)
{
    elements = new List<HUD_Element>(templateHUD->elements);
}


HUD::~HUD()
{
    delete genScript;
    delete elements;
}



HUD_Element *HUD::addElement(HUD_Element *newElement)
{
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(vertex2D pos, float w, float h, Texture *tex)
{
    HUD_Element *newElement = new HUD_Element(pos, w, h, tex);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(vertex2D pos, float w, float h, const char *texname)
{
    HUD_Element *newElement = new HUD_Element(pos, w, h, texname);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(float x, float y, float w, float h, Texture *tex)
{
    HUD_Element *newElement = new HUD_Element(x, y, w, h, tex);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(float x, float y, float w, float h, const char *texname)
{
    HUD_Element *newElement = new HUD_Element(x, y, w, h, texname);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(vertex2D pos, vertex2D s, Texture *tex)
{
    HUD_Element *newElement = new HUD_Element(pos, s, tex);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(vertex2D pos, vertex2D s, const char *texname)
{
    HUD_Element *newElement = new HUD_Element(pos, s, texname);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(float x, float y, vertex2D s, Texture *tex)
{
    HUD_Element *newElement = new HUD_Element(x, y, s, tex);
    elements->PushFront(newElement);
    return newElement;
}


HUD_Element *HUD::addElement(float x, float y, vertex2D s, const char *texname)
{
    HUD_Element *newElement = new HUD_Element(x, y, s, texname);
    elements->PushFront(newElement);
    return newElement;
}


success HUD::render(int swidth, int sheight)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, swidth, sheight, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 0);

    if(elements != NULL)
    {
        ListIterator<HUD_Element> i = ListIterator<HUD_Element>(elements);
        i.SetFirst();

        while(!i.IsLast())
        {
            if(i.GetCurrent()->renderElement() == failture)
                return failture;

            i.Next();
        }
    }

    glBindTexture( GL_TEXTURE_2D, 0);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    return successful;
}


void HUD::loadHUD(const char *script, vertex2D res)
{
    genScript = new Script(script);

    genScript->insertGlobalNumber("width", res.x);
    genScript->insertGlobalNumber("height", res.y);

    genScript->run();

    lua_State *L = genScript->getTable("overlay");

    if(!istable(CURRENT_ELEMENT))
        return;

    foreach_element
    {
        if(!istable(CURRENT_ELEMENT))
        {
            lua_pop(L, 1);
            continue;
        }
            
        foreach_element
        {
            if(isnumber(CURRENT_ELEMENT))
                printf("number value: %d\n", LINT());
            else if(isstring(CURRENT_ELEMENT))
                printf("string value: %s\n", LSTR());
        }

        if(isobject(CURRENT_ELEMENT))
            lua_pop(L, 1);
    }
}
