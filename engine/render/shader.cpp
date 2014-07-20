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

#include <shader.h>

#include <iostream>
#include <fstream>



using namespace std;



ShaderObject::ShaderObject()
{
    initShaderObject();
}


ShaderObject::ShaderObject(const char *filename, ShaderType kind)
{
    initShaderObject();

    if(!loadShader(filename, kind))
        cerr << "error: unable to load shader " << filename << "." << endl;
}


ShaderObject::~ShaderObject()
{
    if(fileBuffer != NULL)
        unloadASCIIFileBuffer(fileBuffer);

    if(object != 0)
        unloadShaderObject(object);
}


bool ShaderObject::loadShader(const char *filename, ShaderType kind)
{
    if(!setType(type, kind))
    {
        status = typeRejected;
        return false;
    }

    status = typeAccepted;

    fileBuffer = loadASCIIFile(filename, fileLen);

    if(fileBuffer == NULL)
    {
        status = fileLoadFailed;
        return false;
    }

    status = fileLoadSuccess;

    object = glCreateShader(kind);

    if(object == 0)
    {
        status = objectCreateFailed;
        return false;
    }

    status = objectCreateSuccess;

    glShaderSourceARB(object, 1, (const char **)&fileBuffer, &fileLen);

    glCompileShaderARB(object);

    glGetObjectParameterivARB(object, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);

    if(compileStatus == true)
    {
        cout << "shader " << object << " " << filename << " loaded and compiled. (shader object)" << endl;
        status = compilationSuccess;
        return true;
    }
    else
    {
        cerr << "error: failed to compile shader " << object << "." << endl;
        status = compilationFailed;
        return false;
    }
}


ShaderState ShaderObject::getStatus()
{
    return status;
}


GLuint ShaderObject::getObject()
{
    return object;
}


void ShaderObject::initShaderObject()
{
    fileBuffer = NULL;
    fileLen = 0;
    object = 0;
    type = undefined;
    compileStatus = 0;
    status = notLoadedYet;
}


int ShaderObject::getFileLength(const char *filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if(!file)
        return 0;

    file.seekg(0, ios::end);
    int len = file.tellg();

    file.close();

    return len;
}


char *ShaderObject::loadASCIIFile(const char *filename, int &len)
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

    file.close();                   // close the file

    return buffer;
}


bool ShaderObject::setType(ShaderType &typevar, ShaderType newType)
{
    if(newType == vertexShader || newType == vertexShaderARB || newType == fragmentShader || newType == fragmentShaderARB)
    {
        typevar = newType;
        return true;
    }
    else if(newType == geometryShader || newType == tesselationControlShader || newType == tesselationEvaluationShader)
    {
        cerr << "warning: chosen shader-type is not supported by cryolite engine yet." << endl;

        typevar = newType;
        return false;
    }
    else
    {
        cerr << "warning: chosen shader-type is not known." << endl;

        typevar = other;
        return false;
    }
}


bool ShaderObject::unloadASCIIFileBuffer(char *&buffer)
{
    if(buffer == NULL)
    {
        return false;
    }
    else
    {
        delete[] buffer;
        buffer = NULL;
        return true;
    }
}


bool ShaderObject::unloadShaderObject(GLuint obj)
{
    if(obj == 0)
       return false;

    glDeleteShader(obj);

    return true;
}





Shader::Shader()
{
    initShader();
}


Shader::Shader(const char *vsfile, const char *fsfile)
{
    bool fail = false;

    initShader();

    if(!vertShader->loadShader(vsfile, vertexShader))
    {
        cerr << "error: unable to load shader " << vsfile << "." << endl;
        fail = true;
    }

    if(!fragShader->loadShader(fsfile, fragmentShader))
    {
        cerr << "error: unable to load shader " << fsfile << "." << endl;
        fail = true;
    }

    if(!fail)
        make();
}


Shader::~Shader()
{
   if(program != 0)
        glDeleteProgram(program);

    if(vertShader != NULL)
        delete vertShader;

    if(fragShader != NULL)
        delete fragShader;
}


bool Shader::loadShader(const char *filename, ShaderType kind)
{
    if(kind == vertexShader || kind == vertexShaderARB)
    {
        if(!vertShader->loadShader(filename, kind))
        {
            cerr << "error: unable to load shader " << filename << " ." << endl;
            return false;
        }
    }
    else if(kind == fragmentShader || kind == fragmentShaderARB)
    {
        if(!fragShader->loadShader(filename, kind))
        {
            cerr << "error: unable to load shader " << filename << " ." << endl;
            return false;
        }
    }
    else
    {
        cerr << "error: tryed to load a shader of an unknown or unsupported type." << endl;
        return false;
    }

    return true;
}


bool Shader::make()
{
    if(vertShader->getStatus() != compilationSuccess || fragShader->getStatus() != compilationSuccess || program == 0)
        return false;

    glAttachShader(program, vertShader->getObject());
    glAttachShader(program, fragShader->getObject());

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


void Shader::deactivate()
{
    glUseProgram(0);
}


void Shader::initShader()
{
    program = glCreateProgram();

    cout << "shader " << program << " created. (program object)" << endl;

    vertShader = new ShaderObject();
    fragShader = new ShaderObject();
}

