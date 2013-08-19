#include <shader.h>



using namespace std;



Shader::Shader()
{
    initShader();
}


Shader::Shader(const char *filename, ShaderType kind)
{
    initShader();

    if(!loadShader(filename, kind))
        cerr << "error: unable to load shader " << filename << " ." << endl;
}


Shader::~Shader()
{
    unloadASCIIFileBuffer(fileBuffer);
    unloadShaderObject(shaderObject);
}


bool Shader::loadShader(const char *filename, ShaderType kind)
{
    if(!setType(kind))
        return false;

    fileBuffer = loadASCIIFile(filename);

    if(fileBuffer == NULL)
        return false;


    shaderObject = glCreateShader(kind);

    glShaderSourceARB(shaderObject, 1, (const char **)&fileBuffer, &len);

    glCompileShaderARB(shaderObject);

    program = glCreateProgram();

    glAttachShader(program, shaderObject);

    glLinkProgram(program);

    return true;
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

    fileBuffer = NULL;
    len = 0;
    shaderObject = 0;
    type = undefined;
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


char *Shader::loadASCIIFile(const char *filename)
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


bool Shader::setType(ShaderType kind)
{
    if(kind == vertexShader || kind == fragmentShader)    // types i know and like
    {
        type = kind;
        return true;
    }
    else if(kind == geometryShader || kind == tesselationControlShader || kind == tesselationEvaluationShader || kind == undefined)   // types i know and don't like
    {
        type = kind;
        return false;
    }
    else    // types i don't know
    {
        type = other;
        return false;
    }
}
