#ifndef LUARAPPER_H_INCLUDED
#define LUARAPPER_H_INCLUDED



#include <lua.hpp>
#include <iostream>
#include <typeinfo>



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

#define CBEGIN(NAME) int NAME(lua_State *L){ luaL_checktype(L, 1, LUA_TTABLE); lua_newtable(L); lua_pushvalue(L,1); lua_setmetatable(L, -2); lua_pushvalue(L,1); lua_setfield(L, 1, "__index");
#define CEND(name) luaL_getmetatable(L, #name);lua_setmetatable(L, -2); lua_setfield(L, -2, "__self"); return 1;}



#define PRT(VALUE) lua_pushunsigned(L,VALUE); LUAPARANUM++;
#define STR(VALUE) lua_pushstring(L,VALUE); LUAPARANUM++;
#define DBL(VALUE) lua_pushnumber(L,VALUE); LUAPARANUM++;
#define INT(VALUE) lua_pushinteger(L,VALUE); LUAPARANUM++;
#define ALLOW_LCALL(...) int LUAPARANUM = 0
#define LCALL(FUNCTION,...) lua_getglobal(L, #FUNCTION); LUAPARANUM = 0; __VA_ARGS__ lua_pcall(L,LUAPARANUM,1,0)

static inline void LRET(lua_State *L)
{
    lua_pop(L,1);
}


template <typename T>
static inline const T LRET(lua_State *L)
{
    T returnvalue;
    if(typeid(T) == typeid(char *) || typeid(T) == typeid(unsigned char *))
        returnvalue = (T)lua_tostring(L,-1);
    else if(typeid(T) == typeid(int) || typeid(T) == typeid(unsigned int) || typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char) || typeid(T) == typeid(short) || typeid(T) ==typeid(unsigned short) )
        returnvalue = (T)lua_tointeger(L,-1);
    else if(typeid(T) == typeid(double) || typeid(T) == typeid(float))
        returnvalue = (T)lua_tonumber(L,-1);
    else
        returnvalue = (T)lua_topointer(L,-1);

    lua_pop(L,1);
    return returnvalue;
}


#endif

