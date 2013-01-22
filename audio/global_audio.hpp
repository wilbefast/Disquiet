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

enum event_id
{
  FOOTSTEP,
  LIGHTNING,
  STORM,
  MONSTER
};

enum parameter_id
{
  PANORAMA,
  DISTANCE,
  OCCLUSION
};

int start_audio();

int audio_event(event_id);
int audio_event_end(event_id);

int audio_event_parameter(parameter_id, float value);
int audio_refresh_parameters();

int stop_audio();
