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
    vertexShader = GL_VERTEX_SHADER, fragmentShader = GL_FRAGMENT_SHADER, geometryShader = GL_GEOMETRY_SHADER, undefined, other
};



class Shader
{
    public:
        Shader();
        Shader(const char *filename, ShaderType kind);
        ~Shader();

        bool loadShader(const char *filename, ShaderType kind);

    protected:
        void initShader();

        int getFileLength(const char *filename);
        char *loadASCIIFile(const char *filename);
        void unloadASCIIFileBuffer(char *buffer);

        bool setType(ShaderType kind);


        GLuint program;

        char *fileBuffer;
        int len;
        GLuint shaderObject;
        ShaderType type;


};



#endif
