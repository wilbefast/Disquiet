/*
Copyright (C) 2013 William James Dyce

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

#include "../view/GridHouseView.hpp"


//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GridHouseView::GridHouseView(NavGrid const& grid_) :
grid(grid_)
{
}

GridHouseView::~GridHouseView()
{
}

//! ----------------------------------------------------------------------------
//! DRAW
//! ----------------------------------------------------------------------------

void GridHouseView::renderTo(sf::RenderTarget &target)
{

  static iV2 grid_pos;
  static fV2 pos;
  //! activate the texture BEFORE glBegin

  for(grid_pos.y = 0; grid_pos.y < (int)grid.n_cells.y; grid_pos.y++)
  {
    for(grid_pos.x = 0; grid_pos.x < (int)grid.n_cells.x; grid_pos.x++)
    {
      // check if the cell is a building or a road
      if(grid.isObstacle(grid_pos))
      {
        sf::RectangleShape rectangle(fV2(32, 32));
        rectangle.setPosition(grid.gridPosToVertex(grid_pos));
        rectangle.setFillColor(sf::Color::Blue);
        target.draw(rectangle);
      }
    }
  }
}
