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

#include "NavCell.hpp"

//! ----------------------------------------------------------------------------
//! CONSTANTS
//! ----------------------------------------------------------------------------

const fV2 NavCell::SIZE = fV2(CELL_W, CELL_H);
const float NavCell::floor_z = CELL_Z;
const float NavCell::wall_h = CELL_WALL_H;

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

NavCell::NavCell(uV2 grid_position_) :
grid_position(grid_position_),
vertex_position((fV2)grid_position_ * SIZE)
{
}

NavCell::~NavCell()
{
}
