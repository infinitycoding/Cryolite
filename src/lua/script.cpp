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

extern reg fpsReg[];
extern reg vectorReg[];
extern reg objReg[];
extern reg profilerReg[];

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
    addMetatable("fps", fpsReg);
    addMetatable("vector", vectorReg);
    addMetatable("object", objReg);
    addMetatable("profiler", profilerReg);
    //addMetatable("Camera",cameraTable);

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


double Script::insertGlobalVar(const char *varname, double value)
{
    lua_pushnumber(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


double Script::getGlobalVar(const char *varname)
{
    lua_getglobal(lState, varname);
    double result = lua_tonumber(lState, -1);
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


