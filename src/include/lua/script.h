#ifndef SCRIPT_H
#define SCRIPT_H



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


// DO NOT USE THE INLINE FUNCTIONS!!! USE THE MACROS!

template <typename T>
static inline T GETINSTANCEFROMLUA(lua_State *L, const char *Metatable, int index = -1)
{
  luaL_checktype(L, index, LUA_TTABLE);
  lua_getfield(L, index, "__self");
  return (T) luaL_checkudata(L, index, Metatable);
}


static inline int LUA_INT(lua_State *L)
{
    int r = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return r;
}


static inline void LUA_INT(lua_State *L, int value)
{
    lua_pushinteger(L, value);
}

static inline double LUA_NUM(lua_State *L)
{
    double r = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return r;
}


static inline void LUA_NUM(lua_State *L, double value)
{
    lua_pushnumber(L, value);
}

static inline char *LUA_STR(lua_State *L)
{
    char *str = (char*) lua_tostring(L, -1);
    lua_pop(L, 1);
    return str;
}


static inline void LUA_STR(lua_State *L, char *str)
{
    lua_pushstring(L, str);
}


static inline bool LUA_BOOL(lua_State *L)
{
    bool value = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return value;
}


static inline void LUA_BOOL(lua_State *L, bool value)
{
    lua_pushboolean(L, value);
}

template <typename T>
static inline T LUA_DATA(lua_State *L, const char *Metatable)
{
    T data = GETINSTANCEFROMLUA<T>(L, Metatable);
    lua_pop(L, 2);
    return data;
}


template <typename T>
static inline void LUA_DATA(lua_State *L, T value)
{
    T* udata = (T*) lua_newuserdata(L, sizeof(T));
    *udata = value;
}




typedef luaL_Reg reg;

#define CBEGIN(NAME) int NAME(lua_State *L){
#define CEND(RETPARAM, ...) __VA_ARGS__; return RETPARAM;}

#define NEWBEGIN(NAME) int NAME(lua_State *L){
#define NEWEND(CLASS) luaL_getmetatable(L, #CLASS);lua_setmetatable(L, -2); lua_setfield(L, -2, "__self"); return 1;}

#define CONSTRUCT(...) luaL_checktype(L, 1, LUA_TTABLE); lua_newtable(L); lua_pushvalue(L,1); lua_setmetatable(L, -2); lua_pushvalue(L,1); lua_setfield(L, 1, "__index")



#define addInstance(TYPE, VALUE) LUA_DATA<TYPE>(L, VALUE);


#define getargc(...) lua_gettop(L)
#define getInstance(TYPE, METATABLE, ...) GETINSTANCEFROMLUA<TYPE>(L, METATABLE, ##__VA_ARGS__)


#define LCALL(FUNCTION, ARGC, ...) lua_getglobal(L, #FUNCTION); __VA_ARGS__ lua_pcall(L,ARGC,1,0)

#define LINT(...) LUA_INT(L,##__VA_ARGS__);
#define LDAT(TYPE, TABLE_OR_VALUE) LUA_DATA<TYPE>(L, TABLE_OR_VALUE);
#define LDBL(...) LUA_NUM(L,##__VA_ARGS__);
#define LSTR(...) LUA_STR(L,##__VA_ARGS__);
#define LBOOL(...) LUA_BOOL(L,##__VA_ARGS__);

#define getarg(...) __VA_ARGS__
#define CHECK(...) if(__VA_ARGS__){
#define ELSE } else {
#define CHECKEND }

#define isstring(PARAM) lua_isstring(L, PARAM * -1)
#define isobject(PARAM) lua_istable(L, PARAM * -1)
#define isnumber(PARAM) lua_isnumber(L, PARAM * -1)
#define lerror(FORMAT, ...) luaL_error(L, FORMAT, ##__VA_ARGS__)

#define RET(RETPARAM, ...) __VA_ARGS__; return RETPARAM







#endif

