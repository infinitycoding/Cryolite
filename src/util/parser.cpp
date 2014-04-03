#include <parser.h>



using namespace std;



BasicParser::BasicParser()
{

}


BasicParser::~BasicParser()
{

}


bool BasicParser::charInList(char character, const charList list)
{
    for(int i = 0; i < list.number; i++)
        if(character == list.chars[i])
            return true;

    return false;
}


bool BasicParser::validNumber(char *string, bool allowFloat, bool allowSigned)
{
    char allowedChars[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    charList allowed = {10, allowedChars};

    if(allowFloat)  allowed.chars[allowed.number] = '.'; allowed.number++;
    if(allowSigned) allowed.chars[allowed.number] = '-'; allowed.number++;

    for(int i = 0; string[i] != '\0'; i++)
        if(!charInList(string[i], allowed))
            return false;

    return true;
}


char **BasicParser::skipCharacters(char **string, const charList characters)
{
    while(charInList(*string[0], characters))
        *string += sizeof(char);

    return string;
}


char **BasicParser::skipUntilCharacters(char **string, const charList characters)
{
    while(!charInList(*string[0], characters))
        *string += sizeof(char);

    return string;
}


char *BasicParser::getString(char **instring, char *outstring, const charList endCharacters)
{
    int i;

    for(i = 0; !charInList(*instring[0],endCharacters); i++)
    {
        outstring[i] = *instring[0];
        *instring += sizeof(char);
    }

    outstring[i] = '\0';

    return outstring;
}


bool BasicParser::getBool(char **string, const charList endCharacters)
{
    char temp[NUMBER_STRING_SIZE];
    memset(temp, '\0', sizeof(temp));

    getString(string, temp, endCharacters);

    if(!strncmp(temp, "yes", 3) || !strncmp(temp, "true", 4) || !strncmp(temp, "activate", 8) || !strncmp(temp, "on", 2) || !strncmp(temp, "1", 1) || !strncmp(temp, "enable", 6) || !strncmp(temp, "correct", 7) || !strncmp(temp, "positive", 8))
        return true;
    else if(!strncmp(temp, "no", 2) || !strncmp(temp, "false", 5) || !strncmp(temp, "deactivate", 10) || !strncmp(temp, "off", 3) || !strncmp(temp, "0", 1) || !strncmp(temp, "disable", 7) || !strncmp(temp, "incorrect", 9) || !strncmp(temp, "negative", 8))
        return false;
    else
    {
        cerr << "parser warning: \"" << temp << "\" is not a bool value" << endl;
        return false;
    }
}


short BasicParser::getShort(char **string, const charList endCharacters)
{
    return (short) getInt(string, endCharacters);
}


int BasicParser::getInt(char **string, const charList endCharacters)
{
    char temp[NUMBER_STRING_SIZE];
    memset(temp, '\0', sizeof(temp));

    getString(string, temp, endCharacters);

    if(validNumber(temp, false, true))
        return atof(temp);
    else
    {
        cerr << "parser error: \"" << temp << "\" is not a int value" << endl;
        exit(-1);
    }

}


long BasicParser::getLong(char **string, const charList endCharacters)
{
    return (long) getInt(string, endCharacters);
}


float BasicParser::getFloat(char **string, const charList endCharacters)
{
    return (float) getDouble(string, endCharacters);
}


double BasicParser::getDouble(char **string, const charList endCharacters)
{
    char temp[NUMBER_STRING_SIZE];
    memset(temp, '\0', sizeof(temp));

    getString(string, temp, endCharacters);

    if(validNumber(temp, true, true))
        return atof(temp);
    else
    {
        cerr << "parser error: \"" << temp << "\" is not a double value" << endl;
        exit(-1);
    }
}





ExtParser::ExtParser()
{
    placeholders.number = 2;
    placeholders.chars = new char[2]{' ', '='};

    lineEndChars.number = 2;
    lineEndChars.chars = new char[2]{'\n', '\0'};

    breakChars.number = 4;
    breakChars.chars = new char[4]{' ', '=', '\n', '\0'};
}


ExtParser::~ExtParser()
{
    delete[] placeholders.chars;
    delete[] lineEndChars.chars;
    delete[] breakChars.chars;
}


float *ExtParser::getGLColor(char **string, float *target)
{
    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 0 parameters to glcolor" << endl;
        return target;
    }

    for(int i = 0; i < 4; i++)
    {
        skipCharacters(string, placeholders);

        if(charInList(*string[0], lineEndChars) && i < 3)
        {
            cerr << "parser warning: had expected more than " << i+1 << " parameters to glcolor" << endl;
            return target;
        }

        target[i] = getFloat(string, breakChars);
    }

    return target;
}


vector ExtParser::getVector(char **string)
{
    vector result = vector();

    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 0 parameters to vector" << endl;
        return result;
    }

    result.x[0] = getFloat(string, breakChars);

    skipCharacters(string, placeholders);

    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 1 parameter to vector" << endl;
        return result;
    }

    result.x[1] = getFloat(string, breakChars);

    skipCharacters(string, placeholders);

    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 2 parameters to vector" << endl;
        return result;
    }

    result.x[2] = getFloat(string, breakChars);


    return result;
}


vertex2D ExtParser::getVertex2D(char **string)
{
    vertex2D result;

    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 0 parameters to vertex2d" << endl;
        return result;
    }

    result.x = getFloat(string, breakChars);

    skipCharacters(string, placeholders);

    if(charInList(*string[0], lineEndChars))
    {
        cerr << "parser warning: had expected more than 1 parameter to vertex2d" << endl;
        return result;
    }

    result.y = getFloat(string, breakChars);

    return result;
}


vertex3D ExtParser::getVertex3D(char **string)
{
    vector temp = getVector(string);
    vertex3D result = {temp.x[0], temp.x[1], temp.x[2]};
    return result;
}
