#include <parser.h>



BasicParser::BasicParser()
{
    highestPlaceholderCharIndex = 0;
    highestLineEndCharIndex = 0;
    highestValueEndCharIndex = 0;
}


BasicParser::~BasicParser()
{

}


char *BasicParser::skipPlaceholders(char *string)
{
    int i;

    for(i = 0; isInList(string[i], placeholderChars, highestPlaceholderCharIndex); i++);

    return (string = &string[i]);
}


char *BasicParser::getString(char *string)
{
    return NULL;
}


bool BasicParser::getBool(char *string)
{
    return false;
}


short BasicParser::getShort(char *string)
{
    return 0;
}


int BasicParser::getInt(char *string)
{
    return 0;
}


long BasicParser::getLong(char *string)
{
    return 0;
}


float BasicParser::getFloat(char *string)
{
    return 0.0;
}


double BasicParser::getDouble(char *string)
{
    return 0.0;
}


void BasicParser::addPlaceholderChar(char character)
{
    placeholderChars[++highestPlaceholderCharIndex] = character;
}


void BasicParser::addLineEndChar(char character)
{
    lineEndChars[++highestLineEndCharIndex] = character;
}


void BasicParser::addValueEndChar(char character)
{
    valueEndChars[++highestValueEndCharIndex] = character;
}


bool BasicParser::isInList(char character, char *list, unsigned int highestIndex)
{
    for(unsigned int i = 0; i <= highestIndex; i++)
        if(list[i] == character)
            return true;

    return false;
}
