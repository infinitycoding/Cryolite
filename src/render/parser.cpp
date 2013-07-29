#include <parser.h>



using namespace std;



BasicParser::BasicParser()
{

}


BasicParser::~BasicParser()
{

}


char *BasicParser::getValueString(const char *line, char *string)
{
    int i, j;

    for(i = 0; line[i] != ' ' && line[i] != '='; i++);
    for(i++; line[i] == ' ' || line[i] == '='; i++);

    for(j = 0; line[i] != '\0' && line[i] != '\n'; i++, j++)
        string[j] = line[i];

    return string;
}


float BasicParser::getValueFloat(const char *line)
{
    return (float) getValueDouble(line);
}


double BasicParser::getValueDouble(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);
    return atof(string);
}


short BasicParser::getValueShort(const char *line)
{
    return (short) getValueInt(line);
}


int BasicParser::getValueInt(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);
    return atoi(string);
}


long BasicParser::getValueLong(const char *line)
{
    return (long) getValueLong(line);
}


bool BasicParser::getValueBool(const char *line)
{
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));
    getValueString(line, string);

    if((strncmp(string, "enable", 6) == 0) || (strncmp(string, "on", 2) == 0) || (strncmp(string, "yes", 3) == 0) || (strncmp(string, "activate", 8) == 0) || (strncmp(string, "true", 4) == 0) || (strncmp(string, "1", 1) == 0))
        return true;
    else if((strncmp(string, "disable", 7) == 0) || (strncmp(string, "off", 3) == 0) || (strncmp(string, "no", 2) == 0) || (strncmp(string, "deactivate", 10) == 0) || (strncmp(string, "false", 5) == 0) || (strncmp(string, "0", 1) == 0))
        return false;
    else
    {
        cout << "The following line is incorrect:" << endl;
        cout << line << endl;
        return false;
    }
}


SDL_Color BasicParser::getValueColor(const char *line)
{
    int i, j;
    SDL_Color returnValue = {0, 0, 0, 0};
    char string[MAX_LINELENGTH];

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_LINELENGTH; i++);

    if(line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i == MAX_LINELENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_LINELENGTH || line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.r = atof(string);

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i == MAX_LINELENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_LINELENGTH || line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.g = atof(string);

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i == MAX_LINELENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_LINELENGTH)
    {
        cerr << "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.b = atof(string);

    return returnValue;
}
