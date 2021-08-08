////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SDL.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class that handles user input to the graphics engine.
 */
class InputHandler 
{
public: 
  /**
   * Takes an event "e" and decodes/handles the event.
   * 
   * returns: True if event was handled, false otherwise.
   */
  bool handleEvent(SDL_Event e);

private:
  /**
   * Helper method used to handle all valid key down events.
   * 
   * returns: True for valid event, false otherwise.
   */
  bool handleKeyDown(SDL_Event e);

  /**
   * Helper method used to handle all valid key up events.
   * 
   * returns: True for valid event, false otherwise.
   */
  bool handleKeyUp(SDL_Event e);

};

////////////////////////////////////////////////////////////////////////////////////////////////////