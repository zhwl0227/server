/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "LuaEngine.h"
#include "Policies/SingletonImp.h"
#include "Chat.h"

INSTANTIATE_SINGLETON_1(LuaEngine);

void RegisterCreatureEvent(int entry, int type, const char* funcName)
{
    CreatureLuaScript cls;
    cls.type = type;
    cls.name = funcName;

    CreatureLuaScripts::iterator it = sLua->creaturescripts.find(entry);
    if (it != sLua->creaturescripts.end())
    {
        (*it).second.push_back(cls);
        sLua->creaturescripts[entry] = (*it).second;
        return;
    }
    else
    {
        CreatureLuaEvents cle;
        cle.push_back(cls);
        sLua->creaturescripts[entry] = cle;
    }
}

void LuaEngine::Initialize()
{
    m_luaState = lua_open();
    int iErr = 0;

    if (!m_luaState)
    {
        sLog.outString("Something wrong happened to the Lua engine");
        return;
    }

	luabind::open(m_luaState);
    luaL_openlibs(m_luaState);

    m_file = "./mangosscript.lua";
	AddHooks();

    if(luaL_dofile(m_luaState, m_file))
	{
		sLog.outString("Lua engine error: %s", lua_tostring(m_luaState, 1));
		return;
	}

    sLog.outString("_______________MMMM");
    sLog.outString("______________MMMMMMM");
    sLog.outString("______________MMMMMMMM_____M_M_M");
    sLog.outString("_______________MMMMMMM____MMMMMM");
    sLog.outString("________________MMMMMMM____MMM");
    sLog.outString("________M__M_M____MMMMMMMMMMM");
    sLog.outString("_________MMMMMM___MMMMMMMMMM     MaNGOS Lua Engine Initialized!");
    sLog.outString("__________MMM_MMMMMMMMMMMMMMMM");
    sLog.outString("___________________MMMMMMMMMMMM");
    sLog.outString("___________________MMMMMMMMMMMM");
    sLog.outString("____________________MMMMMMMMMMMMMMMM");
    sLog.outString("_________________MMMMMMMMMMMMMM___MMM");
    sLog.outString("_________________MMMM___MMMMM______MMMM");
    sLog.outString("_________________MMM_____MMMMM____M_M_M");
    sLog.outString("_______________MMMM_______MMMM");
    sLog.outString("________________M_M_M_____MMMM");
    sLog.outString("__________________________MMMM");
    sLog.outString("_____________MMMMMM_______MMMM");
    sLog.outString("___________MM______MM_____MMMM");
    sLog.outString("__________MMM______MM_____MMM");
    sLog.outString("___________MM_____M______MMM");
    sLog.outString("____________MM__________MMM");
    sLog.outString("______________MMM___MMMMM");
    sLog.outString("________________MMMMM");
}

void LuaEngine::AddHooks()
{
    sLog.outString("Initializing Hooks");

    luabind::module(m_luaState)
		[
			luabind::def("RegisterCreatureEvent",&RegisterCreatureEvent)
        ];
	luabind::module(m_luaState)
        [
            luabind::class_<Creature,Unit>("Creature")
            .def((const char*)"GetGUID",&Creature::GetGUID)
            .def((const char*)"GetGUIDLow",&Creature::GetGUIDLow)
            .def((const char*)"GetName",&Creature::GetName)
            .def((const char*)"GetEntry",&Creature::GetEntry)
        ];

    sLog.outString("Hooks Initialized");
}