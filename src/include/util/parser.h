#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED



#include <SDL.h>

#include <iostream>
#include <cstring>

#include <vector.h>


#define MAX_LINELENGTH 40
#define NUMBER_STRING_SIZE 15


typedef struct charList
{
    int number;
    char *chars;
}charList;


class BasicParser
{
    public:
        BasicParser();
        virtual ~BasicParser();

        bool charInList(char character, const charList list);
        bool validNumber(char *string, bool allowFloat, bool allowSigned);

        char **skipCharacters(char **string, const charList characters);
        char **skipUntilCharacters(char **string, const charList characters);

        char *getString(char **instring, char *outstring, const charList endCharacters);

        bool getBool(char **string, const charList endCharacters);

        short getShort(char **string, const charList endCharacters);
        int getInt(char **string, const charList endCharacters);
        long getLong(char **string, const charList endCharacters);

        float getFloat(char **string, const charList endCharacters);
        double getDouble(char **string, const charList endCharacters);
};


class ExtParser : public BasicParser
{
    public:
        ExtParser();
        virtual ~ExtParser();


        float *getGLColor(char **string, float *target);
        vector getVector(char **string);
        vertex2D getVertex2D(char **string);

    protected:
        charList placeholders;
        charList lineEndChars;
        charList breakChars;
};



#endif
