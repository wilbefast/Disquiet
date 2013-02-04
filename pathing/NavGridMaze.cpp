/*
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under he terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "NavGridMaze.hpp"

#include "unistd.h" // for sleep

//! ----------------------------------------------------------------------------
//! PRIVATE FUNCTIONS
//! ----------------------------------------------------------------------------

static void shuffle_array(const iV2* table[], size_t length)
{
  for(size_t i = length-1; i > 0; i--)
  {
    int rand_i = rand()%(i+1);
    const iV2* swap = table[i];
    table[i] = table[rand_i];
    table[rand_i] = swap;
  }
}

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------


NavGridMaze::NavGridMaze(uV2 grid_size_, size_t percent_broken_walls) :
NavGrid(ORIGIN2(float), grid_size_)
{
}

//! ----------------------------------------------------------------------------
//! ASSIGN GRAPHICS TO CELLS
//! ----------------------------------------------------------------------------

void NavGridMaze::reset_type(iV2 pos)
{
  if(!isValidGridPos(pos))
    return;

  NavCell::type_t type = NavCell::CORRIDOR;

  if(isObstacle(pos))
    type = NavCell::WALL;
  else
  {
    iV2 pos_north(pos.x, pos.y - 1);
    if(!isObstacle(pos_north))
      type = NavCell::LANDING;

    else
      type = (rand() % 2) ? NavCell::WINDOW : NavCell::CORRIDOR;
  }

  cells[pos.y][pos.x]->type = type;
}

//! ----------------------------------------------------------------------------
//! GENERATE A PERFECT MAZE
//! ----------------------------------------------------------------------------

void NavGridMaze::regenerate(size_t percent_broken_walls)
{
  // reset all cells to be filled
  iV2 pos;
  for(pos.y = 0; pos.y < (int)n_cells.y; pos.y ++)
  for(pos.x = 0; pos.x < (int)n_cells.x; pos.x ++)
    setObstacle(pos, true);

  // initial maze starts in the middle
  dig_maze(iV2(n_cells.x/2, n_cells.y/2));

  // starting at top-left: break some extra walls, just for fun
  break_walls(percent_broken_walls);

  // determine types for each cell
  for(pos.y = 0; pos.y < (int)n_cells.y; pos.y ++)
  for(pos.x = 0; pos.x < (int)n_cells.x; pos.x ++)
    reset_type(pos);
}

void NavGridMaze::dig_maze(iV2 start_pos)
{
  // dig out the current block
  setObstacle(start_pos, false);

  // shuffle direction order
  const iV2* dir[] = { &N, &S, &E, &W};
  shuffle_array(dir, 4);


  for(size_t i = 0; i < 4; i++)
  {
    // strike the earth!
    iV2 step = start_pos + *(dir[i]), two_steps = step + *(dir[i]);
    if(isObstacle(two_steps) && !isBorder(two_steps)) // stop case
    {
      setObstacle(step, false);
      dig_maze(two_steps); // recursive call
    }
  }
}

//! ----------------------------------------------------------------------------
//! BREAK SOME WALLS DOWN TO MAKE IT IMPERFECT
//! ----------------------------------------------------------------------------


void NavGridMaze::break_walls(size_t percent_broken_walls)
{
  iV2 pos;
  for(pos.y = 0; pos.y < (int)n_cells.y; pos.y ++)
  for(pos.x = 0; pos.x < (int)n_cells.x; pos.x ++)
  // don't clear the whole map!
  if((rand() % 100) < (int)percent_broken_walls
  // destroy 'walls' only, for a more aesthetic effect
  && isObstacle(pos)
  && !isBorder(pos)
  && isOnLine(pos))
  {
    // objects should not be able to leave the map
    if(!isBorder(pos))
      setObstacle(pos, false);
  }
}

//! ----------------------------------------------------------------------------
//! COLLISIONS
//! ----------------------------------------------------------------------------

void NavGridMaze::snapCollider(fV2& collider) const
{


}
