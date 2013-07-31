#ifndef LUARAPPER_H_INCLUDED
#define LUARAPPER_H_INCLUDED



#include <lua.hpp>

#include <iostream>



class LUASkript
{
    public:
        LUASkript();
        LUASkript(const char *skriptname);
        ~LUASkript();

        void initLUA();


        bool loadSkript(const char *skriptname);
        bool runSkript();

        double insertDoubleVar(const char *varname, double value);
        double getDoubleVar(const char *varname);

    protected:
        lua_State *lState;
};


#endif
