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

#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SFML/Graphics.hpp>  // for RenderTarget

class Scene
{
public:
  // constructors, destructors
  Scene() { }
  virtual ~Scene() { }

  // interface
  virtual void renderTo(sf::RenderTarget &target) = 0;
  virtual int update(unsigned long delta_time) = 0;
  virtual int treatEvent(sf::Event& e) = 0;
};

#endif // SCENE_HPP_INCLUDED
