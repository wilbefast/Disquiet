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

#ifndef GRIDHOUSEVIEW_HPP_INCLUDED
#define GRIDHOUSEVIEW_HPP_INCLUDED

#include "../pathing/NavGrid.hpp"

class GridHouseView
{
  //! CONSTANTS
public:
  static const sf::Color C_CORRIDOR[2], C_FLOOR[2], C_WINDOW[2],
                          C_STAIRS[2], C_STEPS[2];


  //! ATTRIBUTES
private:
  NavGrid const& grid;

  //! METHODS
public:
  // constructors, destructors
  GridHouseView(NavGrid const& grid_);
  virtual ~GridHouseView();
  // mutators
  void renderTo(sf::RenderTarget &target, bool lightning);
};

#endif // GRIDHOUSEVIEW_HPP_INCLUDED
