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

static FMOD::Event *ev_footstep = NULL;
static FMOD::Event *ev_lightning = NULL;

// custom assert
#include "../debug/assert.h"
#define ASSERT_FMOD(fmod_result, what)  \
  ASSERT_AUX((fmod_result == FMOD_OK), what, FMOD_ErrorString(fmod_result))


//!-----------------------------------------------------------------------------
//! START AND STOP
//!-----------------------------------------------------------------------------

static int load_event(const char *event_path, FMOD::Event **p_event)
{
  (*p_event) = new FMOD::Event();
  result = eventsystem->getEvent(event_path, FMOD_EVENT_DEFAULT, p_event);
  ASSERT_FMOD(result, event_path);

  // all clear
  return EXIT_SUCCESS;
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

  // initialise each event
  ASSERT(load_event("disquiet/character/footstep", &ev_footstep) == EXIT_SUCCESS,
         "Loading 'disquiet/character/footstep'");
  ASSERT(load_event("disquiet/ambient/lightning", &ev_lightning) == EXIT_SUCCESS,
         "Loading 'disquiet/ambient/lightning'");

  // all clear
  return EXIT_SUCCESS;
}

int stop_audio()
{
  //!TODO -- free events

  // destroy FMOD event system
  result = eventsystem->release();
  ASSERT_FMOD(result, "Releasing FMOD event system");

  // all clear
  return EXIT_SUCCESS;
}

//!-----------------------------------------------------------------------------
//! LAUNCH AN EVENT
//!-----------------------------------------------------------------------------

int audio_event(event_id id)
{
  switch(id)
  {
    case FOOTSTEP:
      result = ev_footstep->start();
    break;

    case LIGHTNING:
      result = ev_lightning->start();
    break;

    default:
      // couldn't find the event
      return EXIT_FAILURE;
  }

  // check result
  return (result == FMOD_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}
