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

#include "global_audio.hpp"

// for EXIT_FAILURE and EXIT_SUCCESS
#include <stdlib.h>

// FMOD implementation
#include <fmod_event.h>
#include <fmod_errors.h>


//!-----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//!-----------------------------------------------------------------------------
static FMOD_EVENTSYSTEM *eventsystem;
static FMOD_RESULT result;

static FMOD_EVENT *ev_footstep = NULL,
                    *ev_lightning = NULL,
                    *ev_storm = NULL,
                    *ev_monster = NULL,
                    *ev_gun = NULL,
                    *ev_scream = NULL,
                    *ev_music = NULL;

static FMOD_EVENTPARAMETER *ep_panorama = NULL,
                            *ep_occlusion = NULL,
                            *ep_distance = NULL,
                            *ep_tension = NULL;

// custom assert
#include "../debug/assert.h"
#define ASSERT_FMOD(fmod_result, what)  \
  ASSERT_AUX((fmod_result == FMOD_OK), what, FMOD_ErrorString(fmod_result))


//!-----------------------------------------------------------------------------
//! START AND STOP
//!-----------------------------------------------------------------------------

static FMOD_RESULT load_event(const char *event_path, FMOD_EVENT **p_event)
{
  result = FMOD_EventSystem_GetEvent(eventsystem, event_path,
                                      FMOD_EVENT_DEFAULT, p_event);
  return result;
}

static FMOD_RESULT load_parameter(const char *parameter_name, FMOD_EVENT *event,
                                  FMOD_EVENTPARAMETER ** p_parameter)
{
  result = FMOD_Event_GetParameter(event, parameter_name, p_parameter);
  return result;
}
// startup
int start_audio()
{
  // create FMOD event system
  result = FMOD_EventSystem_Create(&eventsystem);
  ASSERT_FMOD(result, "Creating FMOD event system");

  result = FMOD_EventSystem_Init(eventsystem, 64, FMOD_INIT_NORMAL, 0,
                                 FMOD_EVENT_INIT_NORMAL);
  ASSERT_FMOD(result, "Initialising FMOD event system");

  result = FMOD_EventSystem_SetMediaPath(eventsystem, "./assets/sfx/");
  ASSERT_FMOD(result, "Setting FMOD media path to './assets/sfx/'");

  // load event set
  ASSERT_FMOD(FMOD_EventSystem_Load(eventsystem, "disquiet.fev", 0, 0),
              "loading 'disquiet.fev'");

  // get events
  ASSERT_FMOD(load_event("disquiet/character/footstep", &ev_footstep),
         "Loading 'disquiet/character/footstep'");
  ASSERT_FMOD(load_event("disquiet/character/gun", &ev_gun),
       "Loading 'disquiet/character/gun'");
  ASSERT_FMOD(load_event("disquiet/character/scream", &ev_scream),
       "Loading 'disquiet/character/scream'");
  ASSERT_FMOD(load_event("disquiet/ambient/lightning", &ev_lightning),
         "Loading 'disquiet/ambient/lightning'");
  ASSERT_FMOD(load_event("disquiet/ambient/music", &ev_music),
         "Loading 'disquiet/ambient/music'");
  ASSERT_FMOD(load_event("disquiet/ambient/storm", &ev_storm),
       "Loading 'disquiet/ambient/storm'");
  ASSERT_FMOD(load_event("disquiet/monster/monster", &ev_monster),
       "Loading 'disquiet/monster/monster'");


  // get event parameters
  ASSERT_FMOD(load_parameter("panorama", ev_monster, &ep_panorama),
              "Loading parameter 'panorama' of 'ev_monster'");
  ASSERT_FMOD(load_parameter("distance", ev_monster, &ep_distance),
              "Loading parameter 'distance' of 'ev_monster'");
  ASSERT_FMOD(load_parameter("occlusion", ev_monster, &ep_occlusion),
              "Loading parameter 'occlusion' of 'ev_monster'");
  ASSERT_FMOD(load_parameter("tension", ev_storm, &ep_tension),
              "Loading parameter 'tension' of 'ev_storm'");

  // all clear
  return EXIT_SUCCESS;
}

int stop_audio()
{
  // destroy FMOD event system
  result = FMOD_EventSystem_Release(eventsystem);
  ASSERT_FMOD(result, "Releasing FMOD event system");

  // all clear
  return EXIT_SUCCESS;
}

//!-----------------------------------------------------------------------------
//! LAUNCH/STOP AN EVENT
//!-----------------------------------------------------------------------------

static inline FMOD_EVENT* idToEvent(event_id id)
{
  switch(id)
  {
    case FOOTSTEP: return ev_footstep;
    case LIGHTNING: return ev_lightning;
    case STORM: return ev_storm;
    case MONSTER: return ev_monster;
    case GUN: return ev_gun;
    case SCREAM: return ev_scream;
    case MUSIC: return ev_music;

    default: return NULL;
  }
}

int audio_event(event_id id)
{
  FMOD_EVENT* e = idToEvent(id);
  if(e)
  {
    result = FMOD_Event_Start(e);
    return (result == FMOD_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else
    return EXIT_FAILURE;
}

int audio_event_end(event_id id)
{
  FMOD_EVENT* e = idToEvent(id);
  if(e)
  {
    result = FMOD_Event_Stop(e, 1); // 1 = 'true' for immediate stop
    return (result == FMOD_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else
    return EXIT_FAILURE;
}

//!-----------------------------------------------------------------------------
//! PARAMETERISE AN EVENT
//!-----------------------------------------------------------------------------

static inline FMOD_EVENTPARAMETER* idToParameter(parameter_id id)
{
  switch(id)
  {
    case PANORAMA: return ep_panorama;
    case OCCLUSION: return ep_occlusion;
    case DISTANCE: return ep_distance;
    case TENSION: return ep_tension;

    default: return NULL;
  }
}

int audio_event_parameter(parameter_id id, float value)
{
  FMOD_EVENTPARAMETER* p = idToParameter(id);
  if(p)
  {
    result = FMOD_EventParameter_SetValue(p, value);
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}

int audio_refresh_parameters()
{
  result = FMOD_EventSystem_Update(eventsystem);
  return EXIT_SUCCESS;
}
