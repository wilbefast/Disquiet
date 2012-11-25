/*
Disquiet: a horror game written in C++ using SFML and FMOD Events.
Copyright (C) 2012 William James Dyce, Kevin Bradshaw

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LUAMACHINE_HPP_INCLUDED
#define LUAMACHINE_HPP_INCLUDED

#include <iostream> // for std::string

extern "C" {
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

class LuaMachine
{
public:
 
  //! ATTRIBUTES
  lua_State *L;
 
  // constructors, destructors
  LuaMachine();
  LuaMachine(std::string initscript);
  ~LuaMachine() {}

  //! METHODS

  // These methods are mostly used as a stack-neutral wrapper to the lua_State
  // stack neutral means that the stack is left with as many elements before and
  // after the call, this is considered good programming practice in that is has
  // a tendancy to not break or cause memory issues.

  // If you need to access the lua_State directly, it's public, so you can do:

  // lua_getfield(LMach.L, LUA_GLOBALSINDEX, "update");
  // lua_call(LMach.L, 0, 0);

  // Instead of the (safer) :
  // LMach.call("update");

  // Do stuff described in a string or file "script"
  void loadFile(std::string script);
  void loadString(std::string script);

  // Add a function to be used from within Lua
  void registerFunction(std::string tablespace, lua_CFunction func);
  // It's cleaner and better to use namespaces, but Lua is all about freedom
  void registerFunction(lua_CFunction func);

  // Set Lua value "name" to have value "val"
  // If you want (and you should) to use namespace tables, then seperate the
  // name with "." like this:
  // LMach.set("disquiet.player.hitpoints", 100);
  void set(std::string name, std::string val);
  void set(std::string name, double val);

  // mutators
};

#endif // LUAMACHINE_HPP_INCLUDED
