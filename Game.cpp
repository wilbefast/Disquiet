/*
Disquiet: a horror game written in C++ using SFML and FMOD Events.
Copyright (C) 2012 William James Dyce, Kevin Bradshaw

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
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Game::Game() :
first_node(new LevelNode(fV2())),
first_object(NULL),
player(first_node)
//! TODO monster
{
  // create some level nodes
  LevelNode *n1 = new LevelNode(fV2(120, 30)),
            *n2 = new LevelNode(fV2(70, 200)),
            *n3 = new LevelNode(fV2(350, 120));

  // store them instrusively
  first_node->newNext(n1);
  n1->newNext(n2);
  n2->newNext(n3);

  // connect them appropriately
  first_node->connectTo(n1);
  n1->connectTo(n2);
  n1->connectTo(n3);
  n2->connectTo(n3);
}

Game::~Game()
{
  // free all level nodes and game objects
  first_node->deleteConnections();
  first_object->deleteConnections();
}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

void Game::renderTo(sf::RenderTarget& target)
{
  // draw the nodes (debug only)
  current_node = first_node;
  do
  {
    current_node->renderTo(target);
    current_node = (LevelNode*)current_node->getNext();
  }
  while(current_node != first_node);

  // draw non-controlled game objects
  if(first_object)
  {
    current_object = first_object;
    do
    {
      current_object->renderTo(target);
      current_object = (GameObject*)current_object->getNext();
    }
    while(current_object != first_object);
  }

  // draw the player and monster last (painter's algorithm)
  player.renderTo(target);
  //! TODO monster.renderTo(target);
}

int Game::update(unsigned long delta_time)
{
  // update the player and monster first
  player.update(delta_time);
  //! TODO monster.update(delta_time);

  // update non-controlled game objects
  if(first_object)
  {
    current_object = first_object;
    do
    {
      current_object->update(delta_time);
      current_object = (GameObject*)current_object->getNext();
    }
    while(current_object != first_object);
  }

  // all clear!
  return CONTINUE;
}

