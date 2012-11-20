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

#include <stdlib.h> // EXIT_SUCCESS

#include <SFML/Graphics.hpp>
#include "LevelNode.hpp"
#include "Player.hpp"

#define WINDOW_W 640
#define WINDOW_H 480
#define MAX_FPS 30
#define WINDOW_TITLE "Disquiet"

//!-----------------------------------------------------------------------------
//! FUNCTION INTERFACES
//!-----------------------------------------------------------------------------
int treatEvents(sf::Window &window);
unsigned long getDelta();
int update(unsigned long delta_time);
void renderTo(sf::RenderTarget &target);
//!-----------------------------------------------------------------------------

//!-----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//!-----------------------------------------------------------------------------
LevelNode n1(fV2(120, 30)), n2(fV2(70, 200)), n3(fV2(350, 120));
Player p(&n1);

//!-----------------------------------------------------------------------------
//! MAIN
//!-----------------------------------------------------------------------------
int main(int argc, char** argv, char** envp)
{
  // open window
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);
  window.setFramerateLimit(MAX_FPS);

  // create game objects
  n1.neighbours[0] = &n2;
  n1.neighbours[1] = &n3;
  n2.neighbours[2] = &n3;

  // main loop
  while (window.isOpen())
  {
    // deal with events
    if(treatEvents(window) == STOP)
      window.close();

    // update the game
    if(update(getDelta()) == STOP)
      window.close();

    // redraw the game
    renderTo(window);
    window.display();
  }

  // quit
  return EXIT_SUCCESS;
}

//!-----------------------------------------------------------------------------
//! FUNCTION IMPLEMENTATIONS
//!-----------------------------------------------------------------------------
int treatEvents(sf::Window &window)
{
  static sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      return STOP;
  }
  return CONTINUE;
}

unsigned long getDelta()
{
  static sf::Clock clock; // starts the clock
  static unsigned long last, now = clock.getElapsedTime().asMilliseconds();

  last = now;
  now = clock.getElapsedTime().asMilliseconds();

  return (now-last);
}

int update(unsigned long delta_time)
{
  //! COMPLETE ME!

  return CONTINUE;
}

void renderTo(sf::RenderTarget &target)
{
  target.clear();

  n1.renderTo(target);
  n2.renderTo(target);
  n3.renderTo(target);
  p.renderTo(target);

  //! COMPLETE ME!

}
