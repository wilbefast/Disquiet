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

#ifndef NAVGRID_HPP_INCLUDED
#define NAVGRID_HPP_INCLUDED

#include "../math/V2.hpp"
#include "../math/Rect.hpp"

#include "NavCell.hpp"


class NavGrid
{
  //! FRIENDS
friend class NavHouseGridView;

  //! CONSTANTS
public:
  static const iV2 N, S, E, W, NE, SE, NW, SW;

  //! ATTRIBUTES
public:
    const uV2 n_cells;
protected:
  fV2 origin;
  NavCell ***cells;

  //! METHODS
public:
  // constructors, destructors
  NavGrid(fV2 origin_, uV2 grid_size_);
  virtual ~NavGrid();

  // accessors
  fV2 getOrigin() const;
  uV2 const& getNCells() const;

  // mutators
  void setObstacle(iV2 grid_position, bool new_value);
  void setObstacle(fV2 position, bool new_value);

  // collision testing
  bool isBorder(iV2 grid_position) const;
  bool isObstacle(iV2 grid_position) const;
  bool isObstacle(fV2 position) const;
  bool isValidGridPos(iV2 grid_position) const;
  size_t countSideObstacles(iV2 grid_position) const;
  size_t countDiagonalObstacles(iV2 grid_position) const;

  // conversion
  uV2 vertexToGridPos(fV2 position) const;
  fV2 gridPosToVertex(uV2 grid_position) const;

  // pathing
  bool isLineOfSight(iV2 start, iV2 end) const;
  bool isLineOfSight(fV2 start, fV2 end) const;
};

#endif // NAVGRID_HPP_INCLUDED

