#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#define GL_GLEXT_PROTOTYPES



#include <GL/gl.h>
#include <SDL/SDL_opengl.h>

#include <iostream>
#include <fstream>

#include <general_def.h>


enum ShaderType
{
    vertexShader = GL_VERTEX_SHADER,
    fragmentShader = GL_FRAGMENT_SHADER,
    geometryShader = GL_GEOMETRY_SHADER,
    tesselationControlShader = GL_TESS_CONTROL_SHADER,
    tesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,
    undefined = 0,
    other = 0
};


struct shaderObject
{
    char *fileBuffer;
    int fileLen;
    GLuint object;
    ShaderType type;
};



class Shader
{
    public:
        Shader();
        Shader(const char *vsfile, const char *fsfile);
        ~Shader();

        bool loadShader(const char *filename, shaderObject *shaderObj, ShaderType kind);
        void make();

        bool activate();
        void deactivate();

    protected:
        void initShader();

        int getFileLength(const char *filename);
        char *loadASCIIFile(const char *filename, int &len);

        bool setType(ShaderType &typevar, ShaderType newType);

        bool unloadASCIIFileBuffer(char *buffer);
        bool unloadShaderObject(GLuint obj);


        GLuint program;

        shaderObject *vertShader;
        shaderObject *fragShader;
};



#endif
