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

#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#define CONTINUE 1
#define STOP 0

#include "math/V2.hpp"
#include "utils/IntrusiveLinked.hpp"

#include <SFML/Graphics.hpp>  // for Vector2.hpp

class GameObject : public IntrusiveLinked
{
  //! ATTRIBUTES
private:
  fV2 position;
  //! METHODS
public:
  // constructors, destructors
  GameObject(fV2 position_);
  virtual ~GameObject();
  // mutators
  virtual void renderTo(sf::RenderTarget &target);
  virtual int update(unsigned long delta_time);
  // accessors
  fV2 getPosition() const;
};

#endif // GAMEOBJECT_HPP_INCLUDED
