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
#define PERCENT_BROKEN_WALLS 45
#define VIEW_W 200
#define VIEW_H 100

#define MIN_DIST_TO_MONSTER 6
#define MIN_DIST_TO_GUN 8

#define SPAWN_OFFSET fV2(CELL_W * 0.5f, CELL_WALL_H + 0.5f*CELL_Z)

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Game::Game() :
maze(uV2(N_CELLS_W, N_CELLS_H), PERCENT_BROKEN_WALLS),
maze_view(maze),
player(fV2(N_CELLS_W, N_CELLS_H) * 0.5f * NavCell::SIZE + SPAWN_OFFSET),
monster(fV2()),
gun(fV2()),
view(fV2(), fV2(VIEW_W, VIEW_H))
{
  // generate maze
  maze.regenerate(PERCENT_BROKEN_WALLS);

  // place gun
  iV2 player_cell(N_CELLS_W / 2, N_CELLS_H / 2), spawn_cell;
  do { spawn_cell = iV2(rand()%N_CELLS_W, rand()%N_CELLS_H); }
  while(maze.isObstacle(spawn_cell) ||
        (player_cell - spawn_cell).getNorm() < MIN_DIST_TO_GUN);
  gun.position = maze.gridPosToVertex(spawn_cell) + SPAWN_OFFSET;

  // place monster
  do { spawn_cell = iV2(rand()%N_CELLS_W, rand()%N_CELLS_H); }
  while(maze.isObstacle(spawn_cell) ||
        (player_cell - spawn_cell).getNorm() < MIN_DIST_TO_MONSTER);
  monster.position = maze.gridPosToVertex(spawn_cell) + SPAWN_OFFSET;

  // calculate monster initial path
  maze.getPath(spawn_cell, player_cell, &(monster.path));
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

static fV2 const& getArrowDirection()
{
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
  arrow_keys.normalise();
  return arrow_keys;
}

int Game::update(unsigned long delta_time)
{
  // treat input
  fV2 new_position = player.position + getArrowDirection() * (Player::SPEED * delta_time),
      new_position_x(new_position.x, player.position.y),
      new_position_y(player.position.x, new_position.y);
  if(maze.isIsometricObstacle(new_position_x))
    new_position.x = player.position.x;
  if(maze.isIsometricObstacle(new_position_y))
    new_position.y = player.position.y;
  player.position = new_position;

  // update player and recentre view
  player.update(delta_time);
  view.setCenter(player.position.x, player.position.y);

  // update monster
  monster.update(delta_time);
  iV2 target_cell = monster.path.back()->grid_position,
      player_cell = maze.vertexToGridPos(player.position);
  if((target_cell.x != player_cell.x) || (target_cell.y != player_cell.y))
    maze.getPath((iV2)maze.vertexToGridPos(monster.position),
                 player_cell, &(monster.path));

  // all clear!
  return CONTINUE;
}

