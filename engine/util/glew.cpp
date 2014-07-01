#include <glew.h>


GLEW::GLEW()
{
    error = glewInit();

    version = (error == GLEW_OK) ? glewGetString(GLEW_VERSION) : NULL;
}


GLEW::~GLEW()
{

}


GLenum GLEW::loadingSuccess()
{
    return error;
}


const unsigned char *GLEW::getVersion()
{
    return version;
}


bool GLEW::checkExtention(const char *name)
{
    return glewIsSupported(name);
}
