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

#ifndef MACHINEPART_HPP_INCLUDED
#define MACHINEPART_HPP_INCLUDED

#include <iostream> // for std::string

extern "C" {
  #include <lua.h> // for lua_Object
}

#define MP_ERROR 0
#define MP_STRING 1
#define MP_NUMBER 2

class MachinePart
{
private:
  //! ATTRIBUTES
  int type;
  double n;
  std::string s;


public:
  
 
  // constructors, destructors
  MachinePart(double num);
  MachinePart(std::string str);
  //MachinePart(lua_Object lobj);
  ~MachinePart() {}

  //! METHODS
  int getType();
  double getNumber();
  std::string getString();



  // mutators
};

#endif // MACHINEPART_HPP_INCLUDED
