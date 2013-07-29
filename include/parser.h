#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED



#include <iostream>
#include <cstring>
#include <cstdlib>


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
};


#endif
