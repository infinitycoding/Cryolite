#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

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

#include <SDL.h>

#include <iostream>
#include <cstring>

#include <util/vector.h>


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
