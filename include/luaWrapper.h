#ifndef LUARAPPER_H_INCLUDED
#define LUARAPPER_H_INCLUDED



#include <lua.hpp>

#include <iostream>



class LUAScript
{
    public:
        LUAScript();
        LUAScript(const char *Scriptname);
        ~LUAScript();

        void initLUA();


        bool loadScript(const char *Scriptname);
        bool runScript();

        double insertDoubleVar(const char *varname, double value);
        double getDoubleVar(const char *varname);

    protected:
        lua_State *lState;
};


#endif
