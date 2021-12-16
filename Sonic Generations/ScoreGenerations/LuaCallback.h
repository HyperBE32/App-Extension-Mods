#pragma once

#define LUA_FILE "ScoreGenerations.lua"

class LuaCallback
{
	static string LuaPath;

public:
	static bool SetLuaPath(string path);
	static void PushExposedData(lua_State* L);
	static void PushExposedInteger(lua_State* L, string name, unsigned int pushToStack);
	static void PushExposedString(lua_State* L, string name, string value);
	static void PushLuaLibrary(lua_State* L, const char* name, lua_CFunction function);
	static bool LoadInternalLibrary(lua_State* L);
	static bool LoadExternalLibrary(lua_State* L);
	static void PrintExposedData();
	static int RunAlgorithm(string algorithm);

	static int print(lua_State* L)
	{
		int nargs = lua_gettop(L);

		// Print characters from string.
		for (int i = 1; i <= nargs; ++i)
			cout << lua_tostring(L, i);

		// Print line break.
		cout << endl;

		return 0;
	}

	static const struct luaL_Reg Functions[];
};