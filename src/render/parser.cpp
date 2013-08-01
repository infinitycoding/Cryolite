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

    for(i = 0; line[i] != ' ' && line[i] != '=' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(i++; (line[i] == ' ' || line[i] == '=') && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; line[i] != '\0' && line[i] != '\n' && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    return string;
}


bool BasicParser::checkValidNumber(const char *string)
{
    for(int i = 0; string[i] != '\n' && string[i] != '\0' && i < MAX_LINELENGTH; i++)
        if(!((string[i] >= '0' && string[i] <= '9') || string[i] == '-' || string[i] == '+' || string[i] == '.'))
            return false;

    return true;
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

    if(!checkValidNumber(string))
    {
        cerr << "error from parser: \"" << string << "\" is not a valid number." << endl;
        exit(-1);
    }

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

    if(!checkValidNumber(string))
    {
        cerr << "error from parser: \"" << string << "\" is not a valid number." << endl;
        exit(-1);
    }

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
        cerr << "error from parser: \"" << string << "\" is not a bool value";
        exit(-1);
    }
}


float *BasicParser::getValueGLColor(const char *line, float *target)
{
    int i, j;
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(;  (line[i] == ' ' || line[i] == '=') && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    target[0] = atof(string);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    target[1] = atof(string);

        if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    target[2] = atof(string);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    return target;
}


vector BasicParser::getValueVector(const char *line)
{
    int i, j;
    vector returnValue = vector();
    char string[MAX_LINELENGTH];
    memset(string, '\0', sizeof(string));

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(; (line[i] == ' ' || line[i] == '=') && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    string[j] = '\0';

    returnValue.x = atof(string);

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    string[j] = '\0';

    returnValue.y = atof(string);

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    returnValue.z = atof(string);

    return returnValue;
}


Vertex3D BasicParser::getValueVertex3D(const char *line)
{
    vector temp = getValueVector(line);
    return Vertex3D(temp.x, temp.y, temp.z);
}


Vertex2D BasicParser::getValueVertex2D(const char *line)
{
    int i, j;
    Vertex2D returnValue = Vertex2D();
    char string[MAX_LINELENGTH];

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    string[j] = '\0';

    returnValue.setX(atof(string));

    for(; line[i] == ' ' && i < MAX_LINELENGTH; i++);

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == '-') && i < MAX_LINELENGTH; i++, j++)
        string[j] = line[i];

    if(i >= MAX_LINELENGTH)
    {
        cerr << "error from parser: line too long or foregotten \0" << endl;
        exit(-1);
    }

    string[j] = '\0';

    returnValue.setY(atof(string));

    return returnValue;
}
