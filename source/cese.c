/*
 * CESE: Component Entiry Storage Engine
 * Copyright (C) 2015  David Ulrich
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/* ===== Stdlib Includes ===== */
#include <stdbool.h>
#include <stdio.h>

/* ===== Lua Includes ===== */
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


typedef struct CESE_config {
	int test;
} CESE_config;

static int CESE_config_length = 1;
const char * const CESE_config_options[1] = {
	"test"
};

static void CESE_config_load (char *path, CESE_config *config) {
	int i;
	
	lua_State* L;
	L = luaL_newstate();
	luaL_openlibs(L);
	
	if (luaL_loadfile(L,path) || lua_pcall(L,0,0,0)) {
		printf("error in config.lua: %s",lua_tostring(L,-1));
	}
	
	for(i=0;i<CESE_config_length;i++) {
		lua_getglobal(L,CESE_config_options[i]);
		
		if (lua_isnumber(L,-1)) {
			config->test = (int)lua_tonumber(L,-1);
			
		}
		else {
			printf("-1:%s\n",lua_tostring(L,-2));
			config->test = 12;
		}
	}
	
	lua_close(L);
}


int main() {
	CESE_config config;
	
	CESE_config_load("config/config.lua",&config);
	
	printf("test: %d\n",config.test);
	
	return 0;
}
