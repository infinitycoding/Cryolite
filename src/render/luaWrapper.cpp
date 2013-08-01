#include <luaWrapper.h>



using namespace std;



LUAScript::LUAScript()
{
    initLUA();
}


LUAScript::LUAScript(const char *Scriptname)
{
    initLUA();

    loadScript(Scriptname);
}


LUAScript::~LUAScript()
{
    lua_close(lState);
}


void LUAScript::initLUA()
{
    lState = luaL_newstate();
    luaL_openlibs(lState);
}


bool LUAScript::loadScript(const char *Scriptname)
{
    if (luaL_loadfile(lState, Scriptname))
    {
        cerr << "the Script " << Scriptname << " could not be loaded." << endl;
        cerr << lua_tostring(lState, -1) << endl;
        lua_pop(lState,1);
        return false;
    }

    return true;
}


bool LUAScript::runScript()
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


double LUAScript::insertDoubleVar(const char *varname, double value)
{
    lua_pushnumber(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


double LUAScript::getDoubleVar(const char *varname)
{
    lua_getglobal(lState, varname);
    double result = lua_tonumber(lState, -1);
    lua_pop(lState, 1);
    return result;
}
