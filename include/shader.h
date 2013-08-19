#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED



#include <GL/gl.h>
#include <GL/glu.h>

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

        unsigned long getFileLength(const char *filename);
        char *loadASCIIFile(const char *filename);
        void unloadASCIIFileBuffer(char *buffer);


        char *fileBuffer;
        GLuint shaderObject;
        ShaderType type;
};



#endif
