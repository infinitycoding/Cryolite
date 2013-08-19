#ifndef LUARAPPER_H_INCLUDED
#define LUARAPPER_H_INCLUDED



#include <lua.hpp>
#include <iostream>




class Script
{
    public:
        Script();
        Script(const char *Scriptname);
        ~Script();

        void initLUA();


        bool load(const char *Scriptname);
        bool run();

        double insertGlobalVar(const char *varname, double value);
        double getGlobalVar(const char *varname);
        void addMetatable(const char * classname ,luaL_Reg *metatable);
        static void *getObject(lua_State *L, const char *luaClass);

    protected:
        lua_State *lState;
};

#define LCALL int
#define BEGIN (lua_State *L){ luaL_checktype(L, 1, LUA_TTABLE); lua_newtable(L); lua_pushvalue(L,1); lua_setmetatable(L, -2); lua_pushvalue(L,1); lua_setfield(L, 1, "__index");
#define END(name) luaL_getmetatable(L, #name);lua_setmetatable(L, -2); lua_setfield(L, -2, "__self"); return 1;}


#endif

