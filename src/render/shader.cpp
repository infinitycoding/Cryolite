#include <shader.h>         // the header of this module

#include <iostream>         // iostream is needed for debug outputs
#include <fstream>          // fstream is needed for loading files.



using namespace std;        // because i don't want to write std:: hundred times



// the zero-constructor

Shader::Shader()
{
    initShader();       // just the standart initializations
}


// the standart constructor (it needs the name of the two  shader files)

Shader::Shader(const char *vsfile, const char *fsfile)
{
    bool fail = false;    // a flag which is set if something fails

    initShader();           // do the standart initializations

    if(!loadShader(vsfile, vertShader, vertexShader))       // try to load the vertex shader
    {
        cerr << "error: unable to load shader " << vsfile << " ." << endl;  // if it fails, print an error message
        fail = true;                                                        // and remember the failture
    }

    if(!loadShader(fsfile, fragShader, fragmentShader))
    {
        cerr << "error: unable to load shader " << fsfile << " ." << endl;  // if it fails, print an error message
        fail = true;                                                        // and remember the failture
    }

    if(!fail)   // if one of the shaders failed to load, it makes no sense to link them
        make(); // if we succeded, we can link the shader objects with the program object
}


// the destructor

Shader::~Shader()
{
    if(program != 0)       // check if there is a program object to delete
        glDeleteProgram(program);   // i hope this is the correct function

    if(vertShader != NULL)  // check if there is a vertex shader to delete (should always be, but i trust nobody)
    {
        if(vertShader->fileBuffer != NULL)                  // check if there is a file buffer to unload
            unloadASCIIFileBuffer(vertShader->fileBuffer);  // if yes, unload file buffer

        if(vertShader->object != 0)                         // check if there is a shader object to unload
            unloadShaderObject(vertShader->object);         // if yes, unload shader object

        delete vertShader;                                  // delete everything remaining of the vertex shader
    }

    if(fragShader != NULL)  // check if there is a fragment shader to delete (should always be, but i trust nobody)
    {
        if(fragShader->fileBuffer != NULL)                  // check if there is a file buffer to unload
            unloadASCIIFileBuffer(fragShader->fileBuffer);  // if yes, unload file buffer

        if(fragShader->object != 0)                         // check if there is a shader object to unload
            unloadShaderObject(fragShader->object);         // if yes, unload shader object

        delete fragShader;                                  // delete everything remaining of the vertex shader
    }
}


// the load function you have to use if you created the shader with the zero
//constructor (loads a shader object, needs the filename and the type)
// in fact this is a surface to the other load function

bool Shader::loadShader(const char *filename, ShaderType kind)
{
    if(kind == vertexShader)                // check if it's a vertex shader
    {
        if(!loadShader(filename, vertShader, kind))                                         // try to load the shader
        {
            cerr << "error: unable to load shader " << filename << " ." << endl;            // output a error message
            return false;   // tell the calling function it's an idiot
        }
    }
    else if(kind == fragmentShader)         // check if it's a fragment shader
    {
        if(!loadShader(filename, fragShader, kind))                                         // try to load the shader
        {
            cerr << "error: unable to load shader " << filename << " ." << endl;            // output a error message
            return false;   // tell the calling function it's an idiot
        }
    }
    else                                    // if it is no vertex shader and no fragment shader, we can't load it
    {
        cerr << "error: tryed to load a shader of an unknown or unsupported type." << endl;   // output a error message
        return false;       // tell the calling function it's an idiot
    }

    return true;            // tell the calling function everything went right
}


// this function links the two shader objects with the program object after both are loaded

bool Shader::make()
{
    if(vertShader->object == 0 || fragShader->object == 0)      // first we have to check if there are all needed shader objects
        return false;                                           // if not, we can't link them to the program object

    glAttachShader(program, vertShader->object);                // attach the vertex shader to the program object
    glAttachShader(program, fragShader->object);                // attach the fragment shader to the program object

    glLinkProgram(program);                                     // link the program object

    return true;                                                // job done!
}


// a function which activates the shader

bool Shader::activate()
{
    if(program == 0)            // check if there is a program object to activate
        return false;           // because we can't activate something not existing

    glUseProgram(program);      // activate the program object

    return true;                // job done!
}


// a function which deactivates all shaders

void deactivate()
{
    glUseProgram(0);            // if you use program 0, this means to deactivate all programs
}


// a init function which contains the things which are the same in all constructors

void Shader::initShader()
{
    program = glCreateProgram();        // create the program object

    cout << "shader " << program << " created. (program object)" << endl;   // tell the user the program object is created

    vertShader = new shaderObject;      // create the vertex shader struct
    vertShader->fileBuffer = NULL;      // set everything to zero
    vertShader->fileLen = 0;
    vertShader->object = 0;
    vertShader->type = undefined;

    fragShader = new shaderObject;      // create the fragment shader struct
    fragShader->fileBuffer = NULL;      // set erverthing to zero
    fragShader->fileLen = 0;
    fragShader->object = 0;
    fragShader->type = undefined;

}


// the load function which is used by the other load function and the standart constructor
// in addition to the parameters of other load function it needs a pointer to a shader object
// (and really loads a shader instead of starting an other funtion to do this)

bool Shader::loadShader(const char *filename, shaderObject *shaderObj, ShaderType kind)
{
    if(!setType(shaderObj->type, kind))     // check if the shader type is supported
        return false;

    shaderObj->fileBuffer = loadASCIIFile(filename, shaderObj->fileLen);    // load the shader file

    if(shaderObj->fileBuffer == NULL)               // check if the loading was successfully
        return false;


    shaderObj->object = glCreateShader(kind);       // create the opengl shader object

    glShaderSourceARB(shaderObj->object, 1, (const char **)&shaderObj->fileBuffer, &shaderObj->fileLen);            // attach the shader sourcecode with the shader object

    glCompileShaderARB(shaderObj->object);          // compile the shader

    cout << "shader " << shaderObj->object << " " << filename << " loaded and compiled. (shader object)" << endl;   // output a debug message

    return true;        // job done!
}


// a help function to loadASCIIFile, needs a filename and returns the length of the file

int Shader::getFileLength(const char *filename)
{
    ifstream file;                  // the file stream
    file.open(filename, ios::in);   // open the file stream

    if(!file)                       // check if it was a success
        return 0;

    file.seekg(0, ios::end);        // go to the end of the file
    int len = file.tellg();         // our position now is the lenght of the file

    file.close();                    // close the file

    return len;                     // return the length
}


// a help function to loadShader, loads a ASCII-file, needs the filename and a referance to a int-variable to store the length. it returns a pointer to the file buffer

char *Shader::loadASCIIFile(const char *filename, int &len)
{
    unsigned int i = 0;             // somewhere i must be defined
    char *buffer = NULL;            // the file buffer
    ifstream file;                  // the file stream

    file.open(filename, ios::in);   // open the stream

    if(!file)                       // look if the stream is open
        return NULL;                // if not, return

    len = getFileLength(filename);  // get the length of the file

    if(len == 0)                    // look if something is in the file
        return NULL;                // if not, return

    buffer = new char[len+1];       // allocate the buffer (size = the num of characters + zero-termination)

    if(buffer == NULL)              // look if the buffer is allocated
        return NULL;                // if not, return

    buffer[len] = '\0';             // secure is secure

    while(file.good())              // we read as long as we're not at the end of the file
    {
        buffer[i] = file.get();     // we always read one char to the buffer
        if (!file.eof())            // this is to don't terminate false
            i++;                    // increment the position counter
    }

    buffer[i] = '\0';               // terminate the string

    file.close();                   // close the file

    return buffer;                  // return a pointer to the buffer
}


// a function which sets a shadertype-var to a shadertype and returns if the shadertype is supported or not

bool Shader::setType(ShaderType &typevar, ShaderType newType)
{
    if(newType == vertexShader || newType == fragmentShader)    // types i know and like
    {
        typevar = newType;
        return true;
    }
    else if(newType == geometryShader || newType == tesselationControlShader || newType == tesselationEvaluationShader)   // types i know and don't like
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


// a function to unload the file buffer loaded with loadASCIIFile. needs a pointer to the buffer, returns if the operation was successfully or not.

bool Shader::unloadASCIIFileBuffer(char *buffer)
{
    if(buffer == NULL)      // if there is no buffer, i can't unload it
    {
        return false;       // tell the calling function it is an idiot
    }
    else
    {
        delete[] buffer;    // delete the buffer
        buffer = NULL;      // the prevent uninitialized pointers
        return true;        // tell the calling function that i succeeded
    }
}


// a function to unload a shader object. needs the id of the object, returns if the operation was successfully or not.

bool Shader::unloadShaderObject(GLuint obj)
{
    if(obj == 0)            // check if the shader object is loaded
        return false;      // if not, it cann't be unloaded

    glDeleteShader(obj);    // delete the shader object

    return true;            // operation successfully ended
}


