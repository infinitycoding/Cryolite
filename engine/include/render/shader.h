#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */


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
 * Date: 14.10.2013                                                         *
 *                                                                          *
 ****************************************************************************/



#define GL_GLEXT_PROTOTYPES


#include <GL/gl.h>
#include <SDL/SDL_opengl.h>



enum ShaderType
{
    vertexShader = GL_VERTEX_SHADER,
    vertexShaderARB = GL_VERTEX_SHADER_ARB,
    fragmentShader = GL_FRAGMENT_SHADER,
    fragmentShaderARB = GL_FRAGMENT_SHADER_ARB,
    geometryShader = GL_GEOMETRY_SHADER,
    tesselationControlShader = GL_TESS_CONTROL_SHADER,
    tesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,
    undefined = 0,
    other = 0
};


enum ShaderState
{
    notLoadedYet,
    typeAccepted,
    typeRejected,
    fileLoadSuccess,
    fileLoadFailed,
    objectCreateSuccess,
    objectCreateFailed,
    compilationSuccess,
    compilationFailed
};



class ShaderObject
{
    public:
        ShaderObject();
        ShaderObject(const char *filename, ShaderType kind);
        ~ShaderObject();

        bool loadShader(const char *filename, ShaderType kind);

        ShaderState getStatus();
        GLuint getObject();

    private:
        void initShaderObject();

        int getFileLength(const char *filename);
        char *loadASCIIFile(const char *filename, int &len);

        bool setType(ShaderType &typevar, ShaderType newType);

        bool unloadASCIIFileBuffer(char *&buffer);
        bool unloadShaderObject(GLuint obj);


        char *fileBuffer;
        int fileLen;
        GLuint object;
        ShaderType type;
        int compileStatus;
        ShaderState status;
};


class Shader
{
    public:
        Shader();
        Shader(const char *vsfile, const char *fsfile);
        ~Shader();

        bool loadShader(const char *filename, ShaderType kind);

        bool make();

        bool activate();
        void deactivate();

    protected:
        void initShader();


        GLuint program;

        ShaderObject *vertShader;
        ShaderObject *fragShader;
};



#endif
