/*
Copyright (C) 2012 William James Dyce and Guillaume Surroca

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

#include "NavGrid.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

const iV2 NavGrid::N = iV2(0, -1);
const iV2 NavGrid::S = iV2(0, 1);
const iV2 NavGrid::E = iV2(1, 0);
const iV2 NavGrid::W = iV2(-1, 0);
const iV2 NavGrid::NE = iV2(1, -1);
const iV2 NavGrid::SE = iV2(1, 1);
const iV2 NavGrid::NW = iV2(-1, -1);
const iV2 NavGrid::SW = iV2(-1, 1);

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------


NavGrid::NavGrid(fV2 origin_, uV2 n_cells_) :
n_cells(n_cells_),
origin(origin_)
{
  // allocate memory for grid
  cells = new NavCell**[n_cells.y];
  for(unsigned int r = 0; r < n_cells.y; r++)
    cells[r] = new NavCell*[n_cells.x];

  // allocate memory for cells
  uV2 grid_pos;
  for(grid_pos.y = 0; grid_pos.y < n_cells.y; grid_pos.y++)
  for(grid_pos.x = 0; grid_pos.x < n_cells.x; grid_pos.x++)
    cells[grid_pos.y][grid_pos.x] = new NavCell(grid_pos, false);
}

NavGrid::~NavGrid()
{
  // allocate memory from cells
  for(unsigned int r = 0; r < n_cells.y; r++)
    delete[] cells[r];
  delete[] cells;
}

//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------

// mutators
void NavGrid::setObstacle(iV2 grid_position, bool new_value)
{
  if(!isValidGridPos(grid_position))
    return;
  cells[grid_position.y][grid_position.x]->obstacle = new_value;

}

void NavGrid::setObstacle(fV2 position, bool new_value)
{
  setObstacle(iV2(position.x / NavCell::SIZE.x, position.y / NavCell::SIZE.y),
              new_value);
}

//! ----------------------------------------------------------------------------
//! ACCESSORS
//! ----------------------------------------------------------------------------

fV2 NavGrid::getOrigin() const
{
  return origin;
}

//! ----------------------------------------------------------------------------
//! COLLISION-TESTING
//! ----------------------------------------------------------------------------

bool NavGrid::isBorder(iV2 grid_position) const
{
  if(!isValidGridPos(grid_position))
    return true;
  return (grid_position.x == 0 ||
          grid_position.y == 0 ||
          grid_position.x == (int)n_cells.x - 1 ||
          grid_position.y == (int)n_cells.y - 1);
}

bool NavGrid::isObstacle(iV2 grid_position) const
{
  if(!isValidGridPos(grid_position))
    return true;
	return cells[grid_position.y][grid_position.x]->obstacle;
}

bool NavGrid::isObstacle(fV2 position) const
{
  return isObstacle(iV2(position.x / NavCell::SIZE.x, position.y / NavCell::SIZE.y));
}

bool NavGrid::isValidGridPos(iV2 grid_position) const
{
  return (grid_position.x >= 0
          && grid_position.y >= 0
          && grid_position.x < (int)n_cells.x
          && grid_position.y < (int)n_cells.y);
}

//! ----------------------------------------------------------------------------
//! TOPOLOGY
//! ----------------------------------------------------------------------------


bool NavGrid::isOnLine(iV2 grid_position) const
{
  const bool  here = isObstacle(grid_position),
              n = (isObstacle(grid_position + N) == here),
              s = (isObstacle(grid_position + S) == here),
              e = (isObstacle(grid_position + E) == here),
              w = (isObstacle(grid_position + W) == here);
  return ((n && s && !e && !w)
          || (!n && !s && e && w));
}

size_t NavGrid::countSideObstacles(iV2 grid_position) const
{
  size_t count = 0;
  if(isObstacle(grid_position + N)) count ++;
  if(isObstacle(grid_position + S)) count ++;
  if(isObstacle(grid_position + E)) count ++;
  if(isObstacle(grid_position + W)) count ++;
  return count;
}

size_t NavGrid::countDiagonalObstacles(iV2 grid_position) const
{
  size_t count = 0;
  if(isObstacle(grid_position + NE)) count ++;
  if(isObstacle(grid_position + NW)) count ++;
  if(isObstacle(grid_position + SE)) count ++;
  if(isObstacle(grid_position + SW)) count ++;
  return count;
}

NavGrid::neighbourhood_t NavGrid::getNeighbourhood(iV2 grid_position) const
{
  neighbourhood_t result;
  if(isObstacle(grid_position + N)) result.n = true;
  if(isObstacle(grid_position + S)) result.s = true;
  if(isObstacle(grid_position + E)) result.e = true;
  if(isObstacle(grid_position + W)) result.w = true;
  if(isObstacle(grid_position + NE)) result.ne = true;
  if(isObstacle(grid_position + NW)) result.nw = true;
  if(isObstacle(grid_position + SE)) result.se = true;
  if(isObstacle(grid_position + SW)) result.sw = true;
  return result;

}


//! ----------------------------------------------------------------------------
//! CONVERSION
//! ----------------------------------------------------------------------------

uV2 NavGrid::vertexToGridPos(fV2 position) const
{
	return uV2(position.x/NavCell::SIZE.x, position.y/NavCell::SIZE.y);
}

fV2 NavGrid::gridPosToVertex(uV2 position) const
{
  return fV2(origin.x + position.x*NavCell::SIZE.x,
             origin.y + position.y*NavCell::SIZE.y);
}

//! ----------------------------------------------------------------------------
//! PATHING
//! ----------------------------------------------------------------------------

bool NavGrid::isLineOfSight(iV2 start, iV2 end) const
{
  if(!isValidGridPos(start) || !isValidGridPos(end))
    return false;

	// http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
  int dx = abs(end.x - start.x),
      dy = abs(end.y - start.y),
      sx = (start.x < end.x) ? 1 : -1,
      sy = (start.y < end.y) ? 1 : -1,
      err = dx - dy;

  while(start.x != end.x || start.y != end.y)
  {
    if(isObstacle(start))
      // the way is shut (it was made by those who are dead)
      return false;

    int err2 = 2*err;

    //  move horizontally
    if(err2 > -dy)
    {
      err -= dy;
      start.x += sx;
    }

    // move vertically
    if(err2 < dx)
    {
      err += dx;
      start.y += sy;
    }
  }

  // made it - the way is clear!
  return true;
}

bool NavGrid::isLineOfSight(fV2 start, fV2 end) const
{
  return isLineOfSight(iV2(start.x / NavCell::SIZE.x, start.y / NavCell::SIZE.y),
                       iV2(end.x / NavCell::SIZE.x, end.y / NavCell::SIZE.y));
}
