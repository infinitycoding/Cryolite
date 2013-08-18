#include <shader.h>



using namespace std;



Shader::Shader()
{
    initShader();
}


Shader::Shader(const char *filename, ShaderType kind)
{
    initShader();

    fileBuffer = loadASCIIFile(filename);

    if(fileBuffer == NULL)
    {
        cerr << "error: unable to load file " << filename << " ." << endl;
        return;
    }

    type = kind;
}


Shader::~Shader()
{
    unloadASCIIFileBuffer(fileBuffer);
}


void Shader::initShader()
{
    fileBuffer = NULL;
    shaderObject = 0;
    type = undefined;
}


unsigned long Shader::getFileLength(const char *filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if(!file)
        return 0;

    file.seekg(0, ios::end);
    unsigned long len = file.tellg();

    return len;
}


char *Shader::loadASCIIFile(const char *filename)
{
    unsigned int i = 0;
    unsigned int len = 0;
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
