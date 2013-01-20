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
player(fV2(N_CELLS_W + 1, N_CELLS_H) * 0.5f * NavCell::SIZE
       + fV2(0, NavCell::wall_h + 0.5f*NavCell::floor_z)),
monster(fV2(50,50)),
gun(fV2(100,100)),
view(fV2(0,0), fV2(VIEW_W, VIEW_H))
{
  maze.regenerate(PERCENT_BROKEN_WALLS);
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
  // treat input
  static fV2 arrow_keys;
  arrow_keys = fV2(0,0);
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    arrow_keys.x--;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    arrow_keys.x++;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    arrow_keys.y--;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    arrow_keys.y++;

  fV2 new_position = player.position + arrow_keys * (Player::SPEED * delta_time);

  if(!maze.isIsometricObstacle(new_position))
    player.position = new_position;

  // update player and recentre view
  player.update(delta_time);
  view.setCenter(player.position.x, player.position.y);

  // all clear!
  return CONTINUE;
}

