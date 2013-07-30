#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED



#include <SDL.h>

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <vector.h>
#include <vertex.h>


#define MAX_LINELENGTH 30



class BasicParser
{
    public:
        BasicParser();
        virtual ~BasicParser();

        char *getValueString(const char *line, char *string);
        float getValueFloat(const char *line);
        double getValueDouble(const char *line);
        short getValueShort(const char *line);
        int getValueInt(const char *line);
        long getValueLong(const char *line);
        bool getValueBool(const char *line);
        SDL_Color getValueColor(const char *line);
        vector getValueVector(const char *line);
        Vertex3D getValueVertex3D(const char *line);
        Vertex2D getValueVertex2D(const char *line);
};


#endif
