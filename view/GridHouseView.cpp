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
//! DRAW -- CONSTANTS
//! ----------------------------------------------------------------------------

#define WINDOW_SIZE 0.4f
#define N_STEPS_STAIRS 5
#define STEP_SIZE (1.0f / N_STEPS_STAIRS)

const sf::Color GridHouseView::C_CORRIDOR[2] = { sf::Color(90, 90, 100),
                                          sf::Color(140, 140, 150)};
const sf::Color GridHouseView::C_FLOOR[2] = { sf::Color(50, 50, 70),
                                          sf::Color(100, 100, 120)};
const sf::Color GridHouseView::C_WINDOW[2] = { sf::Color(0, 0, 10),
                                          sf::Color(255, 255, 255)};
const sf::Color GridHouseView::C_STAIRS[2] = { sf::Color(70, 70, 100),
                                          sf::Color(120, 120, 150)};
const sf::Color GridHouseView::C_STEPS[2] = { sf::Color(20, 20, 50),
                                          sf::Color(70, 70, 100)};

static sf::RectangleShape corridor_stamp(
                 fV2(NavCell::SIZE.x, NavCell::wall_h));

static sf::RectangleShape floor_stamp(
                  fV2(NavCell::SIZE.x, NavCell::floor_z));

static sf::RectangleShape window_stamp(
                  fV2(NavCell::SIZE.x * WINDOW_SIZE,
                      WINDOW_SIZE * NavCell::floor_z));

static sf::RectangleShape stairs_stamp(
                  fV2(NavCell::SIZE.x, NavCell::SIZE.y));

static sf::RectangleShape landing_stamp(
                  fV2(NavCell::SIZE.x, NavCell::wall_h));

static const fV2 floor_offset(0, NavCell::wall_h);

static const fV2 window_offset = fV2((0.5f - WINDOW_SIZE/2) * NavCell::SIZE.x,
                                      0.2f * NavCell::SIZE.y);


//! ----------------------------------------------------------------------------
//! DRAW -- PRIVATE INLINE FUNCTIONS
//! ----------------------------------------------------------------------------

static inline void draw_floor(sf::RenderTarget &target, fV2 pos)
{
  floor_stamp.setPosition(pos + floor_offset);
  target.draw(floor_stamp);
}

static inline void draw_corridor(sf::RenderTarget &target, fV2 pos)
{
  corridor_stamp.setPosition(pos);
  target.draw(corridor_stamp);
}

static inline void draw_window(sf::RenderTarget &target, fV2 pos)
{
  window_stamp.setPosition(pos + window_offset);
  target.draw(window_stamp);
}

static inline void draw_landing(sf::RenderTarget &target, fV2 pos, bool lightning)
{
  // draw landing background
  landing_stamp.setPosition(pos);
  target.draw(landing_stamp);

  // draw steps
  sf::VertexArray steps(sf::Lines, (N_STEPS_STAIRS-1) * 2 );
  for(size_t i = 0; i < N_STEPS_STAIRS-1; i++)
  {
    float y = pos.y + i*STEP_SIZE*NavCell::SIZE.y;
    steps[2*i].position = sf::Vector2f(pos.x, y);
    steps[2*i + 1].position = sf::Vector2f(pos.x + NavCell::SIZE.x, y);
    steps[2*i].color = steps[2*i + 1].color
                     = GridHouseView::C_STEPS[lightning ? 1 : 0];
  }
  target.draw(steps);
}

static inline void draw_stairs(sf::RenderTarget &target, fV2 pos, bool lightning)
{
  // draw stairs background
  stairs_stamp.setPosition(pos);
  target.draw(stairs_stamp);

  // draw steps
  sf::VertexArray steps(sf::Lines, N_STEPS_STAIRS * 2);
  for(size_t i = 0; i < N_STEPS_STAIRS ; i++)
  {
    float y = pos.y + i*STEP_SIZE*NavCell::SIZE.y;
    steps[2*i].position = sf::Vector2f(pos.x, y);
    steps[2*i + 1].position = sf::Vector2f(pos.x + NavCell::SIZE.x, y);
    steps[2*i].color = steps[2*i + 1].color
                     = GridHouseView::C_STEPS[lightning ? 1 : 0];
  }
  target.draw(steps);
}

//! ----------------------------------------------------------------------------
//! DRAW -- METHODS
//! ----------------------------------------------------------------------------

void GridHouseView::renderTo(sf::RenderTarget &target, bool lighting)
{
  // set palette
  floor_stamp.setFillColor(GridHouseView::C_FLOOR[lighting ? 1 : 0]);
  corridor_stamp.setFillColor(GridHouseView::C_CORRIDOR[lighting ? 1 : 0]);
  window_stamp.setFillColor(GridHouseView::C_WINDOW[lighting ? 1 : 0]);
  stairs_stamp.setFillColor(GridHouseView::C_STAIRS[lighting ? 1 : 0]);
  landing_stamp.setFillColor(GridHouseView::C_STAIRS[lighting ? 1 : 0]);

  // iterate across grid
  static iV2 grid_pos;
  static fV2 pos;
  //! activate the texture BEFORE glBegin

  for(grid_pos.y = 0; grid_pos.y < (int)grid.n_cells.y; grid_pos.y++)
  for(grid_pos.x = 0; grid_pos.x < (int)grid.n_cells.x; grid_pos.x++)
  {
    fV2 pos = grid.gridPosToVertex(grid_pos);

    switch(grid.cells[grid_pos.y][grid_pos.x]->type)
    {
      case NavCell::CORRIDOR:
        draw_floor(target, pos);
        draw_corridor(target, pos);
        break;

      case NavCell::WINDOW:
        draw_floor(target, pos);
        draw_corridor(target, pos);
        draw_window(target, pos);
        break;

      case NavCell::LANDING:
        draw_floor(target, pos);
        draw_landing(target, pos, lighting);
        break;

      case NavCell::STAIRS:
        draw_stairs(target, pos, lighting);
        break;

      case NavCell::WALL:
      default:
        break;
    }
  }
}
