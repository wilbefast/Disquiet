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

#ifndef GUN_HPP_INCLUDED
#define GUN_HPP_INCLUDED

#include "GameObject.hpp"

class Gun : public GameObject
{
public:
  //! ATTRIBUTES

  //! METHODS
  // constructors, destructors
  Gun(fV2 position_);
  virtual ~Gun() {}
  // mutators
  int update(unsigned long delta);
  void renderTo(sf::RenderTarget& target);
};

#endif // GUN_HPP_INCLUDED
