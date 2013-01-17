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

#include "Policies/SingletonImp.h"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <ace/Singleton.h>
#include <luabind/luabind.hpp>

struct CreatureLuaScript
{
    uint32 type;
    const char* name;
};

enum eCreatureLuaEvents
{
    eLuaCreatureEnterCombat        = 0,
    eLuaCreatureLeaveCombat        = 1,
};

typedef std::list<CreatureLuaScript> CreatureLuaEvents;
typedef UNORDERED_MAP<uint32,CreatureLuaEvents> CreatureLuaScripts;

class LuaEngine
{
    friend class ACE_Singleton<LuaEngine, ACE_Thread_Mutex>;

    public:
        void Initialize();
        void AddHooks();

		void LuaCreatureEnterCombat(Creature* cr, Unit* victim);

    protected:
        lua_State* m_luaState;
        const char* m_file;

    public:
        CreatureLuaScripts creaturescripts;

};

#define sLuaEngine MaNGOS::Singleton<LuaEngine>::Instance()
#define sLua ACE_Singleton<LuaEngine, ACE_Thread_Mutex>::instance()