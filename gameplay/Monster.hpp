/*
Disquiet: a horror game written in C++ using SFML and FMOD Events.
Copyright (C) 2013 William James Dyce

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

#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

#include "GameObject.hpp"
#include "../pathing/Path.hpp"

#define MONSTER_REPATH_INTERVAL 2000

class Monster : public GameObject
{
public:
  //! ATTRIBUTES
  path_t path;

  //! METHODS
  // constructors, destructors
  Monster(fV2 position_);
  virtual ~Monster() {}
  // mutators
  int update(unsigned long delta);
  void renderTo(sf::RenderTarget& target);
};

#endif // MONSTER_HPP_INCLUDED
