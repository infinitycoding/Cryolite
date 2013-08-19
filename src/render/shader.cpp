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

    glUseProgram(program);

    return true;
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


void Shader::unloadASCIIFileBuffer(char *buffer)
{
    if(buffer != NULL)
    {
        delete[] buffer;
        buffer = NULL;
    }
}


bool Shader::setType(ShaderType kind)
{
    if(kind != vertexShader && kind != fragmentShader && kind != geometryShader)
    {
        type = other;
        return false;
    }
    else
    {
        type = kind;
        return true;
    }
}
