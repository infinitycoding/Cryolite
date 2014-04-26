#include <hud.h>



HUD_Element::HUD_Element()
{
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;
    sdlcontent = NULL;
    source = renderNOT;
}


HUD_Element::HUD_Element(vertex2D pos, float w, float h, Texture *tex, SDL_Surface *c, renderSource s)
{
    position = pos;
    width = w;
    height = h;
    glcontent = tex;
    sdlcontent = c;
    source = s;
}


HUD_Element::HUD_Element(HUD_Element *templateElement)
{
    this->position = templateElement->position;
    this->width = templateElement->width;
    this->height = templateElement->height;
    this->glcontent = templateElement->glcontent;
    this->sdlcontent = templateElement->sdlcontent;
    this->source = templateElement->source;
}


void HUD_Element::renderElement()
{
    renderElement(source);
}


void HUD_Element::renderElement(renderSource type)
{
    if(type == renderNOT)
        return;

    GLuint tex = type == renderGL ? glcontent->nr : SDL::surfToTexture(sdlcontent);

    glBindTexture( GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);

        glTexCoord2i( 1,  0);
        glVertex2f(position.x, position.y);
        glTexCoord2i( 1,  1);
        glVertex2f(position.x, position.y + height);
        glTexCoord2i( 0,  1);
        glVertex2f(position.x + width, position.y + height);
        glTexCoord2i( 0,  0);
        glVertex2f(position.x + width, position.y);

    glEnd();
}


HUD::HUD()
{
    elements = new List<HUD_Element>;
}


HUD::HUD(const char *script)
{

}


HUD::HUD(HUD *templateHUD)
{
    elements = new List<HUD_Element>(templateHUD->elements);
}


void HUD::addElement(HUD_Element *newElement)
{
    elements->PushFront(newElement);
}


void HUD::render(int swidth, int sheight)
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
            i.GetCurrent()->renderElement();
            i.Next();
        }
    }

    glBindTexture( GL_TEXTURE_2D, 0);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
