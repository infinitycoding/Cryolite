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



class Shader
{
    public:
        Shader();
        Shader(const char *filename, ShaderType kind);
        ~Shader();

        bool loadShader(const char *filename, ShaderType kind);
        bool activate();
        void deactivate();

    protected:
        void initShader();

        int getFileLength(const char *filename);
        char *loadASCIIFile(const char *filename);

        bool setType(ShaderType kind);

        bool unloadASCIIFileBuffer(char *buffer);
        bool unloadShaderObject(GLuint obj);


        GLuint program;

        char *fileBuffer;
        int len;
        GLuint shaderObject;
        ShaderType type;


};



#endif
