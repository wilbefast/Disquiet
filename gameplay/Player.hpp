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

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>  // for sf::RenderTarget

#include "GameObject.hpp"
#include "../math/Rect.hpp"

class Player : public GameObject
{
  //! CONSTANTS
public:
  static const float SPEED;

  //! ATTRIBUTES
public:

  //! METHODS
public:
  // constructors, destructors
  Player(fV2 position_);
  virtual ~Player() {}
  // mutators
  int update(unsigned long delta);
  void renderTo(sf::RenderTarget& target);
};

#endif // PLAYER_HPP_INCLUDED
