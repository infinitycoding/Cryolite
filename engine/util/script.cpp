#define LUA_COMPAT_MODULE

#include <lua/script.h>
#include <iostream>

using namespace std;



Script::Script()
{
    initLUA();
}


Script::Script(const char *Scriptname)
{
    initLUA();

    load(Scriptname);
}


Script::~Script()
{
    lua_close(lState);
}


void Script::initLUA()
{
    lState = luaL_newstate();
    luaL_openlibs(lState);
}

extern reg vectorReg[];
extern reg CameraReg[];
extern reg LevelReg[];

bool Script::load(const char *Scriptname)
{
    if (luaL_loadfile(lState, Scriptname))
    {
        cerr << "the Script " << Scriptname << " could not be loaded." << endl;
        cerr << lua_tostring(lState, -1) << endl;
        lua_pop(lState,1);
        return false;
    }

    //add metatables
    addMetatable("vector", vectorReg);
    addMetatable("Camera", CameraReg);
    addMetatable("Level",LevelReg);

    return true;
}

bool Script::run()
{
    if (lua_pcall(lState,0, LUA_MULTRET, 0))
    {
        cerr << "an error has occured during the execution of some lua Script" << endl;
        cerr << lua_tostring(lState, -1) << endl;
        lua_pop(lState,1);
        return false;
    }
    return true;
}


void Script::addMetatable(const char * classname ,luaL_Reg *metatable)
{
    luaL_newmetatable(lState, classname);
    luaL_setfuncs (lState, metatable, 0);
    lua_pushvalue(lState, -1);
    lua_setfield(lState, -1, "__index");
    lua_setglobal(lState, classname);
}


double Script::insertGlobalNumber(const char *varname, double value)
{
    lua_pushnumber(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


double Script::getGlobalNumber(const char *varname)
{
    lua_getglobal(lState, varname);
    double result = lua_tonumber(lState, -1);
    lua_pop(lState, 1);
    return result;
}


bool Script::insertGlobalBool(const char *varname, bool value)
{
    lua_pushboolean(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


bool Script::getGlobalBool(const char *varname)
{
    lua_getglobal(lState, varname);
    bool result = lua_toboolean(lState, -1);
    lua_pop(lState, 1);
    return result;
}

char *Script::insertGlobalString(const char *varname, char *value)
{
    lua_pushstring(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


const char *Script::getGlobalString(const char *varname)
{
    lua_getglobal(lState, varname);
    const char *result = lua_tostring(lState, -1);
    lua_pop(lState, 1);
    return result;
}


void *Script::getObject(const char *luaClass)
{
    void* ud = 0;
    luaL_checktype(lState, 0, LUA_TTABLE);
    lua_getfield(lState, 0, "__self");
    ud = luaL_checkudata(L, 0, luaClass);
    luaL_argcheck(lState, ud != 0, 0,"NULL object pointer returned");
    return ud;
}

lua_State *Script::getState()
{
    return lState;
}