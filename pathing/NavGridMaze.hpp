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

#ifndef NAVGRIDMAZE_HPP_INCLUDED
#define NAVGRIDMAZE_HPP_INCLUDED

#include "NavGrid.hpp"

class NavGridMaze : public NavGrid
{
  //! ATTRIBUTES
public:

  //! METHODS
public:
  // constructors
  NavGridMaze(uV2 grid_size_, size_t percent_broken_walls);

  // mutators
  void regenerate(size_t percent_broken_walls);

  // collisions
  void snapCollider(fV2& collider) const;

  //! SUBROUTINES
private:
  void dig_maze(iV2 start_pos);
  void break_walls(size_t percent_broken_walls);
  void reset_type(iV2 pos);
};

#endif // NAVGRIDMAZE_HPP_INCLUDED
