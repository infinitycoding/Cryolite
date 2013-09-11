#ifndef SHADER_H_INCLUDED       // as a programmer you shout know what these two lines do
#define SHADER_H_INCLUDED       // if you don't: they prevent a double including of this header file



/****************************************************************************
 *                                                                          *
 *                              Shader-Module                               *
 *                              -------------                               *
 *                                                                          *
 * Contains the shader-class and a few types used by it.                    *
 * With the shader-class you can load, compile and link shaders.            *
 *                                                                          *
 * Useage: Write a vertex-shader and a fragment-shader.                     *
 * Put them in files. Create an instance of the shader-class.               *
 * Now load, compile and the to shader-files with the                       *
 * standart-constructor or with loadShader() and make().                    *
 * Activate the shader with activate(), deactivate it with deactivate().    *
 *                                                                          *
 * Author: Peter Hösch                                                      *
 * Date: 19.08.2013                                                         *
 *                                                                          *
 ****************************************************************************/



#define GL_GLEXT_PROTOTYPES     // this define is needed to make the preprocessor beleaving me that i have the right opengl version (don't ask me why)


#include <GL/gl.h>              // gl.h is needed for the standart gl things (GLuint etc...)
#include <SDL/SDL_opengl.h>     // SDL_opengl.h is needed for some extended shader functions




enum ShaderType             // an enum of shader types (it brings the defines of opengl in one structure)
{
    vertexShader = GL_VERTEX_SHADER,                            // vertex shader affect all drawn vertices
    vertexShaderARB = GL_VERTEX_SHADER_ARB,                     // the same as the normal vertex shader, but opengl has two definitions so i have two too
    fragmentShader = GL_FRAGMENT_SHADER,                        // fragment shaders affect fragments (a fragment is a pixel before it is on the screen)
    fragmentShaderARB = GL_FRAGMENT_SHADER_ARB,                 // the same as the normal fragment shader, but opengl has two definitions so i have two too
    geometryShader = GL_GEOMETRY_SHADER,                        // geometry shaders can add new geometry to the scene
    tesselationControlShader = GL_TESS_CONTROL_SHADER,          // don't ask what this is
    tesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,    // don't ask what this is
    undefined = 0,                                              // i wanted to have a value with which i can initialize it
    other = 0                                                   // the value my program sets the shaderType automatically if it has a different value than the ones above
};


struct shaderObject         // a struct which stores all things one shader object (vertex or fragment shader) can have
{
    char *fileBuffer;       // the uncompiled shader as an loaded ascii-file
    int fileLen;            // the length of the file (opengl want's to know this=
    GLuint object;          // the id of the shader object
    ShaderType type;        // the type of the shader object
};



class Shader                // a class which stores all things and functions one program object (vertex and fragment shader) has
{
    public:
        Shader();                                               // the zero-constructor
        Shader(const char *vsfile, const char *fsfile);      // the standart constructor (it needs the name of the two  shader files)
        ~Shader();                                              // the destructor

        bool loadShader(const char *filename, ShaderType kind);     // the load function you have to use if you created the shader with the zero
                                                                      //constructor (loads a shader object, needs the filename and the type)
                                                                      // in fact this is a surface to the other load function

        bool make();                                            // this function links the two shader objects with the program object after both are loaded

        bool activate();                                        // a function which activates the shader
        void deactivate();                                      // a function which deactivates all shaders

    protected:
        void initShader();                                      // a init function which contains the things which are the same in all constructors

        bool loadShader(const char *filename, shaderObject *shaderObj, ShaderType kind);    // the load function which is used by the other load function and the standart constructor
                                                                                              // in addition to the parameters of other load function it needs a pointer to a shader object
                                                                                              // (and really loads a shader instead of starting an other funtion to do this)

        int getFileLength(const char *filename);                // a help function to loadASCIIFile, needs a filename and returns the length of the file
        char *loadASCIIFile(const char *filename, int &len);   // a help function to loadShader, loads a ASCII-file, needs the filename and a referance to a int-variable to store the length. it returns a pointer to the file buffer

        bool setType(ShaderType &typevar, ShaderType newType);      // a function which sets a shadertype-var to a shadertype and returns if the shadertype is supported or not

        bool unloadASCIIFileBuffer(char *buffer);       // a function to unload the file buffer loaded with loadASCIIFile. needs a pointer to the buffer, returns if the operation was successfully or not.
        bool unloadShaderObject(GLuint obj);             // a function to unload a shader object. needs the id of the object, returns if the operation was successfully or not.


        GLuint program;                 // the id of the program object

        shaderObject *vertShader;       // the vertex shader
        shaderObject *fragShader;       // the fragment shader
};



#endif      // this #endif closes the #ifndef SHADER_H_INCLUDED at the top of this file
