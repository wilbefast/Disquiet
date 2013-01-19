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

#define N_CELLS_W 15
#define N_CELLS_H 15
#define PERCENT_BROKEN_WALLS 50

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Game::Game() :
maze(uV2(N_CELLS_W, N_CELLS_H), PERCENT_BROKEN_WALLS),
maze_view(maze),
player(fV2(100, 100))
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
  maze_view.renderTo(target);
}

int Game::update(unsigned long delta_time)
{

  // all clear!
  return CONTINUE;
}

