#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED



#include <cstdlib>


#define MAX_CHAR_LIST_SIZE 10



class BasicParser
{
    public:
        BasicParser();
        ~BasicParser();


        char *skipPlaceholders(char *string);

        char *getString(char *string);

        bool getBool(char *string);

        short getShort(char *string);
        int getInt(char *string);
        long getLong(char *string);

        float getFloat(char *string);
        double getDouble(char *string);

        void addPlaceholderChar(char character);
        void addLineEndChar(char character);
        void addValueEndChar(char character);

        bool isInList(char character, char *list, unsigned int highestIndex);

    protected:
        unsigned int highestPlaceholderCharIndex;
        unsigned int highestLineEndCharIndex;
        unsigned int highestValueEndCharIndex;

        char placeholderChars[MAX_CHAR_LIST_SIZE];
        char lineEndChars[MAX_CHAR_LIST_SIZE];
        char valueEndChars[MAX_CHAR_LIST_SIZE];
};


#endif
