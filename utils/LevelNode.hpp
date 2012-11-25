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

#ifndef LEVELNODE_HPP_INCLUDED
#define LEVELNODE_HPP_INCLUDED

#include <SFML/Graphics.hpp>  // for sf::RenderTarget

#include "math/V2.hpp"

#define N_NEIGHBOURS 4

class LevelNode
{
public:
  //! ATTRIBUTES
  fV2 position;
  LevelNode *neighbours[N_NEIGHBOURS];

  //! METHODS
  // constructors, destructors
  LevelNode(fV2 _position);
  ~LevelNode() {}
  // mutators
  void renderTo(sf::RenderTarget& target);
};

#endif // LEVELNODE_HPP_INCLUDED
