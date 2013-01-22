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
#include "Menu.hpp"
#include "global.hpp"
#include "audio/global_audio.hpp"

// window
#define WINDOW_W 640
#define WINDOW_H 320
#define MAX_FPS 30
#define WINDOW_TITLE "Disquiet"

// debug mode ?
#define USE_VIEW 0


//!-----------------------------------------------------------------------------
//! FUNCTION INTERFACES
//!-----------------------------------------------------------------------------
int treatEvents(sf::Window &window, Scene *scene);
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
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H),
                          WINDOW_TITLE, sf::Style::None);

  window.setPosition(iV2((sf::VideoMode::getDesktopMode().width/2)-WINDOW_W/2,
                      (sf::VideoMode::getDesktopMode().height/2)-WINDOW_H/2));

  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);
  window.setKeyRepeatEnabled (false);
  window.setFramerateLimit(MAX_FPS);


  // create application states
  Menu menu;
  Game game;
  Scene *scene = &menu;

  // start music / ambient
  audio_event(STORM);

  // background colour
  sf::Color clear_colour(0, 0, 10, 255);

  // main loop
  while (window.isOpen())
  {
    // update
    int eventResult = treatEvents(window, scene);
    int updateResult = scene->update(getDelta());

    // exit
    if(eventResult == STOP || updateResult == STOP)
    {
      if(scene == &menu)
        window.close();
      else
      {
        #if USE_VIEW
          window.setView(window.getDefaultView());
        #endif
        scene = &menu;
      }

    }

    // next scene
    else if(eventResult == NEXT || updateResult == NEXT)
    {
      if(scene == &menu)
        scene = &game;
      game.reset();
    }

    // redraw the game
    window.clear(clear_colour);
    #if USE_VIEW
    if(scene == &game)
      window.setView(game.view);
    #endif
    scene->renderTo(window);
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
int treatEvents(sf::Window &window, Scene *scene)
{
  static sf::Event event;
  while (window.pollEvent(event))
  {
    // treat events in Scene
    int result = scene->treatEvent(event);
    if(result != CONTINUE)
      return result;

    // treat ESC key
    if(event.type == sf::Event::KeyPressed
    && event.key.code == sf::Keyboard::Escape)
      return STOP;

    // treat close button
    if(event.type == sf::Event::Closed)
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

  return (now - last);
}
