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
#include <fmod_event.hpp>
#include <fmod_errors.h>

//!-----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//!-----------------------------------------------------------------------------
static FMOD::EventSystem *eventsystem;
static FMOD_RESULT result;

static FMOD::Event *ev_footstep = NULL,
                    *ev_lightning = NULL,
                    *ev_storm = NULL,
                    *ev_monster = NULL;

static FMOD::EventParameter *ep_panorama = NULL,
                            *ep_occlusion = NULL,
                            *ep_distance = NULL;

// custom assert
#include "../debug/assert.h"
#define ASSERT_FMOD(fmod_result, what)  \
  ASSERT_AUX((fmod_result == FMOD_OK), what, FMOD_ErrorString(fmod_result))


//!-----------------------------------------------------------------------------
//! START AND STOP
//!-----------------------------------------------------------------------------

static FMOD_RESULT load_event(const char *event_path, FMOD::Event **p_event)
{
  (*p_event) = new FMOD::Event();
  return (result = eventsystem->getEvent(event_path, FMOD_EVENT_DEFAULT, p_event));
}

static FMOD_RESULT load_parameter(const char *parameter_name, FMOD::Event *event,
                                  FMOD::EventParameter ** p_parameter)
{
  (*p_parameter) = new FMOD::EventParameter();
  return (result = event->getParameter(parameter_name, p_parameter));
}

// startup
int start_audio()
{
  // create FMOD event system
  result = FMOD::EventSystem_Create(&eventsystem);
  ASSERT_FMOD(result, "Creating FMOD event system");

  result = eventsystem->init(64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL);
  ASSERT_FMOD(result, "Initialising FMOD event system");

  result = eventsystem->setMediaPath("./assets/sfx/");
  ASSERT_FMOD(result, "Setting FMOD media path to './assets/sfx/'");

  // load event set
  ASSERT_FMOD(eventsystem->load("disquiet.fev", 0, 0), "loading 'disquiet.fev'");

  // get events
  ASSERT_FMOD(load_event("disquiet/character/footstep", &ev_footstep),
         "Loading 'disquiet/character/footstep'");
  ASSERT_FMOD(load_event("disquiet/ambient/lightning", &ev_lightning),
         "Loading 'disquiet/ambient/lightning'");
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


  // all clear
  return EXIT_SUCCESS;
}

int stop_audio()
{
  // free events
  delete ev_footstep;
  delete ev_lightning;
  delete ev_storm;
  delete ev_monster;

  // free parameters
  delete ep_panorama;
  delete ep_occlusion;
  delete ep_distance;

  // destroy FMOD event system
  result = eventsystem->release();
  ASSERT_FMOD(result, "Releasing FMOD event system");

  // all clear
  return EXIT_SUCCESS;
}

//!-----------------------------------------------------------------------------
//! LAUNCH/STOP AN EVENT
//!-----------------------------------------------------------------------------

static inline FMOD::Event* idToEvent(event_id id)
{
  switch(id)
  {
    case FOOTSTEP: return ev_footstep;
    case LIGHTNING: return ev_lightning;
    case STORM: return ev_storm;
    case MONSTER: return ev_monster;

    default: return NULL;
  }
}

int audio_event(event_id id)
{
  FMOD::Event* e = idToEvent(id);
  if(e)
  {
    result = e->start();
    return (result == FMOD_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else
    return EXIT_FAILURE;
}

int audio_event_end(event_id id)
{
  FMOD::Event* e = idToEvent(id);
  if(e)
  {
    result = e->stop();
    return (result == FMOD_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else
    return EXIT_FAILURE;
}

//!-----------------------------------------------------------------------------
//! PARAMETERISE AN EVENT
//!-----------------------------------------------------------------------------

static inline FMOD::EventParameter* idToParameter(parameter_id id)
{
  switch(id)
  {
    case PANORAMA: return ep_panorama;
    case OCCLUSION: return ep_occlusion;
    case DISTANCE: return ep_distance;

    default: return NULL;
  }
}

int audio_event_parameter(parameter_id id, float value)
{
  FMOD::EventParameter* p = idToParameter(id);
  if(p)
  {
    result = p->setValue(value);
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}

int audio_refresh_parameters()
{
  result = eventsystem->update();
  return EXIT_SUCCESS;
}
