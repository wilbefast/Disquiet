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

#include "../global.hpp" // for CONTINUE

//!-----------------------------------------------------------------------------
//! CONSTANTS
//!-----------------------------------------------------------------------------

const float Player::SPEED = 0.015f;

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS
//!-----------------------------------------------------------------------------

Player::Player(fV2 position_) :
GameObject(position_)
{

}


//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

int Player::update(unsigned long delta)
{
  return CONTINUE;
}

//!-----------------------------------------------------------------------------
//! DRAW
//!-----------------------------------------------------------------------------

static fV2 stamp_size(5.0f, 10.0f);
static sf::RectangleShape stamp(stamp_size);

void Player::renderTo(sf::RenderTarget& target)
{
  stamp.setPosition(position - stamp_size * 0.5f);
  target.draw(stamp);
}
