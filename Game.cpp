/*
Disquiet: a horror game written in C++ using SFML and FMOD Events.
Copyright (C) 2013 William James Dyce.

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

#include "Game.hpp"

//!-----------------------------------------------------------------------------
//! CONSTANTS
//!-----------------------------------------------------------------------------

#define N_CELLS_W 20
#define N_CELLS_H 10
#define PERCENT_BROKEN_WALLS 35
#define VIEW_W 200
#define VIEW_H 100

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Game::Game() :
maze(uV2(N_CELLS_W, N_CELLS_H), PERCENT_BROKEN_WALLS),
maze_view(maze),
player(fV2(N_CELLS_W, N_CELLS_H) * NavCell::SIZE * 0.5f),
monster(fV2(50,50)),
gun(fV2(100,100)),
view(fV2(0,0), fV2(VIEW_W, VIEW_H))
{

}

Game::~Game()
{
}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

void Game::renderTo(sf::RenderTarget& target)
{
  // draw maze
  maze_view.renderTo(target);

  // draw gun
  gun.renderTo(target);

  // draw monster
  monster.renderTo(target);

  // draw player
  player.renderTo(target);

}

int Game::update(unsigned long delta_time)
{
  // update player and recentre view
  player.update(delta_time);
  //maze.applyPhysics(player);
  view.setCenter(player.position.x, player.position.y);

  // all clear!
  return CONTINUE;
}

