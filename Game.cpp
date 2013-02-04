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

#include "global.hpp"
#include "audio/global_audio.hpp"

//!-----------------------------------------------------------------------------
//! CONSTANTS
//!-----------------------------------------------------------------------------

#define N_CELLS_W 40
#define N_CELLS_H 10
#define PERCENT_BROKEN_WALLS 45
#define VIEW_W 200
#define VIEW_H 100

#define MIN_DIST_TO_GUN 8

#define GUN_GRAB_DISTANCE 10
#define GUN_GRAB_DISTANCE2 (GUN_GRAB_DISTANCE * GUN_GRAB_DISTANCE)
#define MONSTER_GRAB_DISTANCE 16
#define MONSTER_GRAB_DISTANCE2 (MONSTER_GRAB_DISTANCE * MONSTER_GRAB_DISTANCE)
#define CRITICAL_DANGER_DISTANCE 96
#define CRITICAL_DANGER_DISTANCE2 (CRITICAL_DANGER_DISTANCE \
                                   * CRITICAL_DANGER_DISTANCE)

#define SPAWN_OFFSET fV2(CELL_W * 0.5f, CELL_WALL_H + 0.5f*CELL_Z)

#define LIGHTNING_DURATION 200
#define LIGHTNING_DURATION_V 300
#define LIGHTNING_PERIOD 8000
#define LIGHTNING_PERIOD_V 10000

#define FOOTSTEP_PERIOD 300

#define GROWL_PERIOD 3000
#define GROWL_PERIOD_V 1000

// debug mode ?
#define HIDE_MONSTER 1
#define USE_VIEW 1

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Game::Game() :
maze(uV2(N_CELLS_W, N_CELLS_H), PERCENT_BROKEN_WALLS),
maze_view(maze),
footstep_counter(FOOTSTEP_PERIOD),
player(fV2()),
monster(fV2()),
gun(fV2()),
view(fV2(), fV2(USE_VIEW ? VIEW_W : 0, USE_VIEW ? VIEW_H : 0))
{
}

Game::~Game()
{
}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

void Game::reset()
{
  // reset timer
  footstep_counter = FOOTSTEP_PERIOD;
  growl_counter = GROWL_PERIOD;
  storm_counter = LIGHTNING_PERIOD;
  lightning_counter = 0;

  // generate maze
  maze.regenerate(PERCENT_BROKEN_WALLS);

  // place player
  iV2 player_cell(N_CELLS_W / 2, N_CELLS_H / 2);
  player.position = maze.gridPosToVertex(player_cell) + SPAWN_OFFSET;

  // place gun and monster
  iV2 spawn_cell;
  do { spawn_cell = iV2(rand()%N_CELLS_W, rand()%N_CELLS_H); }
  while(maze.isObstacle(spawn_cell) ||
        (player_cell - spawn_cell).getNorm() < MIN_DIST_TO_GUN);
  gun.position = monster.position
               = maze.gridPosToVertex(spawn_cell) + SPAWN_OFFSET;
  // calculate monster initial path
  maze.getPath(spawn_cell, player_cell, &(monster.path));
}

//!-----------------------------------------------------------------------------
//! OVERRIDES
//!-----------------------------------------------------------------------------

void Game::renderTo(sf::RenderTarget& target)
{
  // draw maze
  maze_view.renderTo(target, lightning_counter > 0);

  // draw gun
  gun.renderTo(target);

  // draw monster
  #if HIDE_MONSTER
  if(lightning_counter > 0)
  #endif
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
  fV2 arrows = getArrowDirection(),
      new_position = player.position + arrows * (Player::SPEED * delta_time),
      new_position_x(new_position.x, player.position.y),
      new_position_y(player.position.x, new_position.y);

  //! --------------------------------------------------------------------------
  //! Player - update position

  // is there any input?
  if(arrows.x || arrows.y)
  {
    if(maze.isIsometricObstacle(new_position_x))
      new_position.x = player.position.x;
    if(maze.isIsometricObstacle(new_position_y))
      new_position.y = player.position.y;
    player.position = new_position;

    // play footstep sound when moving
    if(player.position.x == new_position.x || player.position.y == new_position.y)
    {
      if(footstep_counter > 0)
        footstep_counter -= delta_time;
      else
      {
        audio_event(FOOTSTEP);
        footstep_counter = FOOTSTEP_PERIOD;
      }
    }
  }

  //! --------------------------------------------------------------------------
  //! Player - reset view

  // update player and recentre view
  player.update(delta_time);
  view.setCenter(player.position.x, player.position.y);

  //! --------------------------------------------------------------------------
  //! Lightning

  // flash lighting if need be
  if(lightning_counter > 0)
    lightning_counter -= delta_time;
  else
  {
    if(storm_counter > 0)
      storm_counter -= delta_time;
    else
    {
      audio_event(LIGHTNING);
      storm_counter = LIGHTNING_PERIOD + rand()%LIGHTNING_PERIOD_V;
      lightning_counter = LIGHTNING_DURATION + rand()%LIGHTNING_DURATION_V;
    }
  }

  //! --------------------------------------------------------------------------
  //! Monster - pursue player

  monster.update(delta_time);
  iV2 target_cell = monster.path.back()->grid_position,
      player_cell = maze.vertexToGridPos(player.position),
      monster_cell = maze.vertexToGridPos(monster.position);
  // has the player moved ?
  if((target_cell.x != player_cell.x) || (target_cell.y != player_cell.y))
    // reset monster path
    maze.getPath(monster_cell, player_cell, &(monster.path));

  //! --------------------------------------------------------------------------
  //! Monster - launch sound effects

  if(growl_counter > 0)
    growl_counter -= delta_time;
  else
  {
    audio_event(MONSTER);
    growl_counter = GROWL_PERIOD + rand()%GROWL_PERIOD_V;
  }

  //! --------------------------------------------------------------------------
  //! Monster - parameterise sound effects

  // pan
  float pan = (monster.position.x - player.position.x) / 200 + 0.5;
  if(pan > 1) pan = 1;
  else if(pan < 0) pan = 0;
  audio_event_parameter(PANORAMA, pan);

  // distance
  float distance = std::min((size_t)7, monster.path.size()) / 7.0f;
  audio_event_parameter(DISTANCE, distance);

  // occlusion
  float occlusion =
    std::min((size_t)5, maze.countLineObstacle(monster_cell, player_cell)) / 5.0f;
  audio_event_parameter(OCCLUSION, occlusion);


  // tension
  float beeline_distance2 = (player.position - monster.position).getNorm2();
  float tension = (beeline_distance2 < CRITICAL_DANGER_DISTANCE2)
                    ? 1 - (beeline_distance2 / CRITICAL_DANGER_DISTANCE2)
                    : 0.0f;
  audio_event_parameter(TENSION, tension);

  // send parameters to sound manager
  audio_refresh_parameters();

  //! --------------------------------------------------------------------------
  //! End game conditions

  // kill the player if too close to the monster
  if(beeline_distance2 < MONSTER_GRAB_DISTANCE2)
  {
    // reset tension
    audio_event_parameter(TENSION, 0.0f);
    audio_refresh_parameters();

    audio_event(SCREAM);
    return STOP;
  }


  // end the game if the player reaches the gun
  if((player.position - gun.position).getNorm2() < GUN_GRAB_DISTANCE2)
  {
    audio_event(GUN);
    return STOP;
  }


  //! --------------------------------------------------------------------------
  //! Continue game

  return CONTINUE;
}

int Game::treatEvent(sf::Event& e)
{
  return CONTINUE;
}


