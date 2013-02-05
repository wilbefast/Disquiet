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

#include "Monster.hpp"

#include "../global.hpp" // for CONTINUE

//!-----------------------------------------------------------------------------
//! CONSTANTS
//!-----------------------------------------------------------------------------

#define DRAW_SIZE 12
#define SPEED 0.01f
#define OFFSET fV2(CELL_W * 0.5f, CELL_WALL_H + 0.5f*CELL_Z)

// debug mode ?
#define RENDER_MONSTER_PATH 0

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS
//!-----------------------------------------------------------------------------

Monster::Monster(fV2 position_, fV2 const& target_) :
GameObject(position_),
target(target_)
{

}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

int Monster::update(unsigned long delta)
{
  fV2 direction;

  // follow path
  if(path.size())
  {
    direction = path.front()->vertex_position - position + OFFSET;
    if(direction.normalise() < SPEED * delta)
      path.pop_front();
  }
  // follow target directly
  else
    direction = target - position;

  position += direction * (SPEED * delta);

  return CONTINUE;
}

//!-----------------------------------------------------------------------------
//! DRAW
//!-----------------------------------------------------------------------------


static fV2 stamp_size(7.0f, 14.0f);
static sf::RectangleShape stamp(stamp_size);

void Monster::renderTo(sf::RenderTarget& target)
{
  stamp.setFillColor(sf::Color::Black);
  stamp.setPosition(position - stamp_size * 0.5f);
  target.draw(stamp);

  #if RENDER_MONSTER_PATH
  sf::VertexArray line(sf::LinesStrip, path.size() + 1);
  line[0].position = position;
  size_t i = 1;
  for(path_t::iterator pit = path.begin(); pit != path.end(); pit++, i++)
    line[i].position = (fV2)((*pit)->grid_position) * (fV2)(NavCell::SIZE) + OFFSET;
  target.draw(line);
  #endif
}
