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

#include "Game.hpp"
#include "audio/global_audio.hpp"


#define WINDOW_W 640
#define WINDOW_H 320
#define MAX_FPS 30
#define WINDOW_TITLE "Disquiet"

#define USE_VIEW 0

//!-----------------------------------------------------------------------------
//! FUNCTION INTERFACES
//!-----------------------------------------------------------------------------
int treatEvents(sf::Window &window);
unsigned long getDelta();
//!-----------------------------------------------------------------------------

//!-----------------------------------------------------------------------------
//! MAIN
//!-----------------------------------------------------------------------------
int main(int argc, char** argv, char** envp)
{
  // start audio interface
  start_audio();

  // open window
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

  window.setPosition(iV2((sf::VideoMode::getDesktopMode().width/2)-WINDOW_W/2,
                      (sf::VideoMode::getDesktopMode().height/2)-WINDOW_H/2));

  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(MAX_FPS);

  // create game instance
  Game game;

  // main loop
  while (window.isOpen())
  {
    // deal with events
    if(treatEvents(window) == STOP)
      window.close();

    // update the game
    if(game.update(getDelta()) == STOP)
      window.close();

    // redraw the game
    window.clear();

    #if USE_VIEW
      window.setView(game.view);
    #endif
    game.renderTo(window);
    window.display();
  }

  // stop audio interface
  stop_audio();

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
    // escape or close button
    if (event.type == sf::Event::Closed
    || (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape))
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
