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

#include "LevelNode.hpp"

#include <SFML/Graphics.hpp>

#define DRAW_SIZE 16

//! CONSTRUCTORS, DESTRUCTORS

LevelNode::LevelNode(fV2 _position) :
position(_position)
{

}

//! MUTATORS

void LevelNode::renderTo(sf::RenderTarget& target)
{
  // draw the node
  sf::CircleShape circle(DRAW_SIZE);
  circle.setPosition(sf::Vector2f(position.x-DRAW_SIZE, position.y-DRAW_SIZE));
  target.draw(circle);

  // draw links
  for(unsigned int i = 0; i < N_NEIGHBOURS; i++) if(neighbours[i])
  {
    sf::Vertex line[2] = { position, neighbours[i]->position };
    target.draw(line, 2, sf::Lines);
  }
}
