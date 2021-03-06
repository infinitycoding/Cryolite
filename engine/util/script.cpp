#define LUA_COMPAT_MODULE

#include <lua/script.h>
#include <iostream>

using namespace std;

/*example LUA function

CBEGIN(peter)
    double *x = (double *)lua_newuserdata(L, sizeof(double));
    *x = 10.0;
CEND(Peter)
*/

/* example lua Call

ALLOW_LCALL(); //call only once in a function! and please do not use the varriable LUAPARANUM

LCALL(peter, INT(5) DBL(3));
LRET(L);

example 2:

LCALL(simon, STR("XD"));
int retunrvalue = LRET<char *>(L);

*/





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
extern reg SceneReg[];

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
    addMetatable("Scene",SceneReg);

    return true;
}


void PrintTable(lua_State *L)
{
    lua_pushnil(L);

    while(lua_next(L, -2) != 0)
    {
        if(lua_isstring(L, -1))
          printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
          printf("%s = %g\n", lua_tostring(L, -2), lua_tonumber(L, -1));
        else if(lua_istable(L, -1))
          PrintTable(L);

        lua_pop(L, 1);
    }
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


void *Script::getObject(lua_State *L, const char *luaClass)
{
    void* ud = 0;
    luaL_checktype(L, 0, LUA_TTABLE);
    lua_getfield(L, 0, "__self");
    ud = luaL_checkudata(L, 0, luaClass);
    luaL_argcheck(L, ud != 0, 0,"NULL object pointer returned");
    return ud;
}


