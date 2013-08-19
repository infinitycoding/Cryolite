#include <shader.h>



using namespace std;



Shader::Shader()
{
    initShader();
}


Shader::Shader(const char *vsfile, const char *fsfile)
{
    initShader();

    if(!loadShader(vsfile, vertShader, vertexShader))
        cerr << "error: unable to load shader " << vsfile << " ." << endl;

    if(!loadShader(fsfile, fragShader, fragmentShader))
        cerr << "error: unable to load shader " << fsfile << " ." << endl;

    make();
}


Shader::~Shader()
{
    unloadASCIIFileBuffer(vertShader->fileBuffer);
    unloadShaderObject(vertShader->object);
    delete vertShader;

    unloadASCIIFileBuffer(fragShader->fileBuffer);
    unloadShaderObject(fragShader->object);
    delete fragShader;
}


bool Shader::loadShader(const char *filename, shaderObject *shaderObj, ShaderType kind)
{
    if(!setType(shaderObj->type, kind))
        return false;

    shaderObj->fileBuffer = loadASCIIFile(filename, shaderObj->fileLen);

    if(shaderObj->fileBuffer == NULL)
        return false;


    shaderObj->object = glCreateShader(kind);

    glShaderSourceARB(shaderObj->object, 1, (const char **)&shaderObj->fileBuffer, &shaderObj->fileLen);

    glCompileShaderARB(shaderObj->object);

    return true;
}


void Shader::make()
{
    program = glCreateProgram();

    if(vertShader->object)
        glAttachShader(program, vertShader->object);

    if(fragShader->object)
        glAttachShader(program, fragShader->object);

    glLinkProgram(program);
}


bool Shader::activate()
{
    if(program == 0)
        return false;

    glUseProgram(program);

    return true;
}


void deactivate()
{
    glUseProgram(0);
}


void Shader::initShader()
{
    program = 0;

    vertShader = new shaderObject;
    vertShader->fileBuffer = NULL;
    vertShader->fileLen = 0;
    vertShader->object = 0;
    vertShader->type = undefined;

    fragShader = new shaderObject;
    fragShader->fileBuffer = NULL;
    fragShader->fileLen = 0;
    fragShader->object = 0;
    fragShader->type = undefined;

}


int Shader::getFileLength(const char *filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if(!file)
        return 0;

    file.seekg(0, ios::end);
    int len = file.tellg();

    return len;
}


char *Shader::loadASCIIFile(const char *filename, int &len)
{
    unsigned int i = 0;
    char *buffer = NULL;
    ifstream file;

    file.open(filename, ios::in);

    if(!file)
        return NULL;

    len = getFileLength(filename);

    if(len == 0)
        return NULL;

    buffer = new char[len+1];

    if(buffer == NULL)
        return NULL;

    buffer[len] = '\0';

    while(file.good())
    {
        buffer[i] = file.get();
        if (!file.eof())
            i++;
    }

    buffer[i] = '\0';

    file.close();

    return buffer;
}


bool Shader::unloadASCIIFileBuffer(char *buffer)
{
    if(buffer != NULL)
    {
        delete[] buffer;
        buffer = NULL;
        return true;
    }
    else
    {
        return false;
    }
}


bool Shader::unloadShaderObject(GLuint obj)
{
    if(obj == 0)
        return false;

    glDeleteShader(obj);

    return true;
}


bool Shader::setType(ShaderType &typevar, ShaderType newType)
{
    if(newType == vertexShader || newType == fragmentShader)    // types i know and like
    {
        typevar = newType;
        return true;
    }
    else if(newType == geometryShader || newType == tesselationControlShader || newType == tesselationEvaluationShader || newType == undefined)   // types i know and don't like
    {
        cerr << "warning: chosen shader-type is not supported by cryolite engine yet." << endl;

        typevar = newType;
        return false;
    }
    else    // types i don't know
    {
        cerr << "warning: chosen shader-type is not known." << endl;

        typevar = other;
        return false;
    }
}
