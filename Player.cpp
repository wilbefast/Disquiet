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

#include "Player.hpp"

#define DRAW_SIZE 16

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS
//!-----------------------------------------------------------------------------

Player::Player(LevelNode *_start) :
GameObject(_start)
{

}


//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

int Player::update(unsigned long delta)
{
  // get control direct
  static iV2 arrow_keys;
  arrow_keys = iV2(0,0);
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    arrow_keys.x--;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    arrow_keys.x++;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    arrow_keys.y--;
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    arrow_keys.y++;

  return CONTINUE;
}


void Player::renderTo(sf::RenderTarget& target)
{
  sf::RectangleShape rectangle(fV2(DRAW_SIZE, DRAW_SIZE));
  rectangle.setPosition(getPosition() - fV2(DRAW_SIZE/2, DRAW_SIZE/2));
  rectangle.setFillColor(sf::Color::Blue);
  target.draw(rectangle);
}
