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
#include "utils/IntrusiveLinked.hpp"

#define N_NEIGHBOURS 4

class LevelNode : public IntrusiveLinked
{
  //! ATTRIBUTES
public:
  fV2 position;
private:
  LevelNode *neighbours[N_NEIGHBOURS];

  //! METHODS
public:
  // constructors, destructors
  LevelNode(fV2 _position);
  ~LevelNode() {}
  // mutators
  void renderTo(sf::RenderTarget& target) const;
  int connectTo(LevelNode* other); // return index allocated, or -1 if failure
  
  //! SUBROUTINES
private:
  int indexFreeNeighbour() const; // return -1 if there is no free neighbour
};

#endif // LEVELNODE_HPP_INCLUDED
