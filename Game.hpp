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

#include "gameplay/GameObject.hpp"
#include "gameplay/Player.hpp"
#include "gameplay/Gun.hpp"
#include "gameplay/Monster.hpp"

#include "pathing/NavGridMaze.hpp"

#include "view/GridHouseView.hpp"

class Game
{
  //! FRIENDS
friend int main(int argc, char** argv, char** envp);

  //! ATTRIBUTES
private:
  // the maze
  NavGridMaze maze;
  GridHouseView maze_view;
  // gameplay object
  Player player;
  Monster monster;
  Gun gun;
  // the view
  sf::View view;

  //! METHODS
public:
  // constructors, destructors
  Game();
  virtual ~Game();

  // mutators
  void renderTo(sf::RenderTarget &target);
  int update(unsigned long delta_time);

  void poke() { maze.regenerate(50); }
};
