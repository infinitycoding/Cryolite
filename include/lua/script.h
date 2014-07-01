#ifndef SCRIPT_H
#define SCRIPT_H



#include <lua.hpp>
#include <iostream>
#include <typeinfo>
#include <cstring>

using namespace std;



class Script
{
    public:
        Script();
        Script(const char *Scriptname);
        ~Script();

        void initLUA();


        bool load(const char *Scriptname);
        bool run();

        double insertGlobalNumber(const char *varname, double value);
        double getGlobalNumber(const char *varname);
        bool insertGlobalBool(const char *varname, bool value);
        bool getGlobalBool(const char *varname);
        char *insertGlobalString(const char *varname, char *value);
        const char *getGlobalString(const char *varname);

        void addMetatable(const char * classname ,luaL_Reg *metatable);
        void *getObject(const char *luaClass);
        lua_State *getState();

    protected:
        lua_State *lState;
};

using namespace std;

template <typename T>
struct luaObject
{
    size_t id;
    unsigned char cObject[sizeof(T)/sizeof(unsigned char)];
};


// DO NOT USE THE INLINE FUNCTIONS!!! USE THE MACROS!

template <typename T>
static inline luaObject<T>* GETINSTANCEFROMLUA(lua_State *L, const char *Metatable, int index = -1)
{
  luaL_checktype(L, index, LUA_TTABLE);
  lua_getfield(L, index, "__self");
  return (luaObject<T>*)luaL_checkudata(L, index, Metatable);
}

static inline size_t GET_CURRENT_LUA_OBJECT_TYPE(lua_State *L, const char *Metatable, int index = -1)
{
  luaL_checktype(L, index, LUA_TTABLE);
  lua_getfield(L, index, "__self");
  size_t hash = ((size_t*)luaL_checkudata(L, index, Metatable))[0];
  lua_pop(L,1);
  return hash;
}


static inline int LUA_INT(lua_State *L)
{
    int r = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return r;
}


static inline int LUA_INT(lua_State *L, int value)
{
    lua_pushinteger(L, value);
    return 1;
}

static inline double LUA_NUM(lua_State *L)
{
    double r = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return r;
}


static inline int LUA_NUM(lua_State *L, double value)
{
    lua_pushnumber(L, value);
    return 1;
}

static inline char *LUA_STR(lua_State *L)
{
    char *str = (char*) lua_tostring(L, -1);
    lua_pop(L, 1);
    return str;
}


static inline int LUA_STR(lua_State *L, char *str)
{
    lua_pushstring(L, str);
    return 1;
}


static inline bool LUA_BOOL(lua_State *L)
{
    bool value = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return value;
}


static inline int LUA_BOOL(lua_State *L, bool value)
{
    lua_pushboolean(L, value);
    return 1;
}


template <typename T>
static inline T* LUA_DATA(lua_State *L, const char *Metatable,const char *notused)
{
    luaObject<T>* currentObject = GETINSTANCEFROMLUA<T>(L, Metatable);
    lua_pop(L, 2);
    return (T*) &(currentObject->cObject);
}


template <typename T>
static inline int LUA_DATA(lua_State *L, T value, const char *Metatable)
{
    luaL_checktype(L, 1, LUA_TTABLE); lua_newtable(L); lua_pushvalue(L,1); lua_setmetatable(L, -2); lua_pushvalue(L,1); lua_setfield(L, 1, "__index");
    luaObject<T> newObject;
    newObject.id = typeid(T).hash_code();
    *((T*)newObject.cObject) = value;
    *((luaObject<T>*) lua_newuserdata(L, sizeof(newObject))) = newObject;
    luaL_getmetatable(L, Metatable);lua_setmetatable(L, -2); lua_setfield(L, -2, "__self"); return 1;
}

template <typename T>
static inline bool is_object_type(lua_State *L,const char *name, int index = -1)
{
    if(typeid(T).hash_code() == (GET_CURRENT_LUA_OBJECT_TYPE(L,name, index)))
        return true;
    return false;
}


template <typename T>
static inline bool is_type(lua_State *L, int index = -1)
{
    size_t hash = typeid(T).hash_code();
    if(hash == typeid(int).hash_code() || hash == typeid(float).hash_code())
        return lua_isnumber(L, index);
    else if(hash == typeid(char *).hash_code())
        return lua_isstring(L, index);
    else if(hash == typeid(bool).hash_code())
        return lua_isboolean(L, index);
    return false;
}

static inline bool is_table(lua_State *L, int index = -1)
{
    return lua_istable(L, -1);
}

typedef luaL_Reg reg;

#define CBEGIN(NAME) int NAME(lua_State *L){
#define CEND(RETPARAM, ...) __VA_ARGS__; return RETPARAM;}

#define NEWBEGIN(NAME) int NAME(lua_State *L){
#define NEWEND(CLASS) luaL_getmetatable(L, #CLASS);lua_setmetatable(L, -2); lua_setfield(L, -2, "__self"); return 1;}

#define CONSTRUCT(...) luaL_checktype(L, 1, LUA_TTABLE); lua_newtable(L); lua_pushvalue(L,1); lua_setmetatable(L, -2); lua_pushvalue(L,1); lua_setfield(L, 1, "__index")
#define addInstance(TYPE, VALUE) LUA_DATA<TYPE>(L, VALUE, #TYPE)


#define getargc(...) lua_gettop(L)
#define getInstance(TYPE, ...) ((TYPE*)(GETINSTANCEFROMLUA<TYPE>(L, #TYPE, ##__VA_ARGS__)->cObject))


#define LCALL(FUNCTION, ARGC, ...) lua_getglobal(L, #FUNCTION); __VA_ARGS__ lua_pcall(L,ARGC,1,0)

#define LINT(...) LUA_INT(L,##__VA_ARGS__)
#define LDAT(TYPE, TABLE_OR_VALUE) LUA_DATA<TYPE>(L, TABLE_OR_VALUE,#TYPE)
#define LDBL(...) LUA_NUM(L,##__VA_ARGS__)
#define LSTR(...) LUA_STR(L,##__VA_ARGS__)
#define LBOOL(...) LUA_BOOL(L,##__VA_ARGS__)

#define getarg(...) __VA_ARGS__
#define CHECK(...) if(__VA_ARGS__){
#define ELSE } else {
#define ELSEIF(...) } else if(__VA_ARGS__){
#define CHECKEND }

#define isbool(PARAM) lua_isboolean(L, PARAM * -1)
#define isstring(PARAM) lua_isstring(L, PARAM * -1)
#define isobject(PARAM) lua_istable(L, PARAM * -1)
#define isnumber(PARAM) lua_isnumber(L, PARAM * -1)
#define istype(TYPE,...) is_type<TYPE>(L,##__VA_ARGS__)
#define istobjecttype(TYPE, ...) (is_object_type<TYPE>(L,#TYPE,##__VA_ARGS__))
#define lerror(FORMAT, ...) luaL_error(L, FORMAT, ##__VA_ARGS__)
#define RET(RETPARAM, ...) __VA_ARGS__; return RETPARAM
#define LRET(RETC,...) RETC; __VA_ARGS__;


#define CLASS
#define ENDCLASS
#define addClass(TYPE) addMetatable(#TYPE,_#TYPE);
#define OVERLOAD(NAME,...) int NAME(lua_State *L) {int argc = lua_gettop(L)-1; char name[] = #NAME; if(false);
#define ENDOVERLOAD else {printf("%s: can't find matching overloaded function\n",name);} return false;}
#define SELECT(FUNCTION,ARG,...) else if((argc==ARG) && (__VA_ARGS__)){int ret = FUNCTION; return ret;}
#define FUNCTION(NAME,FUNCTION,ARG,CHECK,...) int NAME(lua_State *L) {int argc = lua_gettop(L); if((argc==ARG) && (CHECK)){int ret = FUNCTION; return ret;} lerror("\n%s: expected %d arguments got %d\n",#NAME,ARG,argc); return false;}
#define VOID 0;
//todo: argumet passing
#define ARG0 -1
#define ARG1 -2
#define ARG2 -3
#define ARG3 -4
#define ARG4 -5
#define ARG5 -6
#define ARG6 -7
#define ARG7 -8
#define ARG8 -9
#define ARG9 -10
#define ARG10 -11

inline bool lua_check_key(lua_State *L, const char *key)
{
    const char *table_key = lua_tostring(L, -2);
    if(!table_key)
        return false;

    if(strcmp(table_key, key) == 0)
        return true;
    return false;
}

#define ASSOCIATION(CLASS) reg CLASS ##Reg[]{
#define ENDASSOCIATION {NULL, NULL}};
#define ALIAS(FUNCTION, NAME) {NAME, FUNCTION},
#define checkkey(KEY) lua_check_key(L, KEY)
#define foreach_element(TABLE) for(lua_getglobal(L, TABLE), bool _IS_TABLE = lua_istable(L, -1), lua_pushnil(L); (lua_next(L, -2) != 0) && _IS_TABLE; lua_pop(L, 1))

#endif
