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
#include <climits>

#define DRAW_SIZE 16

using namespace std;

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

LevelNode::LevelNode(fV2 _position) :
position(_position)
{
  // set all neighbours to NULL
  for(unsigned int i = 0; i < N_NEIGHBOURS; i++)
    neighbours[i] = NULL;
}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

void LevelNode::renderTo(sf::RenderTarget& target) const
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

int LevelNode::connectTo(LevelNode* other)
{
  // check that there is a free neighbourhood slot available for other nodes
  int this_index = this->indexFreeNeighbour(),
      other_index = other->indexFreeNeighbour();
  if(this_index < 0 || other_index < 0)
    return -1;

  // if all is well, connect the nodes and re-sort to maintain order
  this->neighbours[this_index] = other;
  this->polarSortNeighbours();
  other->neighbours[other_index] = this;
  other->polarSortNeighbours();

  // return the allocated index
  return this_index;
}

//!-----------------------------------------------------------------------------
//! OUSTREAM
//!-----------------------------------------------------------------------------

void LevelNode::print(std::ostream& stream) const
{
  stream << "LevelNode @ " << position;
  for(unsigned int i = 0; i < N_NEIGHBOURS; i++)
  {
    if(neighbours[i])
      stream << "\n\t" << i << ". " << neighbours[i]->position;
  }
}

std::ostream& operator<<(std::ostream& stream, LevelNode const& n)
{
  n.print(stream);
  return stream;
}

//!-----------------------------------------------------------------------------
//! SUBROUTINES
//!-----------------------------------------------------------------------------

int LevelNode::indexFreeNeighbour() const
{
  for(unsigned int i = 0; i < N_NEIGHBOURS; i++)
    if(!neighbours[i])
      // neighbour i is the first free neighbour
      return i;

  // no free neighbours
  return -1;
}

// polar sort: O(nlogn) to get all the neighbours sorted counter-clockwise
static fV2* centre;
int comparePolar(const void * a, const void * b)
{
  LevelNode *aa = (*(LevelNode**)a), *bb = (*(LevelNode**)b);
  if(!aa && !bb)
    return 0;
  else if(!aa)
    return INT_MIN;
  else if(!bb)
    return INT_MAX;
  else
    return(det(*centre, aa->position) - det(*centre, bb->position));
}
void LevelNode::polarSortNeighbours()
{
  centre = &position;
  qsort(neighbours, N_NEIGHBOURS, sizeof(LevelNode*), comparePolar);
}
